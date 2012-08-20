#include <memory.h>

#include <jansson.h>

#include "appnetclient.h"

#include "appnetpost.h"
#include "appnetpost-private.h"
#include "appnetsouphttpprovider.h"

struct _AppNetClient {
    GObject base;
    gchar *base_url;
    gchar *client_id;
    gchar *token;
    AppNetHttpProvider *http_provider;
};

struct _AppNetClientClass {
    GObjectClass base;
};

typedef struct _AppNetApiCall {
    AppNetClient *client;
    gchar *url;
    char *body;
    size_t body_size;
} AppNetApiCall;

G_DEFINE_TYPE (AppNetClient, app_net_client, G_TYPE_OBJECT);

static GObject*
app_net_client_constructor (GType type, guint nprops, GObjectConstructParam *props)
{
    GObjectClass *gobject_class;
    gobject_class = G_OBJECT_CLASS (app_net_client_parent_class);
    return gobject_class->constructor (type, nprops, props);
}

static void
app_net_client_dispose (GObject *gobj)
{
    AppNetClient *self = APP_NET_CLIENT (gobj);
    g_object_unref (self->http_provider);
    self->http_provider = NULL;
}

static void
app_net_client_finalize (GObject *gobj)
{
    AppNetClient *self = APP_NET_CLIENT (gobj);
    
    g_free (self->base_url);
    g_free (self->client_id);
    g_free (self->token);
}

static void
app_net_client_class_init (AppNetClientClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    gobject_class->constructor = app_net_client_constructor;
    gobject_class->dispose = app_net_client_dispose;
    gobject_class->finalize = app_net_client_finalize;
}

static void
app_net_client_init (AppNetClient *self)
{
    self->base_url = NULL;
    self->client_id = NULL;
    self->token = NULL;
    self->http_provider = NULL;
}

AppNetClient*
app_net_client_new (const gchar *base_url, const gchar *client_id, const gchar *token)
{
    AppNetSoupHttpProvider *http_provider = app_net_soup_http_provider_new ();
    return app_net_client_new_with_http_provider (
        base_url, client_id, token, APP_NET_HTTP_PROVIDER (http_provider));
}

AppNetClient *
app_net_client_new_with_http_provider (
    const gchar *base_url,
    const gchar *client_id,
    const gchar *token,
    AppNetHttpProvider *http_provider)
{
    AppNetClient *c;
    
    c = APP_NET_CLIENT (g_object_new (APP_NET_TYPE_CLIENT, NULL));
    /* TODO use properties */
    c->base_url = g_strdup (base_url);
    c->client_id = g_strdup (client_id);
    c->token = g_strdup (token);
    c->http_provider = http_provider;

    return c;
}

static gchar *
app_net_client_url_vformat (const AppNetClient *self, const gchar *relpath, va_list args)
{
    gchar *result;
    gchar *base = g_strjoin ("/", self->base_url, relpath, NULL);

    result = g_strdup_vprintf (base, args);

    g_free (base);
    return result;
}

static void
app_net_client_create_api_call (AppNetClient *self, AppNetApiCall *call, const gchar *relpath, ...)
{
    va_list args;

    call->client = self;
    va_start (args, relpath);
    call->url = app_net_client_url_vformat (self, relpath, args);
    va_end (args);
    call->body = NULL;
    call->body_size = 0;
}

static char *
app_net_client_exec_api_call (AppNetApiCall *call, const gchar *method, size_t *size)
{
    static const gchar content_type[] = "application/x-form-www-urlencoded; charset=utf-8";
    guint status;
    /*
    SoupMessage *message;
    */
    gchar *auth_header;
    char *data = NULL;
    AppNetHttpRequest *req = NULL;
    AppNetHttpResponse *resp = NULL;
    AppNetClient *client = call->client;

    req = app_net_http_request_new (method, call->url);
    auth_header = g_strdup_printf ("Bearer %s", client->token);
    app_net_http_request_add_header (req, "Authorization", auth_header);
    g_free (auth_header);
    if (call->body != NULL) {
        /* TODO don't take a copy of the data */
        app_net_http_request_add_header (req, "Content-Type", content_type);
        app_net_http_request_set_body (req, call->body, call->body_size);
    }
    resp = app_net_http_provider_send_request (
        APP_NET_HTTP_PROVIDER (client->http_provider), req);
    status = app_net_http_response_get_status (resp);
    if (status >= 200 && status <= 299) {
        app_net_http_response_copy_body (resp, &data, size);
    }

    g_object_unref (req);
    g_object_unref (resp);
    return data;
}

static void
app_net_client_destroy_api_call (AppNetApiCall *call)
{
    g_free (call->url);
    g_free (call->body);
}

GList*
app_net_client_get_stream (AppNetClient *self)
{
    static const gchar method[] = "GET";
    static const gchar endpoint[] = "stream/0/posts/stream";

    AppNetApiCall call;
    GList *posts = NULL;
    char *data;
    size_t size;
    json_t *response = NULL;
    json_error_t error;

    app_net_client_create_api_call (self, &call, endpoint);
    data = app_net_client_exec_api_call (&call, method, &size);

    if (data == NULL) {
        g_warning ("%s: API call failed", endpoint);
        goto done;
    }

    response = json_loadb (data, size, 0, &error);
    if (response == NULL) {
        g_warning (
            "%s: %d:%d [offset=%d] %s",
            endpoint, error.line, error.column, error.position, error.text);
        goto done;
    }

    if (json_is_array (response)) {
        size_t i;
        const size_t num_posts = json_array_size (response);

        for (i = 0; i < num_posts; i++) {
            json_t *post_obj = json_array_get (response, i);
            AppNetPost *post = _app_net_post_from_json (post_obj);
            posts = g_list_append (posts, post);
        }
    }

done:
    if (response) json_decref (response);
    g_free (data);
    app_net_client_destroy_api_call (&call);
    return posts;
}

AppNetPost *
app_net_client_add_post (AppNetClient *self, const gchar *text)
{
    static const gchar method[] = "POST";
    static const gchar endpoint[] = "stream/0/posts";

    AppNetApiCall call;
    AppNetPost *post = NULL;
    char *data;
    size_t size;
    json_error_t error;
    json_t *response = NULL;
    gchar *body;
    gchar *encoded_text;

    encoded_text = g_uri_escape_string (
        text, G_URI_RESERVED_CHARS_GENERIC_DELIMITERS, TRUE);
    body = g_strdup_printf ("text=%s", encoded_text);
    g_free (encoded_text);

    app_net_client_create_api_call (self, &call, endpoint);

    /* XXX this is a bit yuck. call.body is cleaned up automatically. */
    call.body = body;
    call.body_size = strlen (body);

    data = app_net_client_exec_api_call (&call, method, &size);

    if (data == NULL) {
        g_warning ("%s: API call failed", endpoint);
        goto done;
    }

    response = json_loadb (data, size, 0, &error);
    if (response == NULL) {
        g_warning (
            "%s: %d:%d [offset=%d] %s",
            endpoint, error.line, error.column, error.position, error.text);
        goto done;
    }

    if (json_is_object (response)) {
        post = _app_net_post_from_json (response);
    }

done:
    if (response) json_decref (response);
    g_free (data);
    app_net_client_destroy_api_call (&call);
    return post;
}

