#ifndef _APPNETHTTPRESPONSE_H_INCLUDED_
#define _APPNETHTTPRESPONSE_H_INCLUDED_

#include <glib-object.h>

#define APP_NET_TYPE_HTTP_RESPONSE (app_net_http_response_get_type ())
#define APP_NET_HTTP_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), APP_NET_TYPE_HTTP_RESPONSE, AppNetHttpResponse))
#define APP_NET_HTTP_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), APP_NET_TYPE_HTTP_RESPONSE, AppNetHttpResponseClass))
#define APP_NET_IS_HTTP_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), APP_NET_TYPE_HTTP_RESPONSE))
#define APP_NET_IS_HTTP_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), APP_NET_TYPE_HTTP_RESPONSE))
#define APP_NET_HTTP_RESPONSE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), APP_NET_TYPE_HTTP_RESPONSE, AppNetHttpResponseClass))

typedef struct _AppNetHttpResponse AppNetHttpResponse;
typedef struct _AppNetHttpResponseClass AppNetHttpResponseClass;

GType
app_net_http_response_get_type (void);

AppNetHttpResponse*
app_net_http_response_new (guint status, const char *body, const size_t size);

AppNetHttpResponse*
app_net_http_response_new_with_copy (guint status, const char *body, const size_t size);

guint
app_net_http_response_get_status (const AppNetHttpResponse *self);

const char*
app_net_http_response_get_body (const AppNetHttpResponse *self);

size_t
app_net_http_response_get_body_size (const AppNetHttpResponse *self);

void
app_net_http_response_copy_body (const AppNetHttpResponse *self, char **data, size_t *size);

#endif

