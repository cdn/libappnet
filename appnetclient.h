#ifndef _APPNETCLIENT_H_INCLUDED_
#define _APPNETCLIENT_H_INCLUDED_

#include <glib-object.h>

#define APP_NET_TYPE_CLIENT (app_net_client_get_type ())
#define APP_NET_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), APP_NET_TYPE_CLIENT, AppNetClient))
#define APP_NET_CLIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), APP_NET_TYPE_CLIENT, AppNetClientClass))
#define APP_NET_IS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), APP_NET_TYPE_CLIENT))
#define APP_NET_IS_CLIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), APP_NET_TYPE_CLIENT))
#define APP_NET_CLIENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), APP_NET_TYPE_CLIENT, AppNetClientClass))

typedef struct _AppNetClient AppNetClient;
typedef struct _AppNetClientClass AppNetClientClass;

GType
app_net_client_get_type (void);

AppNetClient*
app_net_client_new (const gchar *base_url, const gchar *token);

#endif

