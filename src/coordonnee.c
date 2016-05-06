#include <stdlib.h>
#include <assert.h>
#include "coordonnee.h"
#include <stdio.h>

struct coordonnee_s {
    unsigned int x;
    unsigned int y;
};

Coordonnee coord_init() {
    Coordonnee coord = (Coordonnee)malloc(sizeof(struct coordonnee_s));
    assert(coord != NULL);
    coord->x = 0;
    coord->y = 0;
    return coord;
}

Coordonnee coord_set(Coordonnee coord, unsigned int x, unsigned int y) {
    coord = coord_set_x(coord, x);
    coord = coord_set_y(coord, y);
    return coord;
}

Coordonnee coord_set_x(Coordonnee coord, unsigned int x) {
    if (x <= 11)
        coord->x = x;
    return coord;
}

Coordonnee coord_set_y(Coordonnee coord, unsigned int y) {
    if (y <= 11)
        coord->y = y;
    return coord;
}

unsigned int coord_get_x(Coordonnee coord) {
    return coord->x;
}

unsigned int coord_get_y(Coordonnee coord) {
    return coord->y;
}

Coordonnee pixel_to_rect (unsigned int x, unsigned int y, unsigned int r, unsigned int h, unsigned int s){
    #define HEX_TILE_NUMBER 11 /* Nombre de case en largeur / longueur */
    #define RECT_TILE_NUMBER HEX_TILE_NUMBER + (HEX_TILE_NUMBER / 2)
    #define OFFSET_X 295 /* Position du point x par rapport à la grille */
    #define OFFSET_Y 118 /* Position du point y par rapport à la grille */
    #define RECT_TYPE_A 0 /* Rectangle de type "Maison" */
    #define RECT_TYPE_B 1 /* Rectangle de type Y (i grec)*/

    Coordonnee hexagone; /* Coordonnées de l'hexagone sélectionné */
    unsigned int col, line, rectType; /* Colonne, linene correspondant à un rectangle et son type */
    int roundX, roundY; /* Points X, Y centré sur le point 0.0 du rectangle */
    float m; /* Coefficient directeur */
    int lowerLimitX, upperLimitX; /* Borne inférieure et supérieure de la grille en pixel */

    hexagone = coord_init();

    col = (int) ( (x - OFFSET_X) / (2 * r) );
    line = (int) ( (y - OFFSET_Y) / (h + s) );

    /* Vérification de la borne supérieure de la grille */
    if (col > RECT_TILE_NUMBER - 1 || line > 11 )
        return (hexagone);

    lowerLimitX = OFFSET_X +(HEX_TILE_NUMBER - line - 1) * (int)(r);
    upperLimitX = lowerLimitX + HEX_TILE_NUMBER * (2 * (int)r);

    /* Vérification des bornes inférieures en prenant en compte le décalage */
    if ( (int)(x) < lowerLimitX || (int)(x) > upperLimitX || OFFSET_Y < 0 )
        return (hexagone);

    roundX = (x - OFFSET_X) - col * (2 * r);
    roundY = (y - OFFSET_Y) - line * (h + s);

    rectType = line % 2;
    /* Pris en charge du décalage d'hexagone fantome */
    if (rectType == RECT_TYPE_A)
        col = col - (HEX_TILE_NUMBER /2 - line/2);
    else
        col = col - (HEX_TILE_NUMBER /2 - line);

    m = ((float)h / (float)r);


    switch (rectType)
    {
        case RECT_TYPE_A:
            /* Si on est dans la zone 2 (partie supérieure droite du rectangle) */
            if (roundY < (roundX * m - h))
            {
                hexagone = coord_set(hexagone, col + 1, line - 1);
            }
            else
            {
                /* Si on est dans la zone 1 (partie supérieure gauche du rectangle) */
                if (roundY < (-roundX * m + h))
                {
                    hexagone = coord_set(hexagone, col, line - 1);
                }
                /* Si on est dans la zone 1 (partie inférieure du rectangle) */
                else
                {
                    hexagone = coord_set(hexagone, col, line);
                }
            }
            break;
        case RECT_TYPE_B:
            /* On est dans la moitié droite de l'hexagone */
            if (roundX > r)
            {
                /* On est dans la partie supérieure */
                if ( roundY < (2 * h - roundX * m) )
                {
                    hexagone = coord_set(hexagone, col, line - 1);
                }
                else
                {
                    hexagone = coord_set(hexagone, col, line);
                }
            }
             /* On est dans la moitié gauche de l'hexagone */
            else
            {
                if (roundY < roundX * m)
                {
                    hexagone = coord_set(hexagone, col, line - 1);
                }
                else
                {
                    hexagone = coord_set(hexagone, col -1, line);
                }

            }
            break;

        default:
            break;
    }
    return (hexagone);
}

