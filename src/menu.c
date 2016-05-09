#include "menu.h"
#include "sauvegarde.h"
#include "jeu.h"

Menu menu_init(int size) {
    Menu m = (Menu) malloc(sizeof(struct menu_s));
    m->items = (menuItem *) malloc(sizeof(menuItem) * size);
    m->names = (char **) malloc(sizeof(char *) * size);
    m->size = size;
    m->on_screen = false;
    return m;
}

void menu_destroy(Menu m) {
    if (m != NULL) {
        for (int i = 0; i < m->size; i++) {
            mnit_destroy(m->items[i]);
            free(m->names[i]);
        }
        free(m->names);
        free(m);
    }
}

void menu_set(Menu *menu) {
    /* Menu principal */
    menuItem play = NULL, quit = NULL, options = NULL;
    menu[0]->items[0] = play;
    menu[0]->items[1] = options;
    menu[0]->items[2] = quit;
    char *aux_n[5] = {"Jouer", "Options", "Quitter"};
    menu[0] = menu_set_names(menu[0], aux_n);
    menu[0]->on_screen = true;

    /* Menu Jeu */
    menuItem new_game = NULL, load_game = NULL;
    menu[1]->items[0] = new_game;
    menu[1]->items[1] = load_game;
    aux_n[0] = "Nouvelle partie";
    aux_n[1] = "Charger partie";
    menu[1] = menu_set_names(menu[1], aux_n);

    /* Menu Nouvelle partie */
    menuItem human = NULL, ai = NULL;
    menu[2]->items[0] = human;
    menu[2]->items[1] = ai;
    aux_n[0] = "vs HUMAIN";
    aux_n[1] = "vs ORDINATEUR";
    menu[2] = menu_set_names(menu[2], aux_n);

    /* Menu Difficulté */
    menuItem aiv1 = NULL, aiv2 = NULL;
    menu[3]->items[0] = aiv1;
    menu[3]->items[1] = aiv2;
    aux_n[0] = "IA v1";
    aux_n[1] = "IA v2";
    menu[3] = menu_set_names(menu[3], aux_n);

    /* Menu de sauvegarde */
	menuItem save = NULL;
	menu[4]->items[0] = save;
	aux_n[0] = "Sauvegarder";
    menu[4] = menu_set_names(menu[4], aux_n);
}

Menu menu_set_names(Menu menu, char *names[]) {
    for (int i = 0; i < menu->size; i++) {
        menu->names[i] = (char *) malloc(sizeof(char) * (strlen(names[i]) + 1));
        strcpy(menu->names[i], names[i]);
    }
    return menu;
}

void move_menu(SDL_Surface *screen, Menu *menu, bool corner) {
    if (corner) {
        for (int i = 0; i < N_MENU - 1; i++) {
            int x = 50, y = HEXPOS_Y;
            for (int j = 0; j < menu[i]->size; j++) {
                mnit_get_position(menu[i]->items[j])->x = x;
                mnit_get_position(menu[i]->items[j])->y = y;
                y += mnit_get_selected_surface(menu[i]->items[j])->h;
            }
        }
	    menu[4]->on_screen = true;
	    mnit_get_position(menu[4]->items[0])->x = MENU_MARGIN;
	    mnit_get_position(menu[4]->items[0])->y = 600 - FONT_SIZE - MENU_MARGIN;
    } else {
        for (int i = 0; i < N_MENU - 1; i++) {
            for (int j = 0; j < menu[i]->size; j++) {
                mnit_get_position(menu[i]->items[j])->x =
                        screen->clip_rect.w / 2 - mnit_get_selected_surface(menu[i]->items[j])->clip_rect.w / 2;
                mnit_get_position(menu[i]->items[j])->y =
                        screen->clip_rect.h / 2 - ((int) ((float) menu[i]->size / 2.0f * (float) FONT_SIZE)) -
                        MENU_MARGIN;
            }
        }
    }
}

void new_game(Plateau *p) {
    if (*p == NULL)
        *p = plateau_init();
    else {
        plateau_destroy(p);
        *p = plateau_init();
    }
}

int menu_clic(SDL_Surface *screen, Menu *menu, int *page, Curseur c, Plateau *p, bool *tourJ1, Item *items[], TTF_Font *font, SDL_Color *color, Item** message, bool* game, int* mode) {
    for (int i = 0; i < menu[*page]->size; i++) {
        if (mnit_is_over(menu[*page]->items[i], &c)) {
            switch (*page) {
                case 0:
                    switch (i) {
                        case 0:
                            menu[0]->on_screen = false;
                            menu[1]->on_screen = true;
                            *page = 1;
                            return 1;
                        case N_MAINMENU - 1:
                            return 0;
                        default:
                            break;
                    }
                    break;
                case 1:
                    switch (i) {
                        case 0:
                            menu[1]->on_screen = false;
                            menu[2]->on_screen = true;
                            *page = 2;
                            return 1;
                        case 1:
                            new_game(p);
                            int res = save_charger(p, tourJ1, "./saves/save.txt", mode);
                            if (res != 0) {
                                menu[0]->on_screen = true;
                                menu[1]->on_screen = false;
                                res_placer_pion(*p, res-1, tourJ1, message, game, NULL, *mode);
                                *page = 0;
                                if (res >= 2) {
                                    afficher_message(message, res+1);
                                    *game = false;
                                } else
                                    *game = true;
                            }
                            return 1;
                        default:
                            break;
                    }
                    break;
                case 2:
                    switch (i) {
                        case 0:
                            *game = true;
                            *tourJ1 = true;
                            menu[0]->on_screen = true;
                            menu[2]->on_screen = false;
                            *page = 0;
                            for (i = 0; i < N_ITEM; i++)
                                items[i]->on_screen = true;
                            new_game(p);
                            return 2;
                        case 1:
                            menu[2]->on_screen = false;
                            menu[3]->on_screen = true;
                            *page = 3;
                            return 1;
                        default:
                            break;
                    }
                    break;
                case 3:
                    *game = true;
                    *tourJ1 = true;
                    switch (i) {
                        case 0:
                            menu[0]->on_screen = true;
                            menu[3]->on_screen = false;
                            *page = 0;
                            *mode = 1;
                            for (i = 0; i < N_ITEM; i++)
                                items[i]->on_screen = true;
                            new_game(p);
                            return 2;
                        case 1:
                            menu[0]->on_screen = true;
                            menu[3]->on_screen = false;
                            *page = 0;
                            *mode = 2;
                            for (i = 0; i < N_ITEM; i++)
                                items[i]->on_screen = true;
                            new_game(p);
                            return 2;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        }
    }
    return true;
}
