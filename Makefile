# st - simple terminal
# See LICENSE file for copyright and license details.

include config.mk

SRCS = $(wildcard *.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

BIN = st

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LDLIBS)

$(OBJS): config.mk

clean:
	@$(RM) --verbose -- $(DEPS) $(OBJS) $(BIN) $(BIN)-$(VERSION).tar.xz

dist:
	git archive --prefix $(BIN)-$(VERSION)/ HEAD | xz > $(BIN)-$(VERSION).tar.xz

install: $(BIN)
	mkdir -p "$(DESTDIR)$(BINDIR)"
	cp -f $(BIN) "$(DESTDIR)$(BINDIR)"
	chmod 755 "$(DESTDIR)$(BINDIR)/$(BIN)"
	mkdir -p "$(DESTDIR)$(MANDIR)/man1"
	sed "s/VERSION/$(VERSION)/g" < $(BIN).1 > "$(DESTDIR)$(MANDIR)/man1/$(BIN).1"
	chmod 644 "$(DESTDIR)$(MANDIR)/man1/$(BIN).1"
	tic -sx $(BIN).info
	@echo Please see the README file regarding the terminfo entry of $(BIN).

uninstall:
	@$(RM) "$(DESTDIR)$(BINDIR)/$(BIN)" \
		"$(DESTDIR)$(MANDIR)/man1/$(BIN).1"

lint:
	-clang-tidy --quiet $(SRCS) -- $(CPPFLAGS) $(CFLAGS)

.PHONY: clean dist install uninstall lint

-include $(DEPS)
