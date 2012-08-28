nobase_include_HEADERS = appnet/appnetclient.h \
						  appnet/appnethttpprovider.h \
						  appnet/appnetsouphttpprovider.h \
						  appnet/appnethttprequest.h \
						  appnet/appnethttpresponse.h \
						  appnet/appnetpost.h \
						  appnet/appnetparams.h \
						  appnet/appnet.h

dist_noinst_HEADERS = appnet/appnetpost-private.h

lib_LTLIBRARIES = libappnet.la
libappnet_la_SOURCES = appnetclient.c \
					   appnetpost.c \
					   appnethttpprovider.c \
					   appnethttprequest.c \
					   appnethttpresponse.c \
					   appnetsouphttpprovider.c \
					   appnetparams.c
libappnet_la_CFLAGS = -Wall -Werror -I$(top_srcdir) @GOBJECT_CFLAGS@ @LIBSOUP_CFLAGS@ @JANSSON_CFLAGS@
libappnet_la_LIBADD = @GOBJECT_LIBS@ @LIBSOUP_LIBS@ @JANSSON_LIBS@

$(srcdir)/appnet/appnet.h:
	$(top_srcdir)/script/make-appnet-h $(srcdir) >$(srcdir)/appnet/appnet.h

