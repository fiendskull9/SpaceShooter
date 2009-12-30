CC = gcc
RM = rm

LFLAGS = `allegro-config --libs`
CFLAGS = -Wall -O3 -fomit-frame-pointer `allegro-config --cflags`

SRCDIR = src
BINDIR = bin

BINARY = SpaceShooter

all:
	
	$(CC) -Wall -o $(BINDIR)/$(BINARY) $(SRCDIR)/*.c $(CFLAGS) $(LFLAGS)

clean:
	$(RM) $(BINDIR)/$(BINARY)

rebuild: clean all

install:
	@echo "Sorry, not yet implemented."

uninstall:
	@echo "Sorry, not yet implemented."
