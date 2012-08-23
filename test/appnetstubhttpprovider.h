#ifndef _APPNETSTUBHTTPPROVIDER_H_INCLUDED_
#define _APPNETSTUBHTTPPROVIDER_H_INCLUDED_

#include <glib-object.h>

#include <appnet/appnet.h>

#define APP_NET_TYPE_STUB_HTTP_PROVIDER (app_net_stub_http_provider_get_type ())
#define APP_NET_STUB_HTTP_PROVIDER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), APP_NET_TYPE_STUB_HTTP_PROVIDER, AppNetStubHttpProvider))
#define APP_NET_STUB_HTTP_PROVIDER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), APP_NET_TYPE_STUB_HTTP_PROVIDER, AppNetStubHttpProviderClass))
#define APP_NET_IS_STUB_HTTP_PROVIDER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), APP_NET_TYPE_STUB_HTTP_PROVIDER))
#define APP_NET_IS_STUB_HTTP_PROVIDER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), APP_NET_TYPE_STUB_HTTP_PROVIDER))
#define APP_NET_STUB_HTTP_PROVIDER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), APP_NET_TYPE_STUB_HTTP_PROVIDER, AppNetStubHttpProviderClass))

typedef struct _AppNetStubHttpProvider AppNetStubHttpProvider;
typedef struct _AppNetStubHttpProviderClass AppNetStubHttpProviderClass;

GType
app_net_stub_http_provider_get_type (void);

AppNetStubHttpProvider*
app_net_stub_http_provider_new (void);

AppNetStubHttpProvider*
app_net_stub_http_provider_new_with_response (AppNetHttpResponse *resp);

AppNetHttpRequest*
app_net_stub_http_provider_get_request (const AppNetStubHttpProvider *self);

AppNetHttpResponse*
app_net_stub_http_provider_get_response (const AppNetStubHttpProvider *self);

void
app_net_stub_http_provider_set_response (
    AppNetStubHttpProvider *self,
    AppNetHttpResponse *resp
);

#endif

