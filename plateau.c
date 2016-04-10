#include <stdlib.h>
#include "plateau.h"

#define INDICE 11

struct plateau_s {
    Pion tab[11][11];
};

Plateau plateau_init() {
    Plateau p = (Plateau)malloc(sizeof(struct plateau_s));
    for (int i = 0; i < INDICE; i++)
        for (int j = 0; j < INDICE; j++)
            p->tab[i][j] = NULL;
    return p;
}

bool plateau_case_vide(Plateau p, Coordonnee coord) {
    return p->tab[coord_get_x(coord)][coord_get_y(coord)] == NULL;
}

bool plateau_placer_pion(Plateau* p, Pion pion) {
    Coordonnee coord = pion_get_coord(pion);
    if (!plateau_case_vide(*p,coord)) {
        (*p)->tab[coord_get_x(coord)][coord_get_y(coord)] = pion;
        return true;
    }
    return false;
}

Pion plateau_get_pion(Plateau p, Coordonnee coord) {
    return p->tab[coord_get_x(coord)][coord_get_y(coord)];
}
