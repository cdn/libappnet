#ifndef _APPNETPARAMS_H_INCLUDED_
#define _APPNETPARAMS_H_INCLUDED_

#include <glib.h>

GArray *
app_net_params_new (void);

void
app_net_params_free (GArray *arr);

void
app_net_params_add_string (GArray *arr, const gchar *name, const gchar *value);

void
app_net_params_add_int64 (GArray *arr, const gchar *name, gint64 value);

gchar*
app_net_params_format (const GArray *arr, gboolean query_string);

#endif

