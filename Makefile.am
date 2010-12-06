AUTOMAKE_OPTIONS = foreign

CFLAGS		=-Wall -I/usr/include -O3 -fomit-frame-pointer
LDFLAGS		=-L/usr/lib -lalleg-4.2.2

name 		= spaceshooter
bin_PROGRAMS 	= $(name)

EXTRA_DIST 	= data/* man/spaceshooter.6

noinst_HEADERS  = src/*.h src/game_data.h src/enemies.h src/screen.h src/timers.h src/debug.h src/player.h src/sound.h src/user_data.h

# Install DAT file
datdir 		= $(datadir)/$(name)
dat_DATA    	= data/*

# Man page
man6_MANS	= man/spaceshooter.6

spaceshooter_SOURCES = src/game_data.c src/enemies.c src/player.c src/sound.c src/user_data.c src/debug.c src/main.c src/screen.c  src/timers.c
