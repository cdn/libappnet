#include <memory.h>

#include "appnethttpresponse.h"

struct _AppNetHttpResponse {
    GObject  base;
    guint8  *body;
    size_t   body_size;
    gboolean copied;
    guint    status;
};

struct _AppNetHttpResponseClass {
    GObjectClass base;
};

G_DEFINE_TYPE (AppNetHttpResponse, app_net_http_response, G_TYPE_OBJECT);

static GObject*
app_net_http_response_constructor (GType type, guint nprops, GObjectConstructParam *props)
{
    GObjectClass *gobject_class;
    gobject_class = G_OBJECT_CLASS (app_net_http_response_parent_class);
    return gobject_class->constructor (type, nprops, props);
}

static void
app_net_http_response_finalize (GObject *gobj)
{
    AppNetHttpResponse *self = APP_NET_HTTP_RESPONSE (gobj);

    if (self->copied) {
        g_free (self->body);
    }
}

static void
app_net_http_response_class_init (AppNetHttpResponseClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    gobject_class->constructor = app_net_http_response_constructor;
    gobject_class->finalize = app_net_http_response_finalize;
}

static void
app_net_http_response_init (AppNetHttpResponse *self)
{
    self->body = NULL;
    self->body_size = 0;
    self->copied = FALSE;
    self->status = 0;
}

AppNetHttpResponse*
app_net_http_response_new (guint status, const guint8 *body, const size_t size)
{
    AppNetHttpResponse *self =
        APP_NET_HTTP_RESPONSE (g_object_new (APP_NET_TYPE_HTTP_RESPONSE, NULL));
    /* TODO use properties */
    self->status = status;
    self->body = (guint8 *) body;
    self->body_size = size;
    self->copied = FALSE;
    return self;
}

AppNetHttpResponse*
app_net_http_response_new_with_copy (guint status, const guint8 *body, const size_t size)
{
    AppNetHttpResponse *self =
        APP_NET_HTTP_RESPONSE (g_object_new (APP_NET_TYPE_HTTP_RESPONSE, NULL));
    /* TODO use properties */
    self->status = status;
    self->body = g_malloc (size);
    memcpy (self->body, body, size);
    self->body_size = size;
    self->copied = TRUE;
    return self;
}

guint
app_net_http_response_get_status (const AppNetHttpResponse *self)
{
    return self->status;
}

const guint8*
app_net_http_response_get_body (const AppNetHttpResponse *self)
{
    return self->body;
}

size_t
app_net_http_response_get_body_size (const AppNetHttpResponse *self)
{
    return self->body_size;
}

void
app_net_http_response_copy_body (const AppNetHttpResponse *self, guint8 **data, size_t *size)
{
    *data = g_malloc (self->body_size);
    memcpy (*data, self->body, self->body_size);
    *size = self->body_size;
}

