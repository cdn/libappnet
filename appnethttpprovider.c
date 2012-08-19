#include "appnethttpprovider.h"

G_DEFINE_INTERFACE (AppNetHttpProvider, app_net_http_provider, G_TYPE_OBJECT);

static void
app_net_http_provider_default_init (AppNetHttpProviderInterface *self)
{
}

AppNetHttpResponse *
app_net_http_provider_send_request (
    AppNetHttpProvider *self, AppNetHttpRequest *r)
{
    return APP_NET_HTTP_PROVIDER_GET_INTERFACE (self)->send_request (self, r);
}

