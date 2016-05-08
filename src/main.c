#define _GNU_SOURCE 1
#include <math.h>
#include "initialisation.h"
#include "image.h"
#include "display.h"

int main(int argc, char *argv[]) {
    Uint32 time = 0, message_time = 0;
    SDL_Surface *screen = NULL;
    Item hexBoard, bluePawn, redPawn, j1_victory, j2_victory, j1_turn, j2_turn, miss_click;
    TTF_Font *menu_font, *title_font, *message_font;
    TTF_Font **font[] = {&menu_font, &title_font, &message_font};
    SDL_Rect j1_victory_pos, j2_victory_pos, j1_turn_pos, j2_turn_pos, miss_click_pos;
    SDL_Rect *message_pos[] = {&j1_victory_pos, &j2_victory_pos, &j1_turn_pos, &j2_turn_pos, &miss_click_pos};
    Curseur curseur;
    int page = 0;
    int jeu = 1;
    Menu menu[N_MENU];
    bool message_on_screen = false;
    bool game = false;
    bool tourJ1 = true;
    Plateau p = NULL;
    bool running = true;

    unsigned int r = 15;
    unsigned int s = (unsigned int) ((double) r / cos(30 * M_PI / 180.0f));
    unsigned int h = (unsigned int) ((sin(30 * M_PI / 180.0f)) * (double) s);

    /* Initialise la SDL */
    initialize(&screen);

    /* Définition des couleurs d'affichage du texte non sélectionné et séléctionné */
    SDL_Color color[N_MAINMENU] = {{TEXT_SELECTED},
                                   {TEXT_N_SELECTED}};

    /* Charge la police d'écriture */
    for (int i = 0; i < N_FONT; i++)
        (*font[i]) = TTF_OpenFont(FONT_NAME, FONT_SIZE + ((i * 15) + 1));

    /* Titre du jeu */
    SDL_Color title_color = {TITLE_COLOR};
    SDL_Surface *title = TTF_RenderText_Blended(title_font, TITLE, title_color);
    SDL_Rect title_pos;
    title_pos.x = screen->clip_rect.w / 2 - title->clip_rect.w / 2;
    title_pos.y = 15;

    /* Item */
    Item *items[N_ITEM] = {&hexBoard, &bluePawn, &redPawn};
    Item *message[] = {&j1_victory, &j2_victory, &j1_turn, &j2_turn, &miss_click};
    for (int i = 0; i < N_ITEM; i++)
        items[i]->on_screen = false;

    /* Chargement des images */
    hexBoard.surface = IMG_Load(HEXFILE_PNG);
    bluePawn.surface = IMG_Load(BLUEPAWN_PNG);
    redPawn.surface = IMG_Load(REDPAWN_PNG);
    j1_victory.surface = TTF_RenderText_Blended(message_font, "Victoire du joueur BLEU !", title_color);
    j2_victory.surface = TTF_RenderText_Blended(message_font, "Victoire du joueur ROUGE !", title_color);
    j1_turn.surface = TTF_RenderText_Blended(message_font, "Tour du joueur 1", title_color);
    j2_turn.surface = TTF_RenderText_Blended(message_font, "Tour du joueur 2", title_color);
    miss_click.surface = TTF_RenderText_Blended(message_font, "Coup invalide !", title_color);

    for (int i = 0; i < N_MESSAGE; i++) {
        message[i]->on_screen = false;
        message_pos[i]->x = screen->clip_rect.w / 2 - message[i]->surface->clip_rect.w / 2;
        message_pos[i]->y = screen->clip_rect.h - 150;
    }

    /* Fond de l'écran de jeu */
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, BACKGROUND_MENU));

    menuItem previous = mnit_init();
    mnit_set_not_selected_surface(previous, IMG_Load(PREVIOUS_NS_PNG));
    mnit_set_selected_surface(previous, IMG_Load(PREVIOUS_S_PNG));
    mnit_get_position(previous)->x = 150;
    mnit_get_position(previous)->y = screen->clip_rect.h / 2 - mnit_get_selected_surface(previous)->clip_rect.h / 2;

    Menu main_menu = menu_init(N_MAINMENU), game_menu = menu_init(N_GAMEMENU),
            new_game_menu = menu_init(N_NEWGAMEMENU), diff_menu = menu_init(N_DIFFICULTY),
            load_menu = menu_init(N_LOAD - 2);

    menu[0] = main_menu;
    menu[1] = game_menu;
    menu[2] = new_game_menu;
    menu[3] = diff_menu;
    menu[4] = load_menu;

    menu_set(menu);
    for (int i = 0; i < N_MENU - 1; i++)
        init_menu(menu[i], screen, menu_font, color, FONT_SIZE, MENU_MARGIN);

    /* Mise à jour de l'écran */
    SDL_Flip(screen);

    SDL_Event event;
    while (running) {
        time = SDL_GetTicks();
        if (message_on_screen) {
            if (time > (message_time + 5000)) {
                message_on_screen = false;
                for (int i = 0; i < N_MESSAGE; i++)
                    message[i]->on_screen = false;
            }
        }
        while (SDL_PollEvent(&event)) {
            curseur.x = event.motion.x;
            curseur.y = event.motion.y;
            switch (event.type) {
                case SDL_MOUSEMOTION:
                    mnit_set_selected(previous, mnit_is_over(previous, &curseur));
                    for (int j = 0; j < N_MENU; j++) {
                        if (menu[j]->on_screen)
                            for (int i = 0; i < menu[j]->size; ++i)
                                mnit_set_selected(menu[j]->items[i], mnit_is_over(menu[j]->items[i], &curseur));
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (mnit_is_over(previous, &curseur)) {
                            if (page > 0 && page < 4) {
                                menu[page--]->on_screen = false;
                                menu[page]->on_screen = true;
                                break;
                            }
                            if (page == 4) {
                                menu[page]->on_screen = false;
                                page = 2;
                                menu[page]->on_screen = true;
                            }
                        }
                        jeu = menu_clic(screen, menu, &page, curseur, &p, &tourJ1, items, menu_font, color);
                        if (jeu == 0)
                            running = false;
                        else if (jeu == 2) {
                            game = true;
                            move_menu(screen, menu, true);
                            mnit_get_position(previous)->x = 80;
                            mnit_get_position(previous)->y = 20;
                            break;
                        }
                        if (game) {
                            if (curseur.x >= HEXPOS_X && curseur.x <= hexBoard.surface->clip_rect.w
                                && curseur.y >= HEXPOS_Y && curseur.y <= hexBoard.surface->clip_rect.h) {
                                Coordonnee coord = pixel_to_coord(p, HEXPOS_X+25, HEXPOS_Y+18, (unsigned int) curseur.x,
                                                                  (unsigned int) curseur.y, r, h, s);
                                if (coord != NULL) {
                                    printf("colonne : %d, ligne %d\n", coord_get_x(coord), coord_get_y(coord));
                                    Pion pion = pion_init();
                                    pion = pion_set(pion, coord, tourJ1);
                                    int res = plateau_placer_pion(&p, pion);
                                    switch (res) {
                                        case 0:
                                            SDL_BlitSurface(miss_click.surface, NULL, screen, &miss_click_pos);
                                            message_time = time;
                                            message_on_screen = true;
                                            miss_click.on_screen = true;
                                            pion_destroy(&pion);
                                            break;
                                        case 1:
                                            tourJ1 = !tourJ1;
                                            if (tourJ1) {
                                                SDL_BlitSurface(j1_turn.surface, NULL, screen, &j1_turn_pos);
                                                message_time = time;
                                                message_on_screen = true;
                                                j1_turn.on_screen = true;
                                            } else {
                                                SDL_BlitSurface(j2_turn.surface, NULL, screen, &j2_turn_pos);
                                                message_time = time;
                                                message_on_screen = true;
                                                j2_turn.on_screen = true;
                                            }
                                            break;
                                        case 2:
                                            if (tourJ1) {
                                                SDL_BlitSurface(j1_victory.surface, NULL, screen, &j1_victory_pos);
                                                message_time = time;
                                                message_on_screen = true;
                                                j1_victory.on_screen = true;
                                            } else {
                                                SDL_BlitSurface(j2_victory.surface, NULL, screen, &j2_victory_pos);
                                                message_time = time;
                                                message_on_screen = true;
                                                j2_victory.on_screen = true;
                                            }
                                            break;
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, BACKGROUND_MENU));
        SDL_BlitSurface(title, NULL, screen, &title_pos);
        drawMenu(menu, N_MENU, screen, previous);
        drawPlateau(items, screen, p);
        if (message_on_screen)
            for (int i = 0; i < N_MESSAGE; i++)
                if (message[i]->on_screen)
                    SDL_BlitSurface(message[i]->surface, NULL, screen, message_pos[i]);
        SDL_Flip(screen);
        if (1000 / FPS > (SDL_GetTicks() - time))
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - time));
    }

    //Quit SDL
    plateau_destroy(&p);
    for (int i = 0; i < N_ITEM; i++)
        SDL_FreeSurface(items[i]->surface);
    for (int i = 0; i < N_MENU; i++)
        menu_destroy(menu[i]);
    for (int i = 0; i < N_MESSAGE; i++)
        SDL_FreeSurface(message[i]->surface);
    SDL_FreeSurface(title);
    for (int i = 0; i < N_FONT; i++)
        TTF_CloseFont((*font[i]));
    TTF_Quit();
    SDL_Quit();

    return 0;
}
