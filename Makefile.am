AUTOMAKE_OPTIONS = foreign

CFLAGS		=-Wall -I/usr/include -O3 -fomit-frame-pointer
LDFLAGS		=-L/usr/lib -lalleg-4.2.2

name 		= spaceshooter
bin_PROGRAMS 	= $(name)

# Install DAT file
EXTRA_DIST 	= data/SpaceShooter.dat
datdir 		= $(datadir)/$(name)
dat_DATA    	= data/SpaceShooter.dat

spaceshooter_SOURCES = src/user_data.c src/enemies.c src/player.c src/SpaceShooter.c
