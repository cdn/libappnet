#include "appnetstubhttpprovider.h"

struct _AppNetStubHttpProvider {
    GObject base;
    AppNetHttpRequest  *request;
    AppNetHttpResponse *response;
};

struct _AppNetStubHttpProviderClass {
    GObjectClass base;
};

static void
app_net_http_provider_iface_init (AppNetHttpProviderInterface *iface);

G_DEFINE_TYPE_WITH_CODE (AppNetStubHttpProvider, app_net_stub_http_provider, G_TYPE_OBJECT,
        G_IMPLEMENT_INTERFACE (APP_NET_TYPE_HTTP_PROVIDER, app_net_http_provider_iface_init));

static GObject*
app_net_stub_http_provider_constructor (GType type, guint nprops, GObjectConstructParam *props)
{
    GObjectClass *gobject_class;
    gobject_class = G_OBJECT_CLASS (app_net_stub_http_provider_parent_class);
    return gobject_class->constructor (type, nprops, props);
}

static void
app_net_stub_http_provider_dispose (GObject *gobj)
{
    AppNetStubHttpProvider *self = APP_NET_STUB_HTTP_PROVIDER (gobj);

    if (self->request != NULL) {
        g_object_unref (self->request);
        self->request = NULL;
    }

    if (self->response != NULL) {
        g_object_unref (self->response);
        self->response = NULL;
    }

    G_OBJECT_CLASS (app_net_stub_http_provider_parent_class)->dispose (gobj);
}

static void
app_net_stub_http_provider_class_init (AppNetStubHttpProviderClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    gobject_class->constructor = app_net_stub_http_provider_constructor;
    gobject_class->dispose = app_net_stub_http_provider_dispose;
}

static void
app_net_stub_http_provider_init (AppNetStubHttpProvider *self)
{
    self->request = NULL;
    self->response = NULL;
}

static AppNetHttpResponse*
app_net_stub_http_provider_send_request (
    AppNetHttpProvider *provider,
    AppNetHttpRequest *req
)
{
    AppNetStubHttpProvider *self = APP_NET_STUB_HTTP_PROVIDER (provider);
    if (self->request != NULL) g_object_unref (self->request);
    self->request = req;
    if (self->request != NULL) g_object_ref (self->request);

    if (self->response != NULL) g_object_ref (self->response);
    return self->response;
}

static void
app_net_http_provider_iface_init (AppNetHttpProviderInterface *iface)
{
    iface->send_request = app_net_stub_http_provider_send_request;
}

AppNetStubHttpProvider*
app_net_stub_http_provider_new (void)
{
    return app_net_stub_http_provider_new_with_response (NULL);
}

AppNetStubHttpProvider*
app_net_stub_http_provider_new_with_response (AppNetHttpResponse *resp)
{
    AppNetStubHttpProvider *self;
    
    self = APP_NET_STUB_HTTP_PROVIDER (g_object_new (APP_NET_TYPE_STUB_HTTP_PROVIDER, NULL));
    /* TODO properties */
    app_net_stub_http_provider_set_response (self, resp);

    return self;
}

AppNetHttpRequest*
app_net_stub_http_provider_get_request (const AppNetStubHttpProvider *self)
{
    return self->request;
}

AppNetHttpResponse*
app_net_stub_http_provider_get_response (const AppNetStubHttpProvider *self)
{
    return self->response;
}

void
app_net_stub_http_provider_set_response (
    AppNetStubHttpProvider *self,
    AppNetHttpResponse *resp
)
{
    if (self->response != NULL) g_object_unref (self->response);
    self->response = resp;
    if (self->response != NULL) g_object_ref (self->response);
}

