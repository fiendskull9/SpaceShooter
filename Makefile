# SpaceShooter Makefile
# Copyright (C) 2066 Alessandro Ghedini <al3xbio@gmail.com>
# This file is released under the 3 clause BSD license, see COPYING

RM=rm
RMDIR=rmdir
MKDIR=mkdir
INSTALL=install

CFLAGS+=-Wall -pedantic -O3 -fPIE `pkg-config --cflags libglfw`
LDFLAGS=`pkg-config --libs libglfw`

PREFIX?=/usr/local
BINDIR?=$(DESTDIR)$(PREFIX)/games
MANDIR?=$(DESTDIR)$(PREFIX)/share/man/man6

OBJS=src/main.o src/player.o src/texture.o src/window.o

.PHONY: all install uninstall clean

all: spaceshooter

spaceshooter: $(OBJS)
	$(CC) $(CFLAGS) -o spaceshooter $(OBJS) $(LDFLAGS)

install: all
	mkdir -p $(BINDIR) $(MANDIR)
	$(INSTALL) -m 4755 -o 0 -g 0 spaceshooter $(BINDIR)/spaceshooter
	gzip -9 --stdout < man/spaceshooter.6 > man/spaceshooter.6.gz
	$(INSTALL) -m 0644 -o 0 -g 0 man/spaceshooter.6.gz $(MANDIR)/spaceshooter.6.gz

uninstall:
	$(RM) -f $(BINDIR)/spaceshooter
	$(RM) -f $(MANDIR)/spaceshooter.6.gz

clean:
	$(RM) -rf spaceshooter src/*.o
	$(RM) -rf man/spaceshooter.6.gz

src/main.o: src/main.c \
	src/player.h \
	src/window.h
src/player.o: src/player.c \
	src/player.h \
	src/texture.h
src/texture.o: src/texture.c
src/window.o: src/window.c
