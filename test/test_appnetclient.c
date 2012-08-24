#include <glib.h>

#include <appnet/appnet.h>

#include "appnetstubhttpprovider.h"

static const gchar *base_url = "http://localhost/appnetstub";
static const gchar *access_token = "abcdefg";

static void
make_app_net_client (AppNetClient **client, AppNetStubHttpProvider **prov)
{
    AppNetStubHttpProvider *stub;
    stub = app_net_stub_http_provider_new ();
    *client = app_net_client_new_with_http_provider (
                base_url, access_token, APP_NET_HTTP_PROVIDER (stub));
    if (prov != NULL) *prov = stub;
}

static void
_app_net_client_trivial(void)
{
    AppNetClient *client;
    make_app_net_client (&client, NULL);
    g_object_unref (client);
}

static gboolean
load_file (const char *name, gchar **data, gsize *len)
{
    gboolean result;
    gchar *dirname = g_path_get_dirname (__FILE__);
    gchar *realname = g_build_filename (dirname, "data", name, NULL);

    result = g_file_get_contents (realname, data, len, NULL);

    g_free (realname);
    g_free (dirname);

    return result;
}

static void
_app_net_client_add_post (void)
{
    AppNetClient *client;
    AppNetStubHttpProvider *stub;
    AppNetHttpResponse *resp;
    AppNetHttpRequest *req;
    gchar *body;
    gsize bodylen;
    AppNetPost *post;
    gchar *url;

    make_app_net_client (&client, &stub);

    g_assert (load_file ("appnetclient_add-post", &body, &bodylen));
    /* glib 2.30 */
    /*
    if (!load_file ("appnetclient_add-post", &body, &bodylen)) {
        g_test_fail ();
        return;
    }
    */

    resp = app_net_http_response_new (200, body, bodylen);
    app_net_stub_http_provider_set_response (stub, resp);
    post = app_net_client_add_post (client, "Hello World");

    req = app_net_stub_http_provider_get_request (stub);
    url = g_strdup_printf ("%s/stream/0/posts", base_url);
    g_assert_cmpstr (app_net_http_request_get_url (req), ==, url);
    g_free (url);

    g_assert_cmpstr (app_net_http_request_get_method (req), ==, "POST");
    g_assert_cmpstr (app_net_post_get_author (post), ==, "tomlee");
    g_assert_cmpstr (app_net_post_get_author_name (post), ==, "Tom Lee");
    g_assert_cmpstr (app_net_post_get_id (post), ==, "abcdefg");
    g_assert_cmpstr (app_net_post_get_text (post), ==, "Hello, World");

    g_object_unref (post);
    g_object_unref (client);
}

static void
_app_net_client_get_stream_before (void)
{
    AppNetClient *client;
    AppNetStubHttpProvider *stub;
    AppNetHttpResponse *resp;
    AppNetHttpRequest *req;
    gchar *body;
    gsize bodylen;
    AppNetPost *post;
    GList *posts;
    gchar *url;

    make_app_net_client (&client, &stub);

    g_assert (load_file ("appnetclient_timeline", &body, &bodylen));
    /* glib 2.30 */
    /*
    if (!load_file ("appnetclient_timeline", &body, &bodylen)) {
        g_test_fail ();
        return;
    }
    */

    resp = app_net_http_response_new (200, body, bodylen);
    app_net_stub_http_provider_set_response (stub, resp);
    posts = app_net_client_get_stream_before (client, "abc", 0);

    req = app_net_stub_http_provider_get_request (stub);
    url = g_strdup_printf ("%s/stream/0/posts/stream?before_id=abc", base_url);
    g_assert_cmpstr (app_net_http_request_get_url (req), ==, url);
    g_free (url);

    g_assert_cmpint (g_list_length (posts), ==, 1);

    post = APP_NET_POST (g_list_first (posts)->data);
    g_assert_cmpstr (app_net_http_request_get_method (req), ==, "GET");
    g_assert_cmpstr (app_net_post_get_author (post), ==, "tomlee");
    g_assert_cmpstr (app_net_post_get_author_name (post), ==, "Tom Lee");
    g_assert_cmpstr (app_net_post_get_id (post), ==, "abcdefg");
    g_assert_cmpstr (app_net_post_get_text (post), ==, "Hello, World");

    g_object_unref (post);
    g_object_unref (client);
}

int
main (int argc, char **argv)
{
    g_type_init ();
    g_test_init (&argc, &argv, NULL);

    g_test_add_func ("/appnetclient/trivial", _app_net_client_trivial);
    g_test_add_func ("/appnetclient/add_post", _app_net_client_add_post);
    g_test_add_func ("/appnetclient/get_stream_before", _app_net_client_get_stream_before);

    g_test_run ();

    return 0;
}

