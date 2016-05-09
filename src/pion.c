#include <stdlib.h>
#include <assert.h>
#include "pion.h"
#include "plateau.h"

#define __USE_MISC 1
#include <math.h>

struct pion_s {
    Coordonnee coord;
    int couleur;
};

Pion pion_init() {
    Pion p = (Pion)malloc(sizeof(struct pion_s));
    assert(p != NULL);
    p->coord = coord_init();
    p->couleur = 0;
    return p;
}

Pion pion_set(Pion p, Coordonnee coord, int couleur) {
    assert(couleur == ROUGE || couleur == BLEU);
    p = pion_set_couleur(p, couleur);
    p = pion_set_coord(p, coord);
    return p;
}

Pion pion_set2(Pion p, unsigned int x, unsigned int y, int couleur) {
    p = pion_set_couleur(p, couleur);
    p = pion_set_coord2(p, x, y);
    return p;
}

Pion pion_set_couleur(Pion p, int c) {
    if (c == ROUGE || c == BLEU)
        p->couleur = c;
    return p;
}

int pion_get_couleur(Pion p) {
    return p->couleur;
}

Pion pion_set_coord(Pion p, Coordonnee coord) {
    free(p->coord);
    p->coord = coord;
    return p;
}

Pion pion_set_coord2(Pion p, unsigned int x, unsigned int y) {
    p->coord = coord_set_x(p->coord, x);
    p->coord = coord_set_y(p->coord, y);
    return p;
}

Coordonnee pion_get_coord(Pion p) {
    return p->coord;
}

void pion_destroy(Pion *pion) {
    if (*pion != NULL) {
        coord_destroy(&(*pion)->coord);
        free(*pion);
        *pion = NULL;
    }
}
