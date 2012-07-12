## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	$(WX_CXXFLAGS) \
	$(UPSCLIENT_CFLAGS)\
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall \
	 -g \
	 $(WX_CPPFLAGS)

bin_PROGRAMS = hazelnut

hazelnut_SOURCES = \
	app.cpp \
	app.hpp \
	task-bar-icon.cpp \
	task-bar-icon.hpp \
	config-dialog.cpp \
	config-dialog.hpp \
	device.cpp \
	device.hpp

hazelnut_LDFLAGS = 

hazelnut_LDADD = \
	$(UPSCLIENT_LIBS) \
	$(WX_LIBS)

