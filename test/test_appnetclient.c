#include <glib.h>
#include "appnetclient.h"

static
void _app_net_client_trivial(void)
{
    AppNetClient *client = app_net_client_new ("http://localhost/appnetstub", "abcdefasdafasd", "abcdefg");
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

