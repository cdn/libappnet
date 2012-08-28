TESTS = test_appnetclient test_appnetparams

dist_noinst_HEADERS = appnetstubhttpprovider.h
dist_noinst_DATA = data/appnetclient_add-post \
				   data/appnetclient_timeline

check_PROGRAMS = $(TESTS)
test_appnetclient_SOURCES = test_appnetclient.c appnetstubhttpprovider.c
test_appnetclient_CFLAGS = -Wall -Werror -I$(top_srcdir)/libappnet @GOBJECT_CFLAGS@
test_appnetclient_LDADD = $(top_builddir)/libappnet/libappnet.la

test_appnetparams_SOURCES = test_appnetparams.c
test_appnetparams_CFLAGS = -Wall -Werror -I$(top_srcdir)/libappnet @GOBJECT_CFLAGS@
test_appnetparams_LDADD = $(top_builddir)/libappnet/libappnet.la

