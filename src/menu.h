#ifndef HEX_SCC_MENU_H
#define HEX_SCC_MENU_H

#include "menuItem.h"

typedef struct menu_s* Menu;

Menu menu_init();

Menu menu_add(Menu m);

menuItem menu_get(Menu m, int i);

Menu menu_set_item(Menu m, int i, menuItem mnit);

void menu_destroy(Menu m);

#endif //HEX_SCC_MENU_H
