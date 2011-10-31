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
CFLAGS+= `pkg-config --cflags libglfw`
LDFLAGS+= `pkg-config --libs libglfw`

# sndfile
CFLAGS+=`pkg-config --cflags sndfile`
LDFLAGS+=`pkg-config --libs sndfile`

# openal
CFLAGS+=`pkg-config --cflags openal`
LDFLAGS+=`pkg-config --libs openal`

# freetype2
CFLAGS+=`pkg-config --cflags freetype2`
LDFLAGS+=`pkg-config --libs freetype2`

PREFIX?=/usr/local
BINDIR?=$(DESTDIR)$(PREFIX)/games
MANDIR?=$(DESTDIR)$(PREFIX)/share/man/man6

OBJS=src/background.o src/debug.o src/foes.o src/main.o src/player.o src/sound.o src/text.o src/texture.o src/window.o

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
	src/texture.h \
	src/window.h
src/debug.o: src/debug.c
src/foes.o: src/foes.c \
	src/debug.h \
	src/foes.h \
	src/player.h \
	src/sound.h \
	src/texture.h \
	src/window.h
src/main.o: src/main.c \
	src/background.h \
	src/debug.h \
	src/foes.h \
	src/player.h \
	src/sound.h \
	src/text.h \
	src/window.h
src/player.o: src/player.c \
	src/debug.h \
	src/foes.h \
	src/sound.h \
	src/texture.h \
	src/window.h
src/sound.o: src/sound.c \
	src/debug.h
src/text.o: src/text.c
src/texture.o: src/texture.c \
	src/debug.h
src/window.o: src/window.c \
	src/debug.h
