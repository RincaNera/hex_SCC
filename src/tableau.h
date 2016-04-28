#ifndef HEX_SCC_TABLEAU_H
#define HEX_SCC_TABLEAU_H

#include "pion.h"

typedef struct tab_s* DynTab;

DynTab tab_init();

void tab_destroy(DynTab dt);

DynTab tab_add(DynTab dt, Pion p);

Pion tab_get_pion(DynTab dt, unsigned int i);

unsigned int tab_get_max(DynTab dt);

unsigned int tab_get_taille(DynTab dt);

#endif //HEX_SCC_TABLEAU_H
