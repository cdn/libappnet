#include <glib-object.h>
#include <string.h>

#include "appnet/appnetparams.h"

typedef struct _AppNetParam {
    gchar  name[64];
    GValue value;
} AppNetParam;

GArray *
app_net_params_new (void)
{
    return g_array_new (FALSE, FALSE, sizeof(AppNetParam));
}

void
app_net_params_free (GArray *arr)
{
    guint i;

    for (i = 0; i < arr->len; i++) {
        AppNetParam *param = ((AppNetParam *)arr->data) + i;
        g_value_unset (&param->value);
    }
    
    g_array_free (arr, TRUE);
}

void
app_net_params_add_string (
    GArray *arr, const gchar *name, const gchar *value)
{
    AppNetParam param;

    memset (&param.value, 0, sizeof(param.value));

    g_strlcpy (param.name, name, sizeof(param.name));
    g_value_init (&param.value, G_TYPE_STRING);
    g_value_set_string (&param.value, value);
    g_array_append_val (arr, param);
}

void
app_net_params_add_int64 (
    GArray *arr, const gchar *name, gint64 value)
{
    AppNetParam param;

    memset (&param.value, 0, sizeof(param.value));

    g_strlcpy (param.name, name, sizeof(param.name));
    g_value_init (&param.value, G_TYPE_INT64);
    g_value_set_int64 (&param.value, value);
    g_array_append_val (arr, param);
}

gchar*
app_net_params_format (const GArray *arr, gboolean query_string)
{
    gsize size;
    guint i;
    gchar *temp;
    gchar *ptr;

    size = 0;
    for (i = 0; i < arr->len; i++) {
        gchar *escaped;
        const AppNetParam *param = ((const AppNetParam *)arr->data) + i;
        escaped = g_uri_escape_string (
            param->name, G_URI_RESERVED_CHARS_GENERIC_DELIMITERS, TRUE);
        /* +1 for '=' */
        size += strlen (escaped) + 1;
        g_free (escaped);
        if (G_VALUE_HOLDS_STRING (&param->value)) {
            const gchar *value = g_value_get_string (&param->value);
            escaped = g_uri_escape_string (
                value, G_URI_RESERVED_CHARS_GENERIC_DELIMITERS, TRUE);
            size += strlen (escaped);
        }
        else if (G_VALUE_HOLDS_INT64 (&param->value)) {
            const gint64 value = g_value_get_int64 (&param->value);
            escaped = g_strdup_printf ("%" G_GINT64_FORMAT, value);
            size += strlen (escaped);
        }
        else {
            /* TODO use GValue type transforms instead */
            g_warning ("Unsupported value type");
            continue;
        }

        g_free (escaped);

        /* +1 for '&' */
        if (i < (arr->len - 1)) size++;
    }
    if (size > 0 && query_string) size++; /* leading '?' */
    size++; /* terminating nil */

    ptr = temp = g_malloc (size);
    if (size > 1 && query_string) {
        *ptr = '?';
        ptr++;
    }
    for (i = 0; i < arr->len; i++) {
        gchar *escaped;
        size_t len;
        const AppNetParam *param = ((const AppNetParam *)arr->data) + i;

        escaped = g_uri_escape_string (
            param->name, G_URI_RESERVED_CHARS_GENERIC_DELIMITERS, TRUE);
        len = strlen(escaped);
        memcpy (ptr, escaped, len);
        ptr += len;
        g_free (escaped);

        *ptr = '=';
        ptr++;

        if (G_VALUE_HOLDS_STRING (&param->value)) {
            const gchar *value = g_value_get_string (&param->value);
            escaped = g_uri_escape_string (
                value, G_URI_RESERVED_CHARS_GENERIC_DELIMITERS, TRUE);
        }
        else if (G_VALUE_HOLDS_INT64 (&param->value)) {
            const gint64 value = g_value_get_int64 (&param->value);
            escaped = g_strdup_printf ("%" G_GINT64_FORMAT, value);
        }
        else {
            /* TODO use GValue type transforms instead */
            g_warning ("Unsupported value type");
            continue;
        }

        len = strlen (escaped);
        memcpy (ptr, escaped, len);
        ptr += len;
        g_free (escaped);

        if (i < (arr->len - 1)) {
            *ptr = '&';
            ptr++;
        }
    }
    *ptr = '\0';

    return temp;
}

