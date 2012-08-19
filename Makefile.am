ACLOCAL_AMFLAGS = -I m4

SUBDIRS = . test

lib_LTLIBRARIES = libappnet.la
libappnet_la_SOURCES = appnetclient.c
libappnet_la_CFLAGS = -Wall -Werror @GOBJECT_CFLAGS@
libappnet_la_LIBADD = @GOBJECT_LIBS@

