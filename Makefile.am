ACLOCAL_AMFLAGS = -I m4

SUBDIRS = . test

nobase_include_HEADERS = appnet/appnetclient.h \
						  appnet/appnethttpprovider.h \
						  appnet/appnetsouphttpprovider.h \
						  appnet/appnethttprequest.h \
						  appnet/appnethttpresponse.h \
						  appnet/appnetpost.h \
						  appnet/appnet.h

dist_noinst_HEADERS = appnet/appnetpost-private.h

dist_noinst_SCRIPTS = script/make-appnet-h

lib_LTLIBRARIES = libappnet.la
libappnet_la_SOURCES = appnetclient.c \
					   appnetpost.c \
					   appnethttpprovider.c \
					   appnethttprequest.c \
					   appnethttpresponse.c \
					   appnetsouphttpprovider.c
libappnet_la_CFLAGS = -Wall -Werror -I$(top_srcdir) @GOBJECT_CFLAGS@ @LIBSOUP_CFLAGS@ @JANSSON_CFLAGS@
libappnet_la_LIBADD = @GOBJECT_LIBS@ @LIBSOUP_LIBS@ @JANSSON_LIBS@

appnet/appnet.h: appnet
	script/make-appnet-h >appnet/appnet.h

