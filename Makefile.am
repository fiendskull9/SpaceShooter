AUTOMAKE_OPTIONS = foreign

CFLAGS		=-Wall -Werror -I/usr/include -O3 -fomit-frame-pointer
LDFLAGS		=-L/usr/lib `allegro-config --libs` -pthread

bindir		= $(prefix)/games

name 		= spaceshooter
bin_PROGRAMS 	= $(name)

EXTRA_DIST 	= data/* man/spaceshooter.6 spaceshooter.desktop

noinst_HEADERS  = src/*.h src/game_data.h src/enemies.h src/screen.h src/timers.h src/debug.h src/player.h src/sound.h src/user_data.h

# Install data
gamedatadir	= $(datadir)/games/$(name)

graphicsdir	= $(gamedatadir)/graphics
graphics_DATA   = data/graphics/*

soundsdir	= $(gamedatadir)/sounds
sounds_DATA   	= data/sounds/*

desktopdir 	= $(datadir)/applications
desktop_DATA 	= spaceshooter.desktop

icondir		= $(datadir)/pixmaps
icon_DATA 	= data/spaceshooter.xpm

# Man page
man6_MANS	= man/spaceshooter.6

spaceshooter_SOURCES = src/game_data.c src/enemies.c src/player.c src/sound.c src/user_data.c src/debug.c src/main.c src/screen.c  src/timers.c
