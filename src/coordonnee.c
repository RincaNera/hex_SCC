#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "coordonnee.h"

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
    if (x <= 10)
        coord->x = x;
    return coord;
}

Coordonnee coord_set_y(Coordonnee coord, unsigned int y) {
    if (y <= 10)
        coord->y = y;
    return coord;
}

unsigned int coord_get_x(Coordonnee coord) {
    return coord->x;
}

unsigned int coord_get_y(Coordonnee coord) {
    return coord->y;
}

void coord_destroy(Coordonnee *coord) {
    free(*coord);
    *coord = NULL;
}
