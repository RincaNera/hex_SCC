#include <stdlib.h>
#include "coordonnee.h"

struct coordonnee_s {
    unsigned int x;
    unsigned int y;
};

Coordonnee coord_init() {
    Coordonnee coord = (Coordonnee)malloc(sizeof(struct coordonnee_s));
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