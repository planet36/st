# st version
VERSION = 0.9.3

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
CPPFLAGS = -MMD -MP
CPPFLAGS += -DVERSION=\"$(VERSION)\" -D_XOPEN_SOURCE=600 $(INCS)

CFLAGS = -std=c23
CFLAGS += -pipe -Wall -Wextra -Wpedantic -Wfatal-errors
CFLAGS += -O3 -flto=auto -march=native
CFLAGS += -Wno-shadow
CFLAGS += -Wno-sign-compare
CFLAGS += -Wno-switch-default
CFLAGS += -Wno-type-limits
CFLAGS += -Wno-unused-parameter

LDLIBS = $(LIBS)
