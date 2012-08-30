AC_INIT([libappnet],[0.0.4-SNAPSHOT],[github@tomlee.co])
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([1.9 foreign])

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_LIBTOOL

m4_ifdef([GTK_DOC_CHECK],[
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC],false)
])

GOBJECT_INTROSPECTION_CHECK([1.30.0])
MIN_GOBJECT_VERSION=2.24.0
MIN_LIBSOUP_VERSION=2.30.0
MIN_JANSSON_VERSION=2.3.0
#
# Old versions of jansson had interesting version numbers.
#
FALLBACK_JANSSON_VERSION=2.1

PKG_PROG_PKG_CONFIG

PKG_CHECK_MODULES([GOBJECT],[gobject-2.0 >= $MIN_GOBJECT_VERSION],[],
                  [AC_MSG_ERROR([need gobject-2.0 >= $MIN_GOBJECT_VERSION])])
AC_SUBST([MIN_GOBJECT_VERSION])
AC_SUBST([GOBJECT_CFLAGS])
AC_SUBST([GOBJECT_LIBS])

PKG_CHECK_MODULES([LIBSOUP],[libsoup-2.4 >= $MIN_LIBSOUP_VERSION],[],
                  [AC_MSG_ERROR([need libsoup-2.4 >= $MIN_LIBSOUP_VERSION])])
AC_SUBST([MIN_LIBSOUP_VERSION])
AC_SUBST([LIBSOUP_CFLAGS])
AC_SUBST([LIBSOUP_LIBS])

PKG_CHECK_MODULES([JANSSON],[jansson >= $MIN_JANSSON_VERSION],[],
                  [MIN_JANSSON_VERSION=$FALLBACK_JANSSON_VERSION
                   AC_MSG_WARN([falling back to jansson $MIN_JANSSON_VERSION])
                   PKG_CHECK_MODULES([JANSSON],[jansson >= $MIN_JANSSON_VERSION],[],
                                     [AC_MSG_ERROR([need jansson >= $MIN_JANSSON_VERSION])])])
AC_SUBST([MIN_JANSSON_VERSION])
AC_SUBST([JANSSON_CFLAGS])
AC_SUBST([JANSSON_LIBS])

AC_PROG_CC

AC_CONFIG_FILES([Makefile
                 example/Makefile
                 libappnet/Makefile
                 test/Makefile
                 docs/reference/libappnet/Makefile
                 docs/reference/libappnet/libappnet-docs.sgml
                 libappnet.pc])

AC_OUTPUT

