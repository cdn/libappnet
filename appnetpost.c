#include <jansson.h>

#include "appnetpost.h"
#include "appnetpost-private.h"

struct _AppNetPost {
    GObject base;
};

struct _AppNetPostClass {
    GObjectClass base;
};

G_DEFINE_TYPE (AppNetPost, app_net_post, G_TYPE_OBJECT);

static GObject*
app_net_post_constructor (GType type, guint nprops, GObjectConstructParam *props)
{
    GObjectClass *gobject_class;
    gobject_class = G_OBJECT_CLASS (app_net_post_parent_class);
    return gobject_class->constructor (type, nprops, props);
}

static void
app_net_post_class_init (AppNetPostClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    gobject_class->constructor = app_net_post_constructor;
}

static void
app_net_post_init (AppNetPost *self)
{
}

AppNetPost*
app_net_post_new (void)
{
    return APP_NET_POST (g_object_new (APP_NET_TYPE_POST, NULL));
}

AppNetPost*
_app_net_post_from_json (json_t *json)
{
    AppNetPost *post = app_net_post_new ();
    /* TODO */
    return post;
}

