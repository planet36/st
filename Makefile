# st - simple terminal
# See LICENSE file for copyright and license details.

include config.mk

SRCS = $(wildcard *.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

BIN = st

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(OBJS): config.h config.mk

config.h:
	cp config.def.h config.h

options:
	@echo $(BIN) build options:
	@echo "CFLAGS  = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo "CC      = $(CC)"

clean:
	@$(RM) --verbose -- $(BIN) $(OBJS) $(DEPS) $(BIN)-$(VERSION).tar.xz

dist:
	git archive --prefix $(BIN)-$(VERSION)/ HEAD | xz > $(BIN)-$(VERSION).tar.xz

install: $(BIN)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f $(BIN) $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/$(BIN)
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < $(BIN).1 > $(DESTDIR)$(MANPREFIX)/man1/$(BIN).1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/$(BIN).1
	tic -sx $(BIN).info
	@echo Please see the README file regarding the terminfo entry of $(BIN).

uninstall:
	@$(RM) $(DESTDIR)$(PREFIX)/bin/$(BIN) \
		$(DESTDIR)$(MANPREFIX)/man1/$(BIN).1

.PHONY: options clean dist install uninstall

-include $(DEPS)
