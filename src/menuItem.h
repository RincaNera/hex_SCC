#ifndef HEX_SCC_MENUITEM_H
#define HEX_SCC_MENUITEM_H

#include <stdbool.h>
#include "main.h"

typedef struct menuItem_s* menuItem;

menuItem mnit_init();
void mnit_destroy(menuItem mn);

menuItem mnit_set_selected_surface(menuItem mn, SDL_Surface *surface);
SDL_Surface *mnit_get_selected_surface(menuItem mn);

menuItem mnit_set_not_selected_surface(menuItem mn, SDL_Surface *surface);
SDL_Surface *mnit_get_not_selected_surface(menuItem mn);


menuItem mnit_set_position(menuItem mn, SDL_Rect *position);
SDL_Rect* mnit_get_position(menuItem mn);

menuItem mnit_set_selected(menuItem mn, bool s);
bool mnit_is_selected(menuItem mn);

bool mnit_is_over(menuItem mn, Curseur* c);

#endif //HEX_SCC_MENUITEM_H
