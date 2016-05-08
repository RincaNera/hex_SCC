#include "initialisation.h"
#include "image.h"
#include "display.h"

int main(int argc, char *argv[]) {
    Uint32 time;
    SDL_Surface *screen = NULL;
    Item hexBoard, bluePawn, redPawn;
    TTF_Font *font;
    Curseur curseur;
    int page = 0;
    int jeu = 1;
    Menu menu[N_MENU];
    bool running = true;

    /* Initialise la SDL */
    initialize(&screen);

    /* Définition des couleurs d'affichage du texte non sélectionné et séléctionné */
    SDL_Color color[N_MAINMENU] = {{TEXT_SELECTED},
                                   {TEXT_N_SELECTED}};

    /* Charge la police d'écriture */
    font = TTF_OpenFont(FONT_NAME, FONT_SIZE);
    TTF_Font *title_font = TTF_OpenFont(FONT_NAME, FONT_SIZE +15);

    /* Titre du jeu */
    SDL_Color title_color = {TITLE_COLOR};
    SDL_Surface* title = TTF_RenderText_Blended(title_font, TITLE, title_color);
    SDL_Rect title_pos;
    title_pos.x = screen->clip_rect.w / 2 - title->clip_rect.w / 2;
    title_pos.y = 15;

    /* Item */
    Item *items[N_ITEM] = {&hexBoard, &bluePawn, &redPawn};
    for (int i = 0; i < N_ITEM; i++)
        items[i]->on_screen = false;

    /* Chargement des images */
    hexBoard.surface = IMG_Load(HEXFILE_PNG);
    bluePawn.surface = IMG_Load(BLUEPAWN_PNG);
    redPawn.surface = IMG_Load(REDPAWN_PNG);

    /* Fond de l'écran de jeu */
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, BACKGROUND_MENU));

    menuItem previous = mnit_init();
    mnit_set_not_selected_surface(previous, IMG_Load(PREVIOUS_NS_PNG));
    mnit_set_selected_surface(previous, IMG_Load(PREVIOUS_S_PNG));
    mnit_get_position(previous)->x = 150;
    mnit_get_position(previous)->y = screen->clip_rect.h / 2 - mnit_get_selected_surface(previous)->clip_rect.h/2;

    Menu main_menu = menu_init(N_MAINMENU), game_menu = menu_init(N_GAMEMENU),
            new_game_menu = menu_init(N_NEWGAMEMENU), diff_menu = menu_init(N_DIFFICULTY),
            load_menu = menu_init(N_LOAD-2);

    menu[0] = main_menu;
    menu[1] = game_menu;
    menu[2] = new_game_menu;
    menu[3] = diff_menu;
    menu[4] = load_menu;

    menu_set(menu);
    for (int i = 0; i < N_MENU-1; i++)
        init_menu(menu[i], screen, font, color, FONT_SIZE, MENU_MARGIN);

    Plateau p = NULL;
    bool tourJ1 = true;

    /* Mise à jour de l'écran */
    SDL_Flip(screen);

    SDL_Event event;
    while (running) {
        time = SDL_GetTicks();
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
                            } if (page == 4) {
                                menu[page]->on_screen = false;
                                page = 2;
                                menu[page]->on_screen = true;
                            }
                        }
                        jeu = menu_clic(screen, menu, &page, curseur, &p, &tourJ1, items, font, color);
                        if (jeu == 0)
                            running = false;
                        else if (jeu == 2) {
                            move_menu(screen, menu, true);
                            mnit_get_position(previous)->x = 80;
                            mnit_get_position(previous)->y = 20;
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
    SDL_FreeSurface(title);
    TTF_CloseFont(title_font);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
