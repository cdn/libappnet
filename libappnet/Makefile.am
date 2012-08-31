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
libappnet_la_CFLAGS = -Wall -Werror -I$(srcdir) @GOBJECT_CFLAGS@ @LIBSOUP_CFLAGS@ @JANSSON_CFLAGS@
libappnet_la_LIBADD = @GOBJECT_LIBS@ @LIBSOUP_LIBS@ @JANSSON_LIBS@

$(srcdir)/appnet/appnet.h:
	$(top_srcdir)/script/make-appnet-h $(srcdir) >$(srcdir)/appnet/appnet.h

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --warn-all
INTROSPECTION_COMPILER_ARGS = \
							  --includedir=$(srcdir) \
							  --includedir=.
if HAVE_INTROSPECTION
introspection_files = \
  $(filter-out %private.h appnet/appnet.h appnet/appnetparams.h, $(nobase_include_HEADERS)) \
  $(libappnet_la_SOURCES)

AppNet-1.0.gir: $(INTROSPECTION_SCANNER) libappnet.la Makefile
AppNet_1_0_gir_SCANNERFLAGS = \
		--c-include "appnet/appnet.h"
#
# Fixes KeyError in GI scripts when GObject is missing...
#
AppNet_1_0_gir_INCLUDES = GObject-2.0
AppNet_1_0_gir_CFLAGS = $(AM_CPPFLAGS) -I$(srcdir) @GOBJECT_CFLAGS@
#
# XXX is there a way not to hard-code this?
#
AppNet_1_0_gir_LIBS = libappnet.la
AppNet_1_0_gir_FILES = $(introspection_files)
AppNet_1_0_gir_EXPORT_PACKAGES = libappnet
INTROSPECTION_GIRS += AppNet-1.0.gir

girdir=$(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibsdir=$(libdir)/girepository-1.0
typelibs_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES = $(gir_DATA) $(typelibs_DATA)

endif

