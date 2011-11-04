# SpaceShooter Makefile
# Copyright (C) 2066 Alessandro Ghedini <al3xbio@gmail.com>
# This file is released under the 3 clause BSD license, see COPYING

RM=rm
RMDIR=rmdir
MKDIR=mkdir
INSTALL=install

CFLAGS+=-Wall -pedantic -O3 -fPIE
LDFLAGS=

# glfw
CFLAGS+= $(shell pkg-config --cflags libglfw)
LDFLAGS+= $(shell pkg-config --libs libglfw)

# sndfile
CFLAGS+=$(shell pkg-config --cflags sndfile)
LDFLAGS+=$(shell pkg-config --libs sndfile)

# openal
CFLAGS+=$(shell pkg-config --cflags openal)
LDFLAGS+=$(shell pkg-config --libs openal)

# freetype2
CFLAGS+=$(shell pkg-config --cflags freetype2)
LDFLAGS+=$(shell pkg-config --libs freetype2)

PREFIX?=/usr/local
BINDIR?=$(DESTDIR)$(PREFIX)/games
MANDIR?=$(DESTDIR)$(PREFIX)/share/man/man6

OBJS=src/sound.o src/player.o src/image.o src/foes.o src/main.o src/debug.o src/background.o src/window.o src/text.o

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

src/background.o: src/background.c \
	src/image.h \
	src/window.h
src/debug.o: src/debug.c
src/foes.o: src/foes.c \
	src/debug.h \
	src/foes.h \
	src/player.h \
	src/sound.h \
	src/image.h \
	src/window.h
src/image.o: src/image.c \
	src/debug.h
src/main.o: src/main.c \
	src/background.h \
	src/debug.h \
	src/foes.h \
	src/player.h \
	src/sound.h \
	src/text.h \
	src/image.h \
	src/window.h
src/player.o: src/player.c \
	src/debug.h \
	src/foes.h \
	src/player.h \
	src/sound.h \
	src/image.h \
	src/window.h
src/sound.o: src/sound.c \
	src/debug.h
src/text.o: src/text.c
src/window.o: src/window.c \
	src/debug.h

