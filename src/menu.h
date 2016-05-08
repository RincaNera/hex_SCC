#ifndef HEX_SCC_MENU_H
#define HEX_SCC_MENU_H

#include <SDL/SDL_ttf.h>
#include "menuItem.h"
#include "plateau.h"

struct menu_s {
    menuItem* items;
    char** names;
    int size;
    bool on_screen;
};

typedef struct menu_s* Menu;

Menu menu_init(int size);

void menu_destroy(Menu m);

void menu_set(Menu* menu);

Menu menu_set_names(Menu menu, char* names[]);

void menu_on_screen(Menu menu, bool on_screen);

void move_menu(SDL_Surface *screen, Menu *menu, bool corner);

int menu_clic(SDL_Surface *screen, Menu *menu, int *page, Curseur c, Plateau *p, bool *tourJ1, Item *items[], TTF_Font* font, SDL_Color* color);


#endif //HEX_SCC_MENU_H
