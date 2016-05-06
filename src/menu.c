#include <assert.h>
#include "menu.h"

typedef struct menu_s {
    menuItem* menu;
    int nb_item;
} menu_s;

Menu menu_init() {
    Menu m = (Menu)malloc(sizeof(menu_s));
    assert(m != NULL);
    m->menu = (menuItem*)calloc(1, sizeof(menuItem));
    assert(m->menu != NULL);
    m->nb_item = 0;
    return m;
}

Menu menu_add(Menu m) {
    m->menu[m->nb_item] = mnit_init();
    m->nb_item++;
    m->menu = (menuItem*)realloc(m->menu, sizeof(menuItem)*(m->nb_item));
    assert(m->menu != NULL);
    return m;
}

menuItem menu_get(Menu m, int i) {
    assert(i <= m->nb_item && i > 0);
    return m->menu[i-1];
}

Menu menu_set_item(Menu m, int i, menuItem mnit) {
    assert(i <= m->nb_item && i > 0);
    m->menu[i-1] = mnit;
    return m;
}

void menu_destroy(Menu m) {
    for (int i = 0; i < m->nb_item; i++)
        mnit_destroy(m->menu[i]);
    free(m);
}
