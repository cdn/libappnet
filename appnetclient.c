#include "appnetclient.h"

struct _AppNetClient {
    GObject base;
};

struct _AppNetClientClass {
    GObjectClass base;
};

G_DEFINE_TYPE (AppNetClient, app_net_client, G_TYPE_OBJECT);

static GObject*
app_net_client_constructor (GType type, guint nprops, GObjectConstructParam *props)
{
    GObjectClass *gobject_class;
    gobject_class = G_OBJECT_CLASS (app_net_client_parent_class);
    return gobject_class->constructor (type, nprops, props);
}

static void
app_net_client_class_init (AppNetClientClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    gobject_class->constructor = app_net_client_constructor;
}

static void
app_net_client_init (AppNetClient *self)
{
}

AppNetClient*
app_net_client_new (void)
{
    return APP_NET_CLIENT (g_object_new (APP_NET_TYPE_CLIENT, NULL));
}

