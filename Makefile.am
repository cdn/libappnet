ACLOCAL_AMFLAGS = -I m4

SUBDIRS = . test

lib_LTLIBRARIES = libappnet.la
libappnet_la_SOURCES = appnetclient.c \
					   appnetpost.c \
					   appnethttpprovider.c \
					   appnethttprequest.c \
					   appnethttpresponse.c \
					   appnetsouphttpprovider.c
libappnet_la_CFLAGS = -Wall -Werror @GOBJECT_CFLAGS@ @LIBSOUP_CFLAGS@ @JANSSON_CFLAGS@
libappnet_la_LIBADD = @GOBJECT_LIBS@ @LIBSOUP_LIBS@ @JANSSON_LIBS@

