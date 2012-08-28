#include <appnet/appnet.h>

static const gchar *api_endpoint = "https://alpha-api.app.net";

static void
print_post (const AppNetPost *post, gpointer unused)
{
    g_print ("<%s> %s\n",
        app_net_post_get_author (post),
        app_net_post_get_text (post));
    g_print ("------------------------------------------------\n");
}

int
main (int argc, char **argv)
{
    AppNetClient *client;
    GList *posts;

    if (argc != 2) {
        gchar *prog = g_path_get_basename (argv[0]);
        g_print ("usage: %s <access-token>\n", prog);
        g_free (prog);
        return 1;
    }

    g_type_init ();

    client = app_net_client_new (api_endpoint, argv[1]);
    posts = app_net_client_get_stream_before (client, NULL, 50);
    g_list_foreach (posts, (GFunc) print_post, NULL);
    app_net_post_free_list (posts);
    g_object_unref (client);

    return 0;
}

