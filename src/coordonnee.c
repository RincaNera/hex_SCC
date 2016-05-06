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

int pixel_to_rect (unsigned int x, unsigned int y, unsigned int r, unsigned int h, unsigned int s){
    #define HEX_TILE_NUMBER 11
    #define OFFSET_X 295
    #define OFFSET_Y 118
    #define RECT_TYPE_A 0
    #define RECT_TYPE_B 1

    int col, lig, roundX, roundY, rectType;
    float m;

    col = (int) ( (x - OFFSET_X) / (2 * r) );
    lig = (int) ( (y - OFFSET_Y) / (h + s) );

    roundX = (x - OFFSET_X) - col * (2 * r);
    roundY = (y - OFFSET_Y) - lig * (h + s);

    printf("TempX = %u \nTempY = %u", roundX,roundY);
    printf("\nLigne = %d \nColonne = %d\n",lig,col);

    m = ((float)h / (float)r);
    rectType = lig % 2;
    switch (rectType)
    {
        case RECT_TYPE_A:
            /* Si on est dans la zone 2 (partie supérieure droite du rectangle) */
            if (roundY < (roundX * m - h))
                printf("roundY = %d A2 : %f\n",roundY, m - h);
            else
            {
                /* Si on est dans la zone 1 (partie supérieure gauche du rectangle) */
                if (roundY < (-roundX * m + h))
                    printf("A1\n");
                /* Si on est dans la zone 1 (partie inférieure du rectangle) */
                else
                    printf("A3\n");
            }
            break;
        case RECT_TYPE_B:
            /* On est dans la moitié droite de l'hexagone */
            if (roundX > r)
            {
                /* On est dans la partie supérieure */
                if ( roundY < (2 * h - roundX * m) )
                    printf("B2\n");
                else
                    printf("B3\n");
            }
             /* On est dans la moitié gauche de l'hexagone */
            else
            {
                if (roundY < roundX * m)
                    printf("B2\n");
                else
                    printf("B1\n");
            }
            break;

        default:
            break;
    }
    return (1);
}
