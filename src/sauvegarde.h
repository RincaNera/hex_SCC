#ifndef HEX_SCC_SAUVEGARDE_H
#define HEX_SCC_SAUVEGARDE_H

#include "plateau.h"

bool save_sauvegarder(Plateau p, bool tourJ1, char* fichier);

bool save_charger(Plateau* p, bool* tour, char* fichier);

#endif //HEX_SCC_SAUVEGARDE_H
