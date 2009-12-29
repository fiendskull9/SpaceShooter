INCLUDEALLEGCFLAGS = `allegro-config --cflags`
INCLUDEALLEGLIBS = `allegro-config --libs`
SRCDIR = src

all:
	gcc -Wall -o bin/SpaceShooter $(SRCDIR)/player.c $(SRCDIR)/enemies.c $(SRCDIR)/main.c $(INCLUDEALLEGCFLAGS) $(INCLUDEALLEGLIBS) 

