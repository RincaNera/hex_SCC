CC  = gcc
SYS = -Wall -pedantic -std=c99
INC = -I.

EXEC = hex

SRCDIR = src
BINDIR = bin
OBJDIR = obj
FILESDIR = fichiers

OBJ_JEU   = jeu.o
OBJ_COORD = coordonnee.o
OBJ_PION  = pion.o
OBJ_PLAT  = plateau.o
OBJ_SAVE  = sauvegarde.o
OBJ_MAIN = main.o

OBJ_COMMON = $(OBJ_JEU) $(OBJ_COORD) $(OBJ_PION) $(OBJ_PLAT) $(OBJ_SAVE) $(OBJ_MAIN)


# Mode NC, pas de controle de flux, ni reprise sur erreurs
# ---------------------------------------------------------
all: $(OBJ_COMMON)
	$(CC) -o $(BINDIR)/$(EXEC) $(OBJ_COMMON)
	mv *.o $(OBJDIR)/

# '%' matches filename
# $@  for the pattern-matched target
# $<  for the pattern-matched dependency	
%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(SYS) $(INC)

clean:
	rm -f *.o
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/* $(FILESDIR)/out.*
	

