#ifndef _APPNETSOUPHTTPPROVIDER_H_INCLUDED_
#define _APPNETSOUPHTTPPROVIDER_H_INCLUDED_

#include <glib-object.h>

#include <appnet/appnethttpprovider.h>

#define APP_NET_TYPE_SOUP_HTTP_PROVIDER (app_net_soup_http_provider_get_type ())
#define APP_NET_SOUP_HTTP_PROVIDER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), APP_NET_TYPE_SOUP_HTTP_PROVIDER, AppNetSoupHttpProvider))
#define APP_NET_SOUP_HTTP_PROVIDER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), APP_NET_TYPE_SOUP_HTTP_PROVIDER, AppNetSoupHttpProviderClass))
#define APP_NET_IS_SOUP_HTTP_PROVIDER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), APP_NET_TYPE_SOUP_HTTP_PROVIDER))
#define APP_NET_IS_SOUP_HTTP_PROVIDER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), APP_NET_TYPE_SOUP_HTTP_PROVIDER))
#define APP_NET_SOUP_HTTP_PROVIDER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), APP_NET_TYPE_SOUP_HTTP_PROVIDER, AppNetSoupHttpProviderClass))

typedef struct _AppNetSoupHttpProvider AppNetSoupHttpProvider;
typedef struct _AppNetSoupHttpProviderClass AppNetSoupHttpProviderClass;

GType
app_net_soup_http_provider_get_type (void);

AppNetSoupHttpProvider*
app_net_soup_http_provider_new (void);

#endif

