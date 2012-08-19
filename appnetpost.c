#include <jansson.h>

#include "appnetpost.h"
#include "appnetpost-private.h"

enum {
    PROP_APP_NET_POST_ID=1,
    PROP_APP_NET_POST_THREAD_ID,
    PROP_APP_NET_POST_USERNAME,
    PROP_APP_NET_POST_NAME,
    PROP_APP_NET_POST_TEXT,
    PROP_APP_NET_POST_HTML,
    /*
    PROP_APP_NET_POST_HASHTAGS,
    PROP_APP_NET_POST_MENTIONS,
    PROP_APP_NET_POST_LINKS,
    */
    NUM_APP_NET_POST_PROPERTIES
};

static GParamSpec *properties[NUM_APP_NET_POST_PROPERTIES] = { NULL };

struct _AppNetPost {
    GObject base;
    gchar *id;
    gchar *thread_id;
    gchar *username;
    gchar *name;
    gchar *text;
    gchar *html;
    /*
    GValueArray *hashtags;
    GValueArray *mentions;
    GValueArray *links;
    */
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
app_net_post_set_property (GObject *gobj, guint property_id, const GValue *value, GParamSpec *spec)
{
    AppNetPost *self = APP_NET_POST (gobj);

    switch (property_id) {
        case PROP_APP_NET_POST_ID:
            {
                g_free (self->id);
                self->id = g_value_dup_string (value);
                break;
            }
        case PROP_APP_NET_POST_THREAD_ID:
            {
                g_free (self->thread_id);
                self->thread_id = g_value_dup_string (value);
                break;
            }
        case PROP_APP_NET_POST_USERNAME:
            {
                g_free (self->username);
                self->username = g_value_dup_string (value);
                break;
            }
        case PROP_APP_NET_POST_NAME:
            {
                g_free (self->name);
                self->name = g_value_dup_string (value);
                break;
            }
        case PROP_APP_NET_POST_TEXT:
            {
                g_free (self->text);
                self->text = g_value_dup_string (value);
                break;
            }
        case PROP_APP_NET_POST_HTML:
            {
                g_free (self->html);
                self->html = g_value_dup_string (value);
                break;
            }
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (gobj, property_id, spec);
    };
}

static void
app_net_post_get_property (GObject *gobj, guint property_id, GValue *value, GParamSpec *spec)
{
    AppNetPost *self = APP_NET_POST (gobj);

    switch (property_id) {
        case PROP_APP_NET_POST_ID:
            {
                g_value_set_string (value, self->id);
                break;
            }
        case PROP_APP_NET_POST_THREAD_ID:
            {
                g_value_set_string (value, self->thread_id);
                break;
            }
        case PROP_APP_NET_POST_USERNAME:
            {
                g_value_set_string (value, self->username);
                break;
            }
        case PROP_APP_NET_POST_NAME:
            {
                g_value_set_string (value, self->name);
                break;
            }
        case PROP_APP_NET_POST_TEXT:
            {
                g_value_set_string (value, self->text);
                break;
            }
        case PROP_APP_NET_POST_HTML:
            {
                g_value_set_string (value, self->html);
                break;
            }
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (gobj, property_id, spec);
    }
}

static void
app_net_post_finalize (GObject *gobj)
{
    AppNetPost *post = APP_NET_POST (gobj);

    g_free (post->id);
    g_free (post->thread_id);
    g_free (post->username);
    g_free (post->name);
    g_free (post->text);
    g_free (post->html);
    /* TODO g_list_free_full to clean up properly */
    /*
    g_list_free (post->hashtags);
    g_list_free (post->mentions);
    g_list_free (post->links);
    */
}

static void
app_net_post_class_init (AppNetPostClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    gobject_class->constructor = app_net_post_constructor;
    gobject_class->set_property = app_net_post_set_property;
    gobject_class->get_property = app_net_post_get_property;
    gobject_class->finalize = app_net_post_finalize;

    properties[PROP_APP_NET_POST_ID] =
        g_param_spec_string ("id",
                             "Post ID",
                             "Get/set the post ID",
                             NULL,
                             G_PARAM_READWRITE);
    properties[PROP_APP_NET_POST_THREAD_ID] =
        g_param_spec_string ("thread-id",
                             "Post thread ID",
                             "Get/set the post thread ID",
                             NULL,
                             G_PARAM_READWRITE);
    properties[PROP_APP_NET_POST_USERNAME] =
        g_param_spec_string ("author",
                             "Post author username",
                             "Get/set the username of the author",
                             NULL,
                             G_PARAM_READWRITE);
    properties[PROP_APP_NET_POST_NAME] =
        g_param_spec_string ("author-name",
                             "Post author name",
                             "Get/set the name of the author",
                             NULL,
                             G_PARAM_READWRITE);
    properties[PROP_APP_NET_POST_TEXT] =
        g_param_spec_string ("text",
                             "Post text",
                             "Get/set the post text",
                             NULL,
                             G_PARAM_READWRITE);
    properties[PROP_APP_NET_POST_HTML] =
        g_param_spec_string ("html",
                            "Post HTML",
                            "Get/set the post HTML",
                            NULL,
                            G_PARAM_READWRITE);
    g_object_class_install_properties (
        gobject_class, NUM_APP_NET_POST_PROPERTIES, properties);
}

static void
app_net_post_init (AppNetPost *self)
{
    self->id = NULL;
    self->thread_id = NULL;
    self->username = NULL;
    self->name = NULL;
    self->text = NULL;
    self->html = NULL;
    /*
    self->hashtags = NULL;
    self->mentions = NULL;
    self->links = NULL;
    */
}

AppNetPost*
app_net_post_new (void)
{
    return APP_NET_POST (g_object_new (APP_NET_TYPE_POST, NULL));
}

static gboolean
app_net_post_bind_json_string_property (
    AppNetPost *self, const gchar *prop, json_t *json, const gchar *key)
{
    json_t *value = json_object_get (json, key);
    if (value != NULL) {
        g_object_set (self, prop, json_string_value (value), NULL);
        return TRUE;
    }
    return FALSE;
}

AppNetPost*
_app_net_post_from_json (json_t *json)
{
    json_t *user = json_object_get (json, "user");
    AppNetPost *post = app_net_post_new ();
    app_net_post_bind_json_string_property (post, "id", json, "id");
    app_net_post_bind_json_string_property (post, "thread-id", json, "thread_id");
    if (user != NULL) {
        app_net_post_bind_json_string_property (post, "author", user, "username");
        app_net_post_bind_json_string_property (post, "author-name", user, "name");
    }
    app_net_post_bind_json_string_property (post, "text", json, "text");
    app_net_post_bind_json_string_property (post, "html", json, "html");
    return post;
}

const gchar *
app_net_post_get_id (const AppNetPost *self)
{
    return self->id;
}

const gchar *
app_net_post_get_thread_id (const AppNetPost *self)
{
    return self->thread_id;
}

const gchar *
app_net_post_get_author (const AppNetPost *self)
{
    return self->username;
}

const gchar *
app_net_post_get_author_name (const AppNetPost *self)
{
    return self->name;
}

const gchar *
app_net_post_get_text (const AppNetPost *self)
{
    return self->text;
}

const gchar *
app_net_post_get_html (const AppNetPost *self)
{
    return self->html;
}

