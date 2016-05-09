CC  = gcc
SYS = -g -Wall -std=c99
SDL = `sdl-config --cflags --libs` -lSDL_ttf -lSDL_image
INC = -I.

EXEC = hex

SRCDIR = src
BINDIR = bin
OBJDIR = obj

OBJ_IA = IA.o
OBJ_COORD = coordonnee.o
OBJ_PION  = pion.o
OBJ_PLAT  = plateau.o
OBJ_SAVE  = sauvegarde.o
OBJ_TAB   = tableau.o
OBJ_INIT  = initialisation.o
OBJ_IMG   = image.o
OBJ_ITEM  = menuItem.o
OBJ_DISP  = display.o
OBJ_MENU  = menu.o
OBJ_MAIN  = main.o
OBJ_JEU   = jeu.o

OBJ_COMMON = $(OBJ_IA) $(OBJ_MENU) $(OBJ_JEU) $(OBJ_COORD) $(OBJ_DISP) $(OBJ_PION) $(OBJ_PLAT) $(OBJ_SAVE) $(OBJ_TAB) $(OBJ_INIT) $(OBJ_IMG) $(OBJ_ITEM) $(OBJ_MAIN)

all: $(OBJ_COMMON)
	$(CC) -o $(BINDIR)/$(EXEC) $(OBJ_COMMON) $(SDL)
	mv *.o $(OBJDIR)/

# '%' matches filename
# $@  for the pattern-matched target
# $<  for the pattern-matched dependency	
%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(SYS)

clean:
	rm -f *.o
	rm -f $(OBJDIR)/*.o
	

