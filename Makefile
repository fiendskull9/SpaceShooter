CC = gcc
RM = rm
MKDIR = mkdir
CP = cp
LN = ln

LFLAGS = `allegro-config --libs`
CFLAGS = -Wall -O3 -fomit-frame-pointer `allegro-config --cflags` #-g

SRCDIR = src
BINDIR = bin
INSTALLDIR = /opt/SpaceShooter

BINARY = SpaceShooter
GAMESDIR = /usr/games
.PHONY: all

all:
	
	$(CC) -Wall -o $(BINDIR)/$(BINARY) $(SRCDIR)/*.c $(CFLAGS) $(LFLAGS)

.PHONY: clean
clean:
	$(RM) $(BINDIR)/$(BINARY)

.PHONY: rebuild
rebuild: clean all

.PHONY: install
install:
	$(MKDIR) $(INSTALLDIR)
	$(CP) $(BINDIR)/$(BINARY) $(INSTALLDIR)
	$(CP) $(BINDIR)/$(BINARY).dat $(INSTALLDIR)
	$(LN) -s $(INSTALLDIR)/$(BINARY) $(GAMESDIR)/$(BINARY)

.PHONY: uninstall
uninstall:
	$(RM) -r $(INSTALLDIR)
	$(RM) $(GAMESDIR)/$(BINARY)

.PHONY: help
help:
	@echo "Makefile targets:"
	@echo ""
	@echo "    all       :  build project (default)"
	@echo "    clean     :  remove generated files"
	@echo "    rebuild   :  clean and build"
	@echo "    install   :  install project to local filesystem"
	@echo "    uninstall :  remove project from local filesystem"
	@echo "    help      :  print this message"
