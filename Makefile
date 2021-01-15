# st - simple terminal
# See LICENSE file for copyright and license details.

include config.mk

HDRS = $(filter-out config.def.h, config.h $(wildcard *.h))
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: options st

options:
	@echo st build options:
	@echo "CFLAGS  = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo "CC      = $(CC)"

config.h:
	cp config.def.h config.h

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(OBJS): config.mk $(HDRS)

st: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f st *.o st-$(VERSION).tar.xz

dist:
	git archive --prefix st-$(VERSION)/ HEAD | xz > st-$(VERSION).tar.xz

install: st
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f st $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/st
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < st.1 > $(DESTDIR)$(MANPREFIX)/man1/st.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/st.1
	tic -sx st.info
	@echo Please see the README file regarding the terminfo entry of st.

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/st \
		$(DESTDIR)$(MANPREFIX)/man1/st.1

.PHONY: all options clean dist install uninstall
