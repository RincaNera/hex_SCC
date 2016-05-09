#ifndef JEU_H
#define JEU_H

#include <stdbool.h>
#include "main.h"
#include "plateau.h"

void afficher_message(Item** message, int n);

void res_placer_pion(Plateau p, int res, bool* tourJ1, Item** message, bool* game, Pion pion, int mode);

void clic_plateau(Plateau p, Curseur curseur, Item *hexBoard, unsigned int r, unsigned int h, unsigned int s,
                  bool *tourJ1, Item **message, bool *game, int mode);

#endif
