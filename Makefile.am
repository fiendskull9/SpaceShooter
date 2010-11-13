AUTOMAKE_OPTIONS = foreign

CFLAGS		=-Wall -I/usr/include -O3 -fomit-frame-pointer
LDFLAGS		=-L/usr/lib -lalleg-4.2.2

name 		= spaceshooter
bin_PROGRAMS 	= $(name)

EXTRA_DIST 	= data/SpaceShooter.dat man/spaceshooter.6

noinst_HEADERS  = src/config.h src/dat.h src/enemies.h src/screen.h src/timers.h src/data.h src/debug.h src/player.h src/sound.h src/user_data.h

# Install DAT file
datdir 		= $(datadir)/$(name)
dat_DATA    	= data/SpaceShooter.dat

# Man page
man6_MANS	= man/spaceshooter.6

spaceshooter_SOURCES = src/dat.c src/enemies.c src/player.c src/sound.c src/user_data.c src/debug.c src/main.c src/screen.c  src/timers.c
