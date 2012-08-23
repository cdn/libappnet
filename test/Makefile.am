TESTS = test_appnetclient

dist_noinst_HEADERS = appnetstubhttpprovider.h
dist_noinst_DATA = data/appnetclient_add-post

check_PROGRAMS = test_appnetclient
test_appnetclient_SOURCES = test_appnetclient.c appnetstubhttpprovider.c
test_appnetclient_CFLAGS = -Wall -Werror -I$(top_srcdir) @GOBJECT_CFLAGS@
test_appnetclient_LDADD = $(top_srcdir)/libappnet.la

