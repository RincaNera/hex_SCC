#include <stdlib.h>
#include "menu.h"
#include "initialisation.h"
#include "image.h"
#include "main.h"
#include "menuItem.h"
#include <SDL/SDL_ttf.h>
#include <assert.h>

#define NMENU 2 /* Nombre de menuItem */
#define N_ITEM 3 /* Nombre de SDL_Surface */
#define PLAY 0 /* Passe à l'écran de jeu */
#define QUIT 1 /* Demande de fermeture du jeu */
#define BACKGROUND_MENU 0,188,255 /* Couleur du fond d'écran */
#define MENU_MARGIN 15
#define TEXT_SELECTED 255,255,255 /* Couleur du texte lorsqu'il est selectionné */
#define TEXT_N_SELECTED 0,0,0 /* Couleur du texte lorsqu'il n'est pas selectionné */
#define HEXPOS_X 270
#define HEXPOS_Y 100
#define FONT_NAME "./files/OpenSans-Light.ttf"
#define FONT_SIZE 43
#define FPS 60
#define BACKGROUND_GAME 255,255,255
#define HEXFILE_PNG "./files/hex_inverse.png"
#define REDPAWN_PNG "./files/button-red22.png"
#define BLUEPAWN_PNG "./files/button-blue22.png"

/** \brief Render de la 1ère page d'affichage le menu
 *
 * \param SDL_Surface* screen La surface SDL sur lequel afficher le menu
 * \param TTF_Font * font La police d'écriture désiré
 * \return int Un entier allant de 0 à NMENU qui retourne l'élement selectionné
 *
 */
void drawMenu(menuItem* m, SDL_Surface *screen) {
    for (int i = 0; i < NMENU; ++i)
        if (mnit_is_on_screen(m[i])) {
            if (mnit_is_selected(m[i]))
                SDL_BlitSurface(mnit_get_selected_surface(m[i]), NULL, screen, mnit_get_position(m[i]));
            else
                SDL_BlitSurface(mnit_get_not_selected_surface(m[i]), NULL, screen, mnit_get_position(m[i]));
        }
}

void drawPlateau(Item* items[], SDL_Surface* screen) {
    for (int i = 0; i < N_ITEM; i++)
        if (items[i]->on_screen)
            apply_surface(HEXPOS_X, HEXPOS_Y, items[i]->surface, screen);
}

int main(int argc, char *argv[]) {
    Uint32 time;
    SDL_Surface *screen = NULL;
    Item hexBoard, bluePawn, redPawn;
    TTF_Font *font;
    Curseur curseur;
    bool running = true;

    /* Initialise la SDL */
    initialize(&screen);

    /* Définition des couleurs d'affichage du texte non sélectionné et séléctionné */
    SDL_Color color[NMENU] = {{TEXT_SELECTED},
                              {TEXT_N_SELECTED}};

    /* Charge la police d'écriture */
    font = TTF_OpenFont(FONT_NAME, FONT_SIZE);

    /* Item */
    Item* items[N_ITEM] = {&hexBoard, &bluePawn, &redPawn};
    for (int i = 0; i < N_ITEM; i++)
        items[i]->on_screen = false;

    /* Chargement des images */
    hexBoard.surface = IMG_Load(HEXFILE_PNG);
    bluePawn.surface = load_image(BLUEPAWN_PNG);
    redPawn.surface = load_image(REDPAWN_PNG);

    /* Fond de l'écran de jeu */
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, BACKGROUND_MENU));

    /* Menu */
    menuItem play = NULL, quit = NULL;
    menuItem menu[NMENU] = {play, quit};
    char* menu_name[NMENU] = {"Jouer", "Quitter"};
    int y = screen->clip_rect.h / 2 - (NMENU/2 * FONT_SIZE) - MENU_MARGIN;
    for (int i = 0; i < NMENU; i++) {
        menu[i] = init_menu(menu[i], screen, font, color, menu_name[i], y);
        y += FONT_SIZE + MENU_MARGIN;
    }

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
                    for (int i = 0; i < NMENU; ++i)
                        mnit_set_selected(menu[i], mnit_is_over(menu[i], &curseur));
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        for (int i = 0; i < NMENU; ++i)
                            mnit_set_on_screen(menu[i], false);
                        running = false;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                        printf("X=%d Y=%d\n", curseur.x, curseur.y); // on recupere les coordonnees du clic
                    for (int i = 0; i < NMENU; ++i) {
                        if (mnit_is_on_screen(menu[i]))
                            if (mnit_is_over(menu[i], &curseur)) {
                                if (i == 0) {
                                    for (i = 0; i < N_ITEM; i++)
                                        items[i]->on_screen = true;
                                    for (i = 0; i < NMENU; i++)
                                        mnit_set_on_screen(menu[i], false);
                                }
                                if (i == 1)
                                    running = false;
                                break;
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
        drawMenu(menu, screen);
        drawPlateau(items, screen);
        SDL_Flip(screen);
        if (1000 / FPS > (SDL_GetTicks() - time))
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - time));
    }

    //Quit SDL
    for (int i = 0; i < N_ITEM; i++)
        SDL_FreeSurface(items[i]->surface);
    for (int i = 0; i < NMENU; i++)
        mnit_destroy(menu[i]);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
