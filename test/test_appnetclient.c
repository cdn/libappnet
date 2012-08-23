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

static
void _app_net_client_trivial(void)
{
    AppNetClient *client;
    make_app_net_client (&client, NULL);
    g_object_unref (client);
}

int
main (int argc, char **argv)
{
    g_type_init ();
    g_test_init (&argc, &argv, NULL);

    g_test_add_func ("/appnetclient/trivial", _app_net_client_trivial);

    g_test_run ();

    return 0;
}

