#include <memory.h>

#include <libsoup/soup.h>
#include <jansson.h>

#include "appnetclient.h"

#include "appnetpost.h"
#include "appnetpost-private.h"

struct _AppNetClient {
    GObject base;
    gchar *base_url;
    gchar *client_id;
    gchar *token;
    SoupSession *session;
};

struct _AppNetClientClass {
    GObjectClass base;
};

typedef struct _AppNetApiCall {
    AppNetClient *client;
    gchar *url;
    gchar *body;
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
    g_object_unref (self->session);
    self->session = NULL;
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
}

AppNetClient*
app_net_client_new (const gchar *base_url, const gchar *client_id, const gchar *token)
{
    AppNetClient *c;
    
    c = APP_NET_CLIENT (g_object_new (APP_NET_TYPE_CLIENT, NULL));
    /* TODO use properties */
    c->base_url = g_strdup (base_url);
    c->client_id = g_strdup (client_id);
    c->token = g_strdup (token);
    /* TODO add HAVE_LIBSOUP_GNOME check to configure.ac */
    /* TODO SSL certificate verification */
#ifdef HAVE_LIBSOUP_GNOME
    c->session = soup_session_sync_new_with_options (
        SOUP_SESSION_ADD_FEATURE_BY_TYPE, SOUP_TYPE_PROXY_RESOLVER_GNOME,
        NULL);
#else
    c->session = soup_session_sync_new ();
#endif

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
}

static char *
app_net_client_exec_api_call (AppNetApiCall *call, size_t *size)
{
    guint status;
    SoupMessage *message;
    gchar *auth_header;
    char *data = NULL;
    AppNetClient *client = call->client;

    auth_header = g_strdup_printf ("Bearer %s", client->token);

    message = soup_message_new ("GET", call->url);
    soup_message_headers_append (message->request_headers, "Authorization", auth_header);
    status = soup_session_send_message (client->session, message);
    if (status >= 200 && status <= 299) {
        *size = message->response_body->length;
        data = (char *) g_malloc (*size);
        memcpy (data, message->response_body->data, *size);
    }
    g_free (auth_header);
    g_object_unref (message);
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
    static const gchar endpoint[] = "stream/0/posts/stream";

    AppNetApiCall call;
    GList *posts = NULL;
    gchar *data;
    size_t size;
    json_t *response = NULL;
    json_error_t error;
    app_net_client_create_api_call (self, &call, endpoint);
    data = app_net_client_exec_api_call (&call, &size);

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

