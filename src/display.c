#include "display.h"
#include "image.h"

void drawMenu(Menu *m, int nb_menu, SDL_Surface *screen, menuItem previous) {
    if (mnit_is_selected(previous))
        SDL_BlitSurface(mnit_get_selected_surface(previous), NULL, screen, mnit_get_position(previous));
    else
        SDL_BlitSurface(mnit_get_not_selected_surface(previous), NULL, screen, mnit_get_position(previous));
    for (int j = 0; j < nb_menu; j++) {
        if (m[j]->on_screen)
            for (int i = 0; i < m[j]->size; ++i)
                if (mnit_is_selected(m[j]->items[i]))
                    SDL_BlitSurface(mnit_get_selected_surface(m[j]->items[i]), NULL, screen,
                                    mnit_get_position(m[j]->items[i]));
                else
                    SDL_BlitSurface(mnit_get_not_selected_surface(m[j]->items[i]), NULL, screen,
                                    mnit_get_position(m[j]->items[i]));
    }
}

void drawPlateau(Item *items[], SDL_Surface *screen, Plateau p) {
    if (items[0]->on_screen) {
        Pion pion = NULL;
        SDL_Rect pos;
        Coordonnee coord = coord_init();
        for (unsigned int i = 0; i < TAILLE; i++) {
            for (unsigned int j = 0; j < TAILLE; j++) {
                coord_set(coord, j, i);
                if ((pion = plateau_get_pion(p, coord)) != NULL) {
                    pos = pion_to_hex(pion);
                    if (pion_get_couleur(pion) == ROUGE)
                        apply_surface(HEXPOS_X + pos.x, HEXPOS_Y + pos.y, items[2]->surface, screen);
                    else
                        apply_surface(HEXPOS_X + pos.x, HEXPOS_Y + pos.y, items[1]->surface, screen);
                }
            }
        }
        apply_surface(HEXPOS_X, HEXPOS_Y, items[0]->surface, screen);
    }
}
