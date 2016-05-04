#ifndef HEX_SCC_MENUITEM_H
#define HEX_SCC_MENUITEM_H

#include <stdbool.h>
#include "SDL/SDL.h"

typedef struct menuItem_s* menuItem;

menuItem mnit_init();

void mnit_destroy(menuItem mn);

menuItem mnit_set_name(menuItem mn, char* name);
char* mnit_get_name(menuItem mn);

menuItem mnit_set_surface(menuItem mn, SDL_Surface* surface);
SDL_Surface* mnit_get_surface(menuItem mn);

menuItem mnit_set_position(menuItem mn, SDL_Rect* position);
SDL_Rect* mnit_get_position(menuItem mn);

menuItem mnit_set_selected(menuItem mn, bool s);
bool mnit_get_selected(menuItem mn);

#endif //HEX_SCC_MENUITEM_H
