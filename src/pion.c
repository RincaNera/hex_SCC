#include <stdlib.h>
#include <assert.h>
#include "pion.h"

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
    p = pion_set_couleur(p, couleur);
    p = pion_set_coord(p, coord);
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
    p->coord = coord;
    return p;
}

Coordonnee pion_get_coord(Pion p) {
    return p->coord;
}