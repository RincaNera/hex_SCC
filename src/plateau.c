#include <stdlib.h>
#include <assert.h>
#include "plateau.h"

struct plateau_s {
    Pion tab[TAILLE][TAILLE];
};

Plateau plateau_init() {
    Plateau p = (Plateau)malloc(sizeof(struct plateau_s));
    assert(p != NULL);
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            p->tab[i][j] = NULL;
    return p;
}

bool plateau_case_vide(Plateau p, Coordonnee coord) {
    return p->tab[coord_get_x(coord)][coord_get_y(coord)] == NULL;
}

bool coup_gagnant(Plateau p, Pion pion) {
    return true;
}

// TODO: vérifier coup gagnant
int plateau_placer_pion(Plateau* p, Pion pion) {
    Coordonnee coord = pion_get_coord(pion);
    if (!plateau_case_vide(*p,coord)) {
        (*p)->tab[coord_get_x(coord)][coord_get_y(coord)] = pion;
        return 1;
    }
    return 0;
}

Pion plateau_get_pion(Plateau p, Coordonnee coord) {
    return p->tab[coord_get_x(coord)][coord_get_y(coord)];
}
