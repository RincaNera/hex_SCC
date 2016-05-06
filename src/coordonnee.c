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
    #define OFFSET_X 295
    #define OFFSET_Y 118
    #define HEX_TILE_NUMBER 11

    int col, lig, shift, roundX, roundY, rectType;

    col = (int) ( (x - OFFSET_X) / (2 * r) );
    lig = (int) ( (y - OFFSET_Y) / (h + s) );

    roundX = (x - OFFSET_X) - col * (2 * r);
    roundY = (y - OFFSET_Y) - lig * (h + s);

    printf("TempX = %u \nTempY = %u", roundX,roundY);
    printf("\nLigne = %d \nColonne = %d\n",lig,col);

    return (1);
}
