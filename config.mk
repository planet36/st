# st version
VERSION = 0.8.4
VERSION := $(VERSION)-sdw

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# includes and libs
INCS = \
       `pkg-config --cflags fontconfig freetype2 x11 xft`
LIBS = -lutil \
       `pkg-config --libs fontconfig freetype2 x11 xft`

# flags
CFLAGS += \
		-Wno-float-equal \
		-Wno-shadow \
		-Wno-sign-compare \
		-Wno-switch-default \
		-Wno-type-limits \
		-Wno-unused-parameter \
		-Os
CPPFLAGS += -DVERSION=\"$(VERSION)\" -D_XOPEN_SOURCE=600
CFLAGS += $(INCS) $(CPPFLAGS)
LDFLAGS += $(LIBS)
