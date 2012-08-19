#ifndef _APPNETHTTPREQUEST_H_INCLUDED_
#define _APPNETHTTPREQUEST_H_INCLUDED_

#include <glib-object.h>

#define APP_NET_TYPE_HTTP_REQUEST (app_net_http_request_get_type ())
#define APP_NET_HTTP_REQUEST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), APP_NET_TYPE_HTTP_REQUEST, AppNetHttpRequest))
#define APP_NET_HTTP_REQUEST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), APP_NET_TYPE_HTTP_REQUEST, AppNetHttpRequestClass))
#define APP_NET_IS_HTTP_REQUEST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), APP_NET_TYPE_HTTP_REQUEST))
#define APP_NET_IS_HTTP_REQUEST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), APP_NET_TYPE_HTTP_REQUEST))
#define APP_NET_HTTP_REQUEST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), APP_NET_TYPE_HTTP_REQUEST, AppNetHttpRequestClass))

typedef struct _AppNetHttpRequest AppNetHttpRequest;
typedef struct _AppNetHttpRequestClass AppNetHttpRequestClass;

typedef struct _AppNetHttpRequestHeader {
    gchar *name;
    gchar *value;
} AppNetHttpRequestHeader;

GType
app_net_http_request_get_type (void);

AppNetHttpRequest*
app_net_http_request_new (const gchar *method, const gchar *url);

void
app_net_http_request_add_header (
    AppNetHttpRequest *self, const gchar *name, const gchar *value);

GList *
app_net_http_request_get_headers (const AppNetHttpRequest *self);

void
app_net_http_request_set_body (
    AppNetHttpRequest *self, const guint8 *body, size_t size);

const gchar *
app_net_http_request_get_method (const AppNetHttpRequest *self);

const gchar *
app_net_http_request_get_url (const AppNetHttpRequest *self);

const guint8 *
app_net_http_request_get_body (const AppNetHttpRequest *self);

size_t
app_net_http_request_get_body_size (const AppNetHttpRequest *self);

#endif

