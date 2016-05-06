#include <stdlib.h>
#include "menu.h"
#include "initialisation.h"
#include "image.h"
#include <SDL/SDL_ttf.h>

#define NMENU 2 /* Nombre de menuItem */
#define PLAY 0 /* Passe à l'écran de jeu */
#define QUIT 1 /* Demande de fermeture du jeu */
#define BACKGROUND_MENU 0,188,255 /* Couleur du fond d'écran */
#define TEXT_SELECTED 255,255,255 /* Couleur du texte lorsqu'il est selectionné */
#define TEXT_N_SELECTED 0,0,0 /* Couleur du texte lorsqu'il n'est pas selectionné */
#define HEXPOS_X 270
#define HEXPOS_Y 100
#define FONT_NAME "./files/OpenSans-Light.ttf"
#define FONT_SIZE 43
#define FPS 60
#define BACKGROUND_GAME 255,255,255
#define HEXFILE_PNG "./files/hex_inverse.png"
#define HEXFILE_BMP "./files/hex_updated.bmp"
#define REDPAWN_PNG "./files/button-red22.png"
#define BLUEPAWN_PNG "./files/button-blue22.png"

/** \brief Render de la 1ère page d'affichage le menu
 *
 * \param SDL_Surface* screen La surface SDL sur lequel afficher le menu
 * \param TTF_Font * font La police d'écriture désiré
 * \return int Un entier allant de 0 à NMENU qui retourne l'élement selectionné
 *
 */
