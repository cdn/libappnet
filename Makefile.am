ACLOCAL_AMFLAGS = -I m4
DISTCHECK_CONFIGURE_FLAGS=--enable-gtk-doc

SUBDIRS = . libappnet test docs/reference/libappnet

dist_noinst_SCRIPTS = script/make-appnet-h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libappnet.pc

clean-local:
	- rm -f *.tar.gz

