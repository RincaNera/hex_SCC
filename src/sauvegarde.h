#ifndef HEX_SCC_SAUVEGARDE_H
#define HEX_SCC_SAUVEGARDE_H

#include "plateau.h"
#include "dirent.h"

bool save_sauvegarder(Plateau p, bool tourJ1, char* fichier, int mode);

int save_charger(Plateau* p, bool* tour, char* fichier, int* mode);

#endif //HEX_SCC_SAUVEGARDE_H
