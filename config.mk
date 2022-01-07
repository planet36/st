# st version
VERSION = 0.8.5
VERSION := $(VERSION)-sdw

# Customize below to fit your system

# paths
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man

# includes and libs
INCS = `pkg-config --cflags fontconfig freetype2 x11 xft`
LIBS = `pkg-config --libs   fontconfig freetype2 x11 xft` -lutil

# flags
CPPFLAGS += -DVERSION=\"$(VERSION)\" -D_DEFAULT_SOURCE $(INCS)
DEPFLAGS += -MMD -MP
CFLAGS += -O2 \
		-Wno-float-equal \
		-Wno-shadow \
		-Wno-sign-compare \
		-Wno-switch-default \
		-Wno-type-limits \
		-Wno-unused-parameter
LDLIBS += $(LIBS)
