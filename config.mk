# st version
VERSION = 0.9
VERSION := $(shell git describe --tags --abbrev=0)-planet36

# Customize below to fit your system

# paths
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man

# includes and libs
INCS = `pkg-config --cflags xft`
LIBS = `pkg-config --libs   fontconfig x11 xft`

# flags
CPPFLAGS += -DVERSION=\"$(VERSION)\" -D_XOPEN_SOURCE=600 $(INCS)
DEPFLAGS += -MMD -MP
CFLAGS += -O2 \
		-Wno-shadow \
		-Wno-sign-compare \
		-Wno-switch-default \
		-Wno-type-limits \
		-Wno-unused-parameter
LDLIBS += $(LIBS)
