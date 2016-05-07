#include "menu.h"

Menu menu_init(int size) {
    Menu m = (Menu)malloc(sizeof(struct menu_s));
    m->items = (menuItem*)malloc(sizeof(menuItem)*size);
    m->names = (char**)malloc(sizeof(char*)*size);
    m->size = size;
    m->on_screen = false;
    return m;
}

void menu_destroy(Menu m) {
    for (int i = 0; i < m->size; i++) {
        mnit_destroy(m->items[i]);
        free(m->names[i]);
    }
    free(m->names);
    free(m);
}

Menu menu_set_names(Menu menu, char* names[]) {
    for (int i = 0; i < menu->size; i++) {
        menu->names[i] = (char*)malloc(sizeof(char)*(strlen(names[i])+1));
        strcpy(menu->names[i], names[i]);
    }
    return menu;
}