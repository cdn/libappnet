#include <glib.h>

#include <appnet/appnet.h>

static void
_app_net_params_trivial(void)
{
    gchar *value;
    GArray *arr;
    
    arr = app_net_params_new ();
    value = app_net_params_format (arr, TRUE);
    app_net_params_free (arr);

    g_assert_cmpstr (value, ==, "");
    g_free (value);
}

static void
_app_net_params_format_strings(void)
{
    gchar *value;
    GArray *arr;

    arr = app_net_params_new ();
    app_net_params_add_string (arr, "foo", "bar");
    app_net_params_add_string (arr, "baz", "boz");
    value = app_net_params_format (arr, TRUE);
    app_net_params_free (arr);

    g_assert_cmpstr (value, ==, "?foo=bar&baz=boz");
    g_free (value);
}

static void
_app_net_params_format_strings_with_escape(void)
{
    gchar *value;
    GArray *arr;

    arr = app_net_params_new ();
    app_net_params_add_string (arr, "foo", "bar&baz");
    app_net_params_add_string (arr, "boz", "bort");
    value = app_net_params_format (arr, TRUE);
    app_net_params_free (arr);

    g_assert_cmpstr (value, ==, "?foo=bar%26baz&boz=bort");
    g_free (value);
}

static void
_app_net_params_format_int64(void)
{
    gchar *value;
    GArray *arr;

    arr = app_net_params_new ();
    app_net_params_add_int64 (arr, "foo", G_GINT64_CONSTANT(123));
    app_net_params_add_int64 (arr, "bar", G_GINT64_CONSTANT(456));
    value = app_net_params_format (arr, TRUE);
    app_net_params_free (arr);

    g_assert_cmpstr (value, ==, "?foo=123&bar=456");
    g_free (value);
}

static void
_app_net_params_format_mixed(void)
{
    gchar *value;
    GArray *arr;

    arr = app_net_params_new ();
    app_net_params_add_int64 (arr, "foo", G_GINT64_CONSTANT(123));
    app_net_params_add_string (arr, "bar", "baz");
    value = app_net_params_format (arr, TRUE);
    app_net_params_free (arr);

    g_assert_cmpstr (value, ==, "?foo=123&bar=baz");
    g_free (value);
}

int
main (int argc, char **argv)
{
    g_type_init ();
    g_test_init (&argc, &argv, NULL);

    g_test_add_func ("/appnetparams/trivial", _app_net_params_trivial);

    g_test_add_func (
        "/appnetparams/format-strings",
        _app_net_params_format_strings
    );

    g_test_add_func (
        "/appnetparams/format-strings-with-escape",
        _app_net_params_format_strings_with_escape
    );

    g_test_add_func (
        "/appnetparams/format-int64", _app_net_params_format_int64);

    g_test_add_func (
        "/appnetparams/format-mixed", _app_net_params_format_mixed);

    g_test_run ();

    return 0;
}


