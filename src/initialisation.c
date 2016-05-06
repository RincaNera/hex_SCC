#include "initialisation.h"

#include <SDL/SDL_ttf.h>

bool initialize_screen(SDL_Surface **myScreen) {
    // INITIALISATION ET TEST
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return false;

    // MISE A JOUR DE L'ECRAN ET DE SES PROPRIETES
    *myScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    // TEST DE FONCTIONNEMENT DE L'ECRAN
    if (*myScreen == NULL)
        return false;

    // TITRE DE LA FENÊTRE
    SDL_WM_SetCaption("HEX", NULL);

    return true;
}

bool initialize_TTF() {
    if (TTF_Init() == -1)
        return false;
    else
        return true;
}

Menu initialize_menu(char* name[], int n) {
    Menu m = menu_init();
    for (int i = 0; i < n; i++) {
        m = menu_add(m);
        menu_set_item(m, i+1, mnit_set_name(menu_get(m, i+1), name[i]));
    }
    return m;
}
