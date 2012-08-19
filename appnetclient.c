#include "appnetclient.h"

struct _AppNetClient {
    GObject base;
    gchar *base_url;
    gchar *token;
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
app_net_client_finalize (GObject *gobj)
{
    AppNetClient *self = APP_NET_CLIENT (gobj);
    
    g_free (self->base_url);
    g_free (self->token);
}

static void
app_net_client_class_init (AppNetClientClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    gobject_class->constructor = app_net_client_constructor;
    gobject_class->finalize = app_net_client_finalize;
}

static void
app_net_client_init (AppNetClient *self)
{
    self->base_url = NULL;
    self->token = NULL;
}

AppNetClient*
app_net_client_new (const gchar *base_url, const gchar *token)
{
    AppNetClient *c;
    
    c = APP_NET_CLIENT (g_object_new (APP_NET_TYPE_CLIENT, NULL));
    /* TODO use properties */
    c->base_url = g_strdup (base_url);
    c->token = g_strdup (token);
    return c;
}

