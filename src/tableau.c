#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "tableau.h"

#define TAILLE 8

struct tab_s {
    Pion* tab;
    unsigned int taille;
    unsigned int max;
};

DynTab tab_init() {
    DynTab dt = (DynTab)malloc(sizeof(struct tab_s));
    assert(dt != NULL);
    dt->taille = 0;
    dt->max = TAILLE;
    dt->tab = (Pion*)malloc(sizeof(Pion)*TAILLE);
    assert(dt->tab != NULL);
    for (int i = 0; i < TAILLE; i++)
        dt->tab[i] = NULL;
    return dt;
}

void tab_destroy(DynTab dt) {
    assert(dt != NULL);
    free(dt->tab);
    free(dt);
}

DynTab tab_add(DynTab dt, Pion p) {
    assert(dt != NULL && p != NULL);
    Pion elt = dt->tab[0];
    int i = 0;
    while (elt != NULL && i < dt->taille) {
        if (elt == p)
            return dt;
        elt = dt->tab[++i];
    }
    if (dt->taille == dt->max-1) {
        dt->max += TAILLE;
        dt->tab = (Pion *) realloc(dt->tab, sizeof(Pion) * (dt->max));
    }
    dt->tab[dt->taille] = p;
    dt->taille++;
    return dt;
}

Pion tab_get_pion(DynTab dt, unsigned int i) {
    assert(dt != NULL);
    if (i <= dt->taille)
        return dt->tab[i];
    else
        return NULL;
}

unsigned int tab_get_max(DynTab dt) {
    assert(dt != NULL);
    return dt->max;
}

unsigned int tab_get_taille(DynTab dt) {
    assert(dt != NULL);
    return dt->taille;
}
