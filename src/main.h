#ifndef HEX_SCC_MAIN_H
#define HEX_SCC_MAIN_H

typedef struct curseur_s {
    int x;
    int y;
} Curseur;

typedef struct item_s {
    SDL_Surface* surface;
    bool on_screen;
} Item;

#endif //HEX_SCC_MAIN_H
