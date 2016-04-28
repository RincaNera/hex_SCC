#include <stdlib.h>
#include <assert.h>
#include "plateau.h"
#include "tableau.h"

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
    return p->tab[coord_get_y(coord)][coord_get_x(coord)] == NULL;
}

bool plateau_case_vide2(Plateau p, unsigned int x, unsigned int y) {
    assert(x < 11 && y < 11);
    return p->tab[y][x] == NULL;
}

Pion plateau_get_pion_v(Plateau p, int x, int y) {
    if (x < 0 || y < 0 || x > 10 || y > 10)
        return NULL;
    else
        return p->tab[y][x];
}

DynTab voisin(Plateau p, Pion pion, DynTab dt) {
    Coordonnee c = pion_get_coord(pion);
    int x = coord_get_x(c), y = coord_get_y(c);
    Pion p_;
    if ((p_ = plateau_get_pion_v(p, x-1, y)) != NULL)
        tab_add(dt, p_);
    if ((p_ = plateau_get_pion_v(p, x-1, y-1)) != NULL)
        tab_add(dt, p_);
    if ((p_ = plateau_get_pion_v(p, x, y-1)) != NULL)
        tab_add(dt, p_);
    if ((p_ = plateau_get_pion_v(p, x, y+1)) != NULL)
        tab_add(dt, p_);
    if ((p_ = plateau_get_pion_v(p, x+1, y+1)) != NULL)
        tab_add(dt, p_);
    if ((p_ = plateau_get_pion_v(p, x+1, y)) != NULL)
        tab_add(dt, p_);
    return dt;
}

bool coup_gagnant(Plateau p, Pion pion) {
    bool debut = false, fin = false;
    DynTab dt = tab_init();
    tab_add(dt, pion);
    Pion c = tab_get_pion(dt, 0);
    unsigned int i = 0;
    while (c != NULL && i < tab_get_taille(dt)) {
        Coordonnee coord = pion_get_coord(c);
        int x = coord_get_x(coord), y = coord_get_y(coord);
        if (pion_get_couleur(c) == BLEU) {
            if (x == 0 && !debut)
                debut = true;
            else if (x == 10 && !fin)
                fin = true;
        } else {
            if (y == 0 && !debut)
                debut = true;
            else if (y == 10 && !fin)
                fin = true;
        }
        dt = voisin(p, c, dt);
        c = tab_get_pion(dt, ++i);
    }
    tab_destroy(dt);
    return (debut && fin);
}

int plateau_placer_pion(Plateau* p, Pion pion) {
    Coordonnee coord = pion_get_coord(pion);
    if (plateau_case_vide(*p,coord)) {
        (*p)->tab[coord_get_y(coord)][coord_get_x(coord)] = pion;
        if (coup_gagnant(*p, pion))
            return 2;
        return 1;
    }
    return 0;
}

Pion plateau_get_pion(Plateau p, Coordonnee coord) {
    return p->tab[coord_get_y(coord)][coord_get_x(coord)];
}

Pion plateau_get_pion2(Plateau p, unsigned int x, unsigned int y) {
    assert(x < 11 && y < 11);
    return p->tab[y][x];
}
