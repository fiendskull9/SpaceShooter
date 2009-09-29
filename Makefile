INCLUDEALLEGCFLAGS = `allegro-config --cflags`
INCLUDEALLEGLIBS = `allegro-config --libs`
SRCDIR = src

all:
	gcc -Wall -o SpaceShooter $(SRCDIR)/main.c $(INCLUDEALLEGCFLAGS) $(INCLUDEALLEGLIBS) 
