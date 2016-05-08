#include "initialisation.h"

static bool initialize_screen(SDL_Surface **screen) {
    // INITIALISATION ET TEST
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return false;

    // MISE A JOUR DE L'ECRAN ET DE SES PROPRIETES
    *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    // TEST DE FONCTIONNEMENT DE L'ECRAN
    if (*screen == NULL)
        return false;

    // TITRE DE LA FENÊTRE
    SDL_WM_SetCaption(TITLE, NULL);

    return true;
}

static bool initialize_TTF() {
    if (TTF_Init() == -1)
        return false;
    else
        return true;
}

void initialize(SDL_Surface **screen) {
    if (!initialize_screen(screen))  {
        fprintf(stderr, "ERROR: screen not properly initialized\n");
        exit(1);
    }
    if (!initialize_TTF()) {
        fprintf(stderr, "ERROR: font not properly initialized\n");
        exit(2);
    }
}

static menuItem init_item(menuItem item, SDL_Surface *screen, TTF_Font* font, SDL_Color color[], char* name, int y) {
    item = mnit_init();
    item = mnit_set_not_selected_surface(item, TTF_RenderText_Blended(font, name, color[0]));
    item = mnit_set_selected_surface(item, TTF_RenderText_Blended(font, name, color[1]));
    mnit_get_position(item)->x = screen->clip_rect.w / 2 - mnit_get_selected_surface(item)->clip_rect.w / 2;
    mnit_get_position(item)->y = y;
    item = mnit_set_selected(item, false);
    return item;
}

void init_menu(Menu menu, SDL_Surface *screen, TTF_Font* font, SDL_Color color[], int size, int margin) {
    int y = screen->clip_rect.h / 2 - ((int)((float)menu->size / 2.0f * (float)size)) - margin;
    for (int i = 0; i < menu->size; i++) {
        menu->items[i] = init_item(menu->items[i], screen, font, color, menu->names[i], y);
        y += size + margin;
    }
}
