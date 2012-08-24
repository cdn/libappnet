#include <memory.h>

#include <appnet/appnethttprequest.h>

struct _AppNetHttpRequest {
    GObject base;
    gchar *method;
    gchar *url;
    char *body;
    size_t  body_size;
    GList *headers;
};

struct _AppNetHttpRequestClass {
    GObjectClass base;
};

G_DEFINE_TYPE (AppNetHttpRequest, app_net_http_request, G_TYPE_OBJECT);

static GObject*
app_net_http_request_constructor (GType type, guint nprops, GObjectConstructParam *props)
{
    GObjectClass *gobject_class;
    gobject_class = G_OBJECT_CLASS (app_net_http_request_parent_class);
    return gobject_class->constructor (type, nprops, props);
}

static void
app_net_http_request_header_free (gpointer ptr)
{
    AppNetHttpRequestHeader *header = (AppNetHttpRequestHeader *) ptr;
    g_free (header->name);
    g_free (header->value);
    g_free (header);
}

static void
app_net_http_request_finalize (GObject *gobj)
{
    AppNetHttpRequest *self = APP_NET_HTTP_REQUEST (gobj);

    g_free (self->method);
    g_free (self->url);
    g_free (self->body);
    g_list_free_full (self->headers, app_net_http_request_header_free);

    G_OBJECT_CLASS (app_net_http_request_parent_class)->finalize (gobj);
}

static void
app_net_http_request_class_init (AppNetHttpRequestClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    gobject_class->constructor = app_net_http_request_constructor;
    gobject_class->finalize = app_net_http_request_finalize;
}

static void
app_net_http_request_init (AppNetHttpRequest *self)
{
    self->method = NULL;
    self->url = NULL;
    self->body = NULL;
    self->body_size = 0;
    self->headers = NULL;
}

AppNetHttpRequest*
app_net_http_request_new (const gchar *method, const gchar *url)
{
    AppNetHttpRequest *req =
        APP_NET_HTTP_REQUEST (g_object_new (APP_NET_TYPE_HTTP_REQUEST, NULL));
    /* TODO use properties */
    req->method = g_strdup (method);
    req->url = g_strdup (url);
    return req;
}

void
app_net_http_request_add_header (
    AppNetHttpRequest *self, const gchar *name, const gchar *value)
{
    AppNetHttpRequestHeader *header = g_new0 (AppNetHttpRequestHeader, 1);
    header->name = g_strdup (name);
    header->value = g_strdup (value);
    self->headers = g_list_append (self->headers, header);
}

GList *
app_net_http_request_get_headers (const AppNetHttpRequest *self)
{
    return self->headers;
}

void
app_net_http_request_set_body (
    AppNetHttpRequest *self, const char *body, size_t size)
{
    g_free (self->body);
    self->body = g_malloc (size);
    memcpy (self->body, body, size);
    self->body_size = size;
}

const gchar *
app_net_http_request_get_method (const AppNetHttpRequest *self)
{
    return self->method;
}

const gchar *
app_net_http_request_get_url (const AppNetHttpRequest *self)
{
    return self->url;
}

const char *
app_net_http_request_get_body (const AppNetHttpRequest *self)
{
    return self->body;
}

size_t
app_net_http_request_get_body_size (const AppNetHttpRequest *self)
{
    return self->body_size;
}

