#include <string.h>

#include <libsoup/soup.h>

#include <appnet/appnetsouphttpprovider.h>

struct _AppNetSoupHttpProvider {
    GObject base;
    SoupSession *session;
};

struct _AppNetSoupHttpProviderClass {
    GObjectClass base;
};

static void
app_net_http_provider_iface_init (AppNetHttpProviderInterface *iface);

G_DEFINE_TYPE_WITH_CODE (AppNetSoupHttpProvider, app_net_soup_http_provider, G_TYPE_OBJECT,
        G_IMPLEMENT_INTERFACE (APP_NET_TYPE_HTTP_PROVIDER, app_net_http_provider_iface_init));

static GObject*
app_net_soup_http_provider_constructor (GType type, guint nprops, GObjectConstructParam *props)
{
    GObjectClass *gobject_class;
    gobject_class = G_OBJECT_CLASS (app_net_soup_http_provider_parent_class);
    return gobject_class->constructor (type, nprops, props);
}

static void
app_net_soup_http_provider_dispose (GObject *gobj)
{
    AppNetSoupHttpProvider *self =
        APP_NET_SOUP_HTTP_PROVIDER (gobj);
    g_object_unref (self->session);
    self->session = NULL;
}

static void
app_net_soup_http_provider_class_init (AppNetSoupHttpProviderClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    gobject_class->constructor = app_net_soup_http_provider_constructor;
    gobject_class->dispose = app_net_soup_http_provider_dispose;
}

static void
app_net_soup_http_provider_init (AppNetSoupHttpProvider *self)
{
    /* TODO add HAVE_LIBSOUP_GNOME check to configure.ac */
    /* TODO SSL certificate verification */
#ifdef HAVE_LIBSOUP_GNOME
    self->session = soup_session_sync_new_with_options (
        SOUP_SESSION_ADD_FEATURE_BY_TYPE, SOUP_TYPE_PROXY_RESOLVER_GNOME,
        NULL);
#else
    self->session = soup_session_sync_new ();
#endif
}

static gint
app_net_http_request_header_cmp (gpointer a, gpointer b)
{
    const AppNetHttpRequestHeader *header = (AppNetHttpRequestHeader *) a;
    const gchar *key = (const gchar *) b;

    return strcmp (header->name, key);
}

static void
app_net_soup_http_provider_add_header (gpointer item, gpointer user_data)
{
    const AppNetHttpRequestHeader *header = (const AppNetHttpRequestHeader *) item;
    SoupMessage *message = SOUP_MESSAGE (user_data);
    soup_message_headers_append (
        message->request_headers, header->name, header->value);
}

static AppNetHttpResponse *
app_net_soup_http_provider_send_request (AppNetHttpProvider *iface, AppNetHttpRequest *r)
{
    SoupMessage *message;
    gchar *content_type = NULL;
    AppNetHttpResponse *resp;
    GList *ptr;
    guint status;
    GList *headers = g_list_copy (app_net_http_request_get_headers (r));
    AppNetSoupHttpProvider *self = APP_NET_SOUP_HTTP_PROVIDER (iface);

    /* XXX ugly as hell. */
    ptr = g_list_find_custom (
        headers, "Content-Type",
        (GCompareFunc) app_net_http_request_header_cmp);
    if (ptr != NULL) {
        AppNetHttpRequestHeader *header =
            (AppNetHttpRequestHeader *) ptr->data;
        content_type = header->value;
        g_free (header->name);
        headers = g_list_delete_link (headers, ptr);
    }

    message = soup_message_new (
        app_net_http_request_get_method (r),
        app_net_http_request_get_url (r)
    );

    g_list_foreach (headers, app_net_soup_http_provider_add_header, message);

    if (app_net_http_request_get_body (r) != NULL) {
        const char *body = app_net_http_request_get_body (r);
        size_t body_size = app_net_http_request_get_body_size (r);
        if (content_type == NULL) {
            g_warning ("missing Content-Type header with a request body");
        }
        soup_message_set_request (
            message, content_type, SOUP_MEMORY_STATIC, body, body_size);
    }
    g_free (content_type);

    status = soup_session_send_message (self->session, message);
    resp = app_net_http_response_new_with_copy (
        status, message->response_body->data, message->response_body->length);
    g_object_unref (message);
    g_list_free (headers);
    return resp;
}

static void
app_net_http_provider_iface_init (AppNetHttpProviderInterface *iface)
{
    iface->send_request = app_net_soup_http_provider_send_request;
}

AppNetSoupHttpProvider*
app_net_soup_http_provider_new (void)
{
    return APP_NET_SOUP_HTTP_PROVIDER (g_object_new (APP_NET_TYPE_SOUP_HTTP_PROVIDER, NULL));
}

