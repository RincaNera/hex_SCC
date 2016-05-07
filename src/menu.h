#ifndef HEX_SCC_MENU_H
#define HEX_SCC_MENU_H

#include "menuItem.h"

struct menu_s {
    menuItem* items;
    char** names;
    int size;
    bool on_screen;
};

typedef struct menu_s* Menu;

Menu menu_init(int size);

void menu_destroy(Menu m);

Menu menu_set_names(Menu menu, char* names[]);

#endif //HEX_SCC_MENU_H
