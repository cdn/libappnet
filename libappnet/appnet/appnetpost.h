#ifndef _APPNETPOST_H_INCLUDED_
#define _APPNETPOST_H_INCLUDED_

#include <glib-object.h>

#define APP_NET_TYPE_POST (app_net_post_get_type ())
#define APP_NET_POST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), APP_NET_TYPE_POST, AppNetPost))
#define APP_NET_POST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), APP_NET_TYPE_POST, AppNetPostClass))
#define APP_NET_IS_POST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), APP_NET_TYPE_POST))
#define APP_NET_IS_POST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), APP_NET_TYPE_POST))
#define APP_NET_POST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), APP_NET_TYPE_POST, AppNetPostClass))

typedef struct _AppNetPost AppNetPost;
typedef struct _AppNetPostClass AppNetPostClass;

GType
app_net_post_get_type (void);

AppNetPost*
app_net_post_new (void);

const gchar *
app_net_post_get_id (const AppNetPost *self);

const gchar *
app_net_post_get_thread_id (const AppNetPost *self);

const gchar *
app_net_post_get_author (const AppNetPost *self);

const gchar *
app_net_post_get_author_name (const AppNetPost *self);

const gchar *
app_net_post_get_text (const AppNetPost *self);

const gchar *
app_net_post_get_html (const AppNetPost *self);

void
app_net_post_free_list (GList *posts);

#endif

