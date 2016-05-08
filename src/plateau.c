#include <stdlib.h>
#include <assert.h>
#define __USE_MISC 1
#include <math.h>
#include "plateau.h"
#include "tableau.h"

#define RECT_TILE_NUMBER TAILLE + (TAILLE / 2)
#define RECT_TYPE_A 0 /* Rectangle de type "Maison" */
#define RECT_TYPE_B 1 /* Rectangle de type Y (i grec)*/

struct plateau_s {
    Pion tab[TAILLE][TAILLE];
};

Plateau plateau_init() {
    Plateau p = (Plateau) malloc(sizeof(struct plateau_s));
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

Pion plateau_get_pion(Plateau p, Coordonnee coord) {
    return p->tab[coord_get_y(coord)][coord_get_x(coord)];
}

Pion plateau_get_pion_2(Plateau p, int x, int y) {
    if (x < 0 || y < 0 || x > 10 || y > 10)
        return NULL;
    else
        return p->tab[y][x];
}

Pion plateau_get_pion_neg(Plateau p, int x, int y) {
    if (x < 0 || y < 0 || x > 10 || y > 10)
        return NULL;
    else
        return p->tab[y][x];
}

DynTab voisin(Plateau p, Pion pion, DynTab dt) {
    Coordonnee c = pion_get_coord(pion);
    int x = coord_get_x(c), y = coord_get_y(c);
    Pion p_;
    if ((p_ = plateau_get_pion_neg(p, x - 1, y)) != NULL) if (pion_get_couleur(pion) == pion_get_couleur(p_))
        tab_add(dt, p_);
    if ((p_ = plateau_get_pion_neg(p, x - 1, y - 1)) != NULL) if (pion_get_couleur(pion) == pion_get_couleur(p_))
        tab_add(dt, p_);
    if ((p_ = plateau_get_pion_neg(p, x, y - 1)) != NULL) if (pion_get_couleur(pion) == pion_get_couleur(p_))
        tab_add(dt, p_);
    if ((p_ = plateau_get_pion_neg(p, x + 1, y)) != NULL) if (pion_get_couleur(pion) == pion_get_couleur(p_))
        tab_add(dt, p_);
    if ((p_ = plateau_get_pion_neg(p, x + 1, y - 1)) != NULL) if (pion_get_couleur(pion) == pion_get_couleur(p_))
        tab_add(dt, p_);
    if ((p_ = plateau_get_pion_neg(p, x, y - 1)) != NULL) if (pion_get_couleur(pion) == pion_get_couleur(p_))
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

int plateau_placer_pion(Plateau *p, Pion pion) {
    Coordonnee coord = pion_get_coord(pion);
    if (plateau_case_vide(*p, coord)) {
        (*p)->tab[coord_get_y(coord)][coord_get_x(coord)] = pion;
        if (coup_gagnant(*p, pion))
            return 2;
        return 1;
    }
    return 0;
}

Coordonnee pixel_to_coord(Plateau p, unsigned int offset_x, unsigned int offset_y, unsigned int x, unsigned int y,
                         unsigned int r, unsigned int h, unsigned int s) {
    Coordonnee hexagone;                /* Coordonnées de l'hexagone sélectionné */
    unsigned int col, line, rectType;   /* Colonne, ligne correspondant à un rectangle et son type */
    int roundX, roundY;                 /* Points X, Y centré sur le point 0.0 du rectangle */
    float m;                            /* Coefficient directeur */
    int lowerLimitX, upperLimitX;       /* Borne inférieure et supérieure de la grille en pixel */

    col = (int) ((x - offset_x) / (2 * r));
    line = (int) ((y - offset_y) / (h + s));

    /* Vérification de la borne supérieure de la grille */
    if (col > RECT_TILE_NUMBER - 1 || line > RECT_TILE_NUMBER - 1)
        return NULL;

    lowerLimitX = offset_x + (TAILLE - line - 1) * (int) (r);
    upperLimitX = lowerLimitX + TAILLE * (2 * (int) r);

    /* Vérification des bornes inférieures en prenant en compte le décalage */
    if ((int) (x) < lowerLimitX || (int) (x) > upperLimitX || offset_y < 0)
        return NULL;

    hexagone = coord_init();

    roundX = (x - offset_x) - col * (2 * r);
    roundY = (y - offset_y) - line * (h + s);

    rectType = line % 2;

    m = ((float) h / (float) r);

    switch (rectType) {
        case RECT_TYPE_A:
            col = col - ((TAILLE - line) / 2);
            /* Si on est dans la zone 2 (partie supérieure droite du rectangle) */
            if (roundY < (roundX * m - h))
                hexagone = coord_set(hexagone, col + 1, line - 1);
            else {
                /* Si on est dans la zone 1 (partie supérieure gauche du rectangle) */
                if (roundY < (-roundX * m + h))
                    hexagone = coord_set(hexagone, col, line - 1);
                    /* Si on est dans la zone 1 (partie inférieure du rectangle) */
                else
                    hexagone = coord_set(hexagone, col, line);
            }
            break;
        case RECT_TYPE_B:
            col = col - ((TAILLE - line) / 2) + 1;
            /* On est dans la moitié droite de l'hexagone */
            if (roundX > r) {
                /* On est dans la partie supérieure */
                if (roundY < (2 * h - roundX * m))
                    hexagone = coord_set(hexagone, col, line - 1);
                else
                    hexagone = coord_set(hexagone, col, line);
            }
                /* On est dans la moitié gauche de l'hexagone */
            else {
                if (roundY < roundX * m)
                    hexagone = coord_set(hexagone, col, line - 1);
                else
                    hexagone = coord_set(hexagone, col - 1, line);
            }
            break;
        default:
            break;
    }
    return hexagone;
}

SDL_Rect pion_to_pixel(Pion p) {
    SDL_Rect pos;
    int c = coord_get_x(pion_get_coord(p)), l = coord_get_y(pion_get_coord(p)), r = 15;
    int s = (int)((double)r / cos(30* M_PI / 180.0f));
    int h = (int)((sin(30* M_PI / 180.0f)) * (double)s);
    pos.x = (c + (10-l) / 2) * 2 * r + ((10-l) % 2?2:1) *r + r;
    pos.y = l * (h + s) + h + s / 2 + s/2;
    return pos;
}

void plateau_destroy(Plateau *p) {
    if (*p != NULL) {
        for (int i = 0; i < TAILLE; i++)
            for (int j = 0; j < TAILLE; j++)
                if ((*p)->tab[i][j] != NULL)
                    pion_destroy(&(*p)->tab[i][j]);
        free(*p);
        *p = NULL;
    }
}
