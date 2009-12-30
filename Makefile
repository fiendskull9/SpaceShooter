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

release:
	@echo "Sorry, not yet implemented."

help:
	@echo "Makefile targets:"
	@echo ""
	@echo "    all       :  build project (default)"
	@echo "    clean     :  remove generated files"
	@echo "    rebuild   :  clean and build"
	@echo "    install   :  install project to local filesystem"
	@echo "    uninstall :  remove project from local filesystem"
	@echo "    release   :  build source tarfile"
	@echo "    help      :  print this message"