int drawMenu(Menu m, SDL_Surface *screen, TTF_Font *font) {

    Uint32 time; /* Permet de réguler le temps d'affichage d'une image */
    int x, y; /* Position enregistré du curseur */

    /* Définition des couleurs d'affichage du texte non sélectionné et séléctionné */
    SDL_Color color[NMENU] = {{TEXT_SELECTED},
                              {TEXT_N_SELECTED}};

    /* Définition de l'élement "Jouer" */
    mnit_set_surface(menu_get(m, 1), TTF_RenderText_Blended(font, mnit_get_name(menu_get(m, 1)), color[0]));
    mnit_get_position(menu_get(m, 1))->x = screen->clip_rect.w / 2 - mnit_get_surface(menu_get(m, 1))->clip_rect.w / 2;
    mnit_get_position(menu_get(m, 1))->y = screen->clip_rect.h / 2 - mnit_get_surface(menu_get(m, 1))->clip_rect.h;

    /* Définition de l'élement "Quitter" */
    mnit_set_surface(menu_get(m, 2), TTF_RenderText_Blended(font, mnit_get_name(menu_get(m, 2)), color[0]));
    mnit_get_position(menu_get(m, 2))->x = screen->clip_rect.w / 2 - mnit_get_surface(menu_get(m, 2))->clip_rect.w / 2;
    mnit_get_position(menu_get(m, 2))->y = screen->clip_rect.h / 2 + mnit_get_surface(menu_get(m, 2))->clip_rect.h;

    /* Mise en place du fond d'écran propre au Menu*/
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, BACKGROUND_MENU));

    SDL_Event event;
    int running = true;
    while (running) {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for (int i = 0; i < NMENU; ++i) {
                        /* Si l'élément est sélectionné il est supprimé puis réécrit en surbrillance*/
                        if (x >= mnit_get_position(menu_get(m, i+1))->x &&
                            x <= mnit_get_position(menu_get(m, i+1))->x + mnit_get_position(menu_get(m, i+1))->w &&
                            y >= mnit_get_position(menu_get(m, i+1))->y &&
                            y <= mnit_get_position(menu_get(m, i+1))->y + mnit_get_position(menu_get(m, i+1))->h) {
                            if (!mnit_get_selected(menu_get(m, i+1))) {
                                mnit_set_selected(menu_get(m, i+1), true);
                                SDL_FreeSurface(mnit_get_surface(menu_get(m, i+1)));
                                mnit_set_surface(menu_get(m, i+1),
                                                 TTF_RenderText_Blended(font, mnit_get_name(menu_get(m, i+1)), color[1]));
                            }
                        }
                        /* Cas où l'élément a été mis en surbrillance mais n'est plus sélectionné */
                        else {
                            if (mnit_get_selected(menu_get(m, i+1))) {
                                mnit_set_selected(menu_get(m, i+1), false);
                                SDL_FreeSurface(mnit_get_surface(menu_get(m, i+1)));
                                mnit_set_surface(menu_get(m, i+1),
                                                 TTF_RenderText_Blended(font, mnit_get_name(menu_get(m, i+1)), color[0]));
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for (int i = 0; i < NMENU; ++i) {
                        /* Retourne l'indice de l'élément sélectionné */
                        if (x >= mnit_get_position(menu_get(m, i+1))->x &&
                            x <= mnit_get_position(menu_get(m, i+1))->x + mnit_get_position(menu_get(m, i+1))->w &&
                            y >= mnit_get_position(menu_get(m, i+1))->y &&
                            y <= mnit_get_position(menu_get(m, i+1))->y + mnit_get_position(menu_get(m, i+1))->h) {
                            for (int j = 0; j < NMENU; ++j)
                                SDL_FreeSurface(mnit_get_surface(menu_get(m, j+1)));
                            return i;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    /* Ferme l'écran du menu */
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        for (int j = 0; j < NMENU; ++j)
                            SDL_FreeSurface(mnit_get_surface(menu_get(m, j+1)));
                        return QUIT;
                    }
                    break;
                case SDL_QUIT:
                    return QUIT;
                default:
                    break;
            }
        }

        /* Affichage des surfaces mises à jour */
        for (int i = 0; i < NMENU; ++i)
            SDL_BlitSurface(mnit_get_surface(menu_get(m, i+1)), NULL, screen, mnit_get_position(menu_get(m, i+1)));
        SDL_Flip(screen);

        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
    return -1; /* Cas d'erreur */
}


int main(int argc, char *argv[]) {
    Uint32 time;
    SDL_Surface *screen = NULL;
    SDL_Surface *hexBoard = NULL;
    SDL_Surface *bluePawn = NULL;
    SDL_Surface *redPawn = NULL;
    TTF_Font *font;
    Menu menu = NULL;
    int running;
    int i;

    char* menu_name[NMENU] = {"Jouer", "Quitter"};

    if (initialize_screen(&screen) == 0) {
        fprintf(stderr, "ERROR: screen not properly initialized\n");
        exit(1);
    }

    if (initialize_TTF() == 0) {
        fprintf(stderr, "ERROR: font not properly initialized\n");
        exit(2);
    }

    if ((menu = initialize_menu(menu_name, NMENU)) == NULL) {
        fprintf(stderr, "ERROR: Menu not properly initialized\n");
        exit(3);
    }

    font = TTF_OpenFont(FONT_NAME, FONT_SIZE);
    running = true;
    i = drawMenu(menu, screen, font);
    if (i == 1)
        running = false;

    /* Fond de l'écran de jeu */
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, BACKGROUND_GAME));

    /* Application de l'image HEX */
    hexBoard = IMG_Load(HEXFILE_PNG);
    apply_surface(HEXPOS_X, HEXPOS_Y, hexBoard, screen);

    /* Chargement des images de pions */
    bluePawn = load_image(BLUEPAWN_PNG);
    redPawn = load_image(REDPAWN_PNG);

    SDL_Flip(screen);

    /* Mise à jour de l'écran */
    SDL_Event event;
    while (running) {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mouseX = event.motion.x;
                        int mouseY = event.motion.y;
                        printf("X=%d Y=%d\n", mouseX, mouseY); // on recupere les coordonnees du clic
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        SDL_LockSurface(screen);
                        SDL_SaveBMP(screen, HEXFILE_BMP);
                        SDL_UnlockSurface(screen);
                        i = drawMenu(menu, screen, font);
                        if (i == 1)
                            running = false;
                        hexBoard = load_image(HEXFILE_BMP);
                        apply_surface(0, 0, hexBoard, screen);
                        SDL_Flip(screen);
                    }
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        SDL_Flip(screen);
        if (1000 / FPS > (SDL_GetTicks() - time))
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - time));
    }

    //Quit SDL
    menu_destroy(menu);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(hexBoard);
    SDL_FreeSurface(bluePawn);
    SDL_FreeSurface(redPawn);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
