AUTOMAKE_OPTIONS = foreign

CFLAGS		=-Wall -I/usr/include -O3 -fomit-frame-pointer
LDFLAGS		=-L/usr/lib -lalleg-4.2.2

name 		= spaceshooter
bin_PROGRAMS 	= $(name)

EXTRA_DIST 	= data/SpaceShooter.dat man/spaceshooter.1

include_HEADERS = src/timers.h src/enemies.h src/player.h src/SpaceShooter.h src/data.h

# Install DAT file
datdir 		= $(datadir)/$(name)
dat_DATA    	= data/SpaceShooter.dat

# Man page
man1_MANS	= man/spaceshooter.1

spaceshooter_SOURCES = src/timers.c src/user_data.c src/enemies.c src/player.c src/SpaceShooter.c
