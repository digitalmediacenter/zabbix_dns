#
# Makefile for zabbix_dns
#
# vi:set ts=4 nu nowrap:
#

PROG=zabbix_dns
VERSION=1.2

SRCS= 	main.c

BINDIR=/etc/zabbix/externalscripts
BINOWN=root
BINGRP=root
BINMODE=0755

LDNS_CFLAGS=$(shell ldns-config --cflags)
LDNS_LDFLAGS=$(shell ldns-config --libs)

CC=gcc
CFLAGS=	-O2 -fno-strict-aliasing -pipe -march=native \
		-W -Wall -ansi -pedantic -Wbad-function-cast -Wcast-align \
		-Wcast-qual -Wchar-subscripts -Winline \
		-Wmissing-prototypes -Wnested-externs -Wpointer-arith \
		-Wredundant-decls -Wshadow -Wstrict-prototypes -Wwrite-strings \
		-std=c99 -D_GNU_SOURCE $(LDNS_CFLAGS) \
		-DVERSION="\"$(VERSION)\"" -DBUILDDATE="\"$(shell date)\""
LDFLAGS=
LDADD=$(LDNS_LDFLAGS)

ifeq ($(MAKECMDGOALS),debug)
CFLAGS+=-g
STRIP=
else
STRIP?=-s
endif

OBJS+=$(SRCS:.c=.o)

%.d: %.c
	@echo generating $@
	@$(CC) -E -MM $< | sed -e 's,:, $@:,' >$@

%.o: %.c
	@echo compiling $<
	@$(CC) -c $(CFLAGS) $(MYSQL_CFLAGS) $(GDLIB_CFLAGS) -o $@ $<

.PHONY: default all debug
default: $(PROG)
all: default
debug: $(PROG)

$(PROG): $(OBJS)
	@echo linking $@
	@$(CC) $(LDFLAGS) $(MYSQL_LDFLAGS) $(GDLIB_LDFLAGS) -o $@ $^ $(LDADD) $(MYSQL_LDADD) $(GDLIB_LDADD)

ifneq ($(MAKECMDGOALS),clean)
-include $(OBJS:.o=.d)
endif

install: $(PROG)
	install -g $(BINGRP) -m $(BINMODE) -o $(BINOWN) -d $(BINDIR)
	install $(STRIP) -g $(BINGRP) -m $(BINMODE) -o $(BINOWN) $(PROG) $(BINDIR)

.PHONY: tar.gz
tar.gz: clean
	ln -s . $(PROG)-$(VERSION)
	tar -c -z --exclude=$(PROG)-$(VERSION)/$(PROG)-$(VERSION) \
	  --exclude=$(PROG)-$(VERSION)/$(PROG)-*.tar.gz \
	  --exclude=$(PROG)-$(VERSION)/.hg \
	  -f $(PROG)-$(VERSION).tar.gz $(PROG)-$(VERSION)/* \
	  $(PROG)-$(VERSION)/.[a-zA-Z0-9]*
	rm -f $(PROG)-$(VERSION)

.PHONY: indent
indent:
	indent *.[ch]

.PHONY: clean
clean:
	rm -f $(PROG) $(OBJS) core *.core *.[ch]~ *.d

