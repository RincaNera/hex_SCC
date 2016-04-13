#ifndef HEX_SCC_SAUVEGARDE_H
#define HEX_SCC_SAUVEGARDE_H

#include "plateau.h"

typedef struct save_s* Save;

Save save_init();

Save save_set(Save s, Plateau p, bool tour);

bool save_sauvegarder(Save s, char* fichier);

bool save_charger(Plateau* p, bool* tour, char* fichier);

#endif //HEX_SCC_SAUVEGARDE_H
