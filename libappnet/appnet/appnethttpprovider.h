#ifndef _APPNETHTTPPROVIDER_H_INCLUDED_
#define _APPNETHTTPPROVIDER_H_INCLUDED_

#include <glib-object.h>

#include <appnet/appnethttprequest.h>
#include <appnet/appnethttpresponse.h>

#define APP_NET_TYPE_HTTP_PROVIDER (app_net_http_provider_get_type ())
#define APP_NET_HTTP_PROVIDER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), APP_NET_TYPE_HTTP_PROVIDER, AppNetHttpProvider))
#define APP_NET_IS_HTTP_PROVIDER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), APP_NET_TYPE_HTTP_PROVIDER))
#define APP_NET_HTTP_PROVIDER_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), APP_NET_TYPE_HTTP_PROVIDER, AppNetHttpProviderInterface))

typedef struct _AppNetHttpProvider AppNetHttpProvider;
typedef struct _AppNetHttpProviderInterface AppNetHttpProviderInterface;

struct _AppNetHttpProviderInterface {
    GTypeInterface base;

    AppNetHttpResponse *(*send_request)(
        AppNetHttpProvider *, AppNetHttpRequest *r);
};

GType
app_net_http_provider_get_type (void);

/**
 * app_net_http_provider_send_request:
 * Returns: (transfer full):
 */
AppNetHttpResponse *
app_net_http_provider_send_request (
    AppNetHttpProvider *self, AppNetHttpRequest *r);

#endif

