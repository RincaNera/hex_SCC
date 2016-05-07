#include "initialisation.h"
#include "image.h"
#include "display.h"
#include "sauvegarde.h"

int main(int argc, char *argv[]) {
    Uint32 time;
    SDL_Surface *screen = NULL;
    Item hexBoard, bluePawn, redPawn;
    TTF_Font *font;
    Curseur curseur;
    int menu_on_screen = 0;
    Menu menu[N_MENU];
    bool running = true;

    /* Initialise la SDL */
    initialize(&screen);

    /* Définition des couleurs d'affichage du texte non sélectionné et séléctionné */
    SDL_Color color[N_MAINMENU] = {{TEXT_SELECTED},
                                   {TEXT_N_SELECTED}};

    /* Charge la police d'écriture */
    font = TTF_OpenFont(FONT_NAME, FONT_SIZE);

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

    /* Menu principal */
    menuItem play = NULL, quit = NULL, options = NULL;
    Menu main_menu = menu_init(N_MAINMENU);
    main_menu->items[0] = play;
    main_menu->items[1] = options;
    main_menu->items[2] = quit;
    char *aux_n[5] = {"Jouer", "Options", "Quitter"};
    main_menu = menu_set_names(main_menu, aux_n);
    main_menu->on_screen = true;
    init_menu(main_menu, screen, font, color, FONT_SIZE, MENU_MARGIN);

    /* Menu Jeu */
    menuItem new_game = NULL, load_game = NULL;
    Menu game_menu = menu_init(N_GAMEMENU);
    game_menu->items[0] = new_game;
    game_menu->items[1] = load_game;
    aux_n[0] = "Nouvelle partie";
    aux_n[1] = "Charger partie";
    game_menu = menu_set_names(game_menu, aux_n);
    init_menu(game_menu, screen, font, color, FONT_SIZE, MENU_MARGIN);

    /* Menu Nouvelle partie */
    menuItem human = NULL, ai = NULL;
    Menu new_game_menu = menu_init(N_NEWGAMEMENU);
    new_game_menu->items[0] = human;
    new_game_menu->items[1] = ai;
    aux_n[0] = "vs HUMAIN";
    aux_n[1] = "vs ORDINATEUR";
    new_game_menu = menu_set_names(new_game_menu, aux_n);
    init_menu(new_game_menu, screen, font, color, FONT_SIZE, MENU_MARGIN);

    /* Menu Difficulté */
    menuItem aiv1 = NULL, aiv2 = NULL;
    Menu diff_menu = menu_init(N_DIFFICULTY);
    diff_menu->items[0] = aiv1;
    diff_menu->items[1] = aiv2;
    aux_n[0] = "IA v1";
    aux_n[1] = "IA v2";
    diff_menu = menu_set_names(diff_menu, aux_n);
    init_menu(diff_menu, screen, font, color, FONT_SIZE, MENU_MARGIN);

    menu[0] = main_menu;
    menu[1] = game_menu;
    menu[2] = new_game_menu;
    menu[3] = diff_menu;

    Plateau p = plateau_init();
    bool tour = true;
    save_charger(&p, &tour, "save.txt");

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
                    if (event.button.button == SDL_BUTTON_LEFT)
                        for (int j = 0; j < N_MENU; j++) {
                            if (menu[j]->on_screen)
                                for (int i = 0; i < menu[j]->size; ++i) {
                                    if (mnit_is_over(menu[j]->items[i], &curseur)) {
                                        switch (j) {
                                            case 0:
                                                switch (i) {
                                                    case 0:
                                                        menu[0]->on_screen = false;
                                                        menu[1]->on_screen = true;
                                                        break;
                                                    case N_MAINMENU - 1:
                                                        running = false;
                                                        break;
                                                    default:
                                                        break;
                                                }
                                                break;
                                            case 1:
                                                switch(i) {
                                                    case 0:
                                                        menu[1]->on_screen = false;
                                                        menu[2]->on_screen = true;
                                                        break;
                                                    default:
                                                        break;
                                                }
                                                break;
                                            case 2:
                                                switch (i) {
                                                    case 0:
                                                        menu[2]->on_screen = false;
                                                        break;
                                                    case 1:
                                                        menu[2]->on_screen = false;
                                                        menu[3]->on_screen = true;
                                                    default:
                                                        break;
                                                }
                                                break;
                                            case 3:
                                                break;
                                            case 4:
                                                break;
                                            default:
                                                break;
                                        }
                                        break;
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
        drawMenu(menu, N_MENU, screen);
        drawPlateau(items, screen, p);
        SDL_Flip(screen);
        if (1000 / FPS > (SDL_GetTicks() - time))
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - time));
    }

    //Quit SDL
    for (int i = 0; i < N_ITEM; i++)
        SDL_FreeSurface(items[i]->surface);
    for (int i = 0; i < N_MENU; i++)
        menu_destroy(menu[i]);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
