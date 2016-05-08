#ifndef HEX_SCC_SAUVEGARDE_H
#define HEX_SCC_SAUVEGARDE_H

#include "plateau.h"
#include "dirent.h"

bool save_sauvegarder(Plateau p, bool tourJ1, char* fichier);

char** save_page(DIR ** dir, int page);

char* save_file(struct dirent* dir, int page, int n);

int save_charger(Plateau* p, bool* tour, char* fichier);

#endif //HEX_SCC_SAUVEGARDE_H
