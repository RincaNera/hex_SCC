#ifndef HEX_SCC_MAIN_H
#define HEX_SCC_MAIN_H

#include <SDL/SDL_video.h>
#include "menuItem.h"

#define N_MAINMENU 3 /* Nombre d'items du menu principal */
#define N_GAMEMENU 2 /* Nombre d'items du menu de jeu */
#define N_NEWGAMEMENU 2 /* Nombre d'items du menu de nouvelle partie */
#define N_DIFFICULTY 2 /* Nombre d'items du choix de difficulté */
#define N_LOAD 7
#define N_MENU 5 /* Nombre de menu */
#define N_ITEM 3 /* Nombre de SDL_Surface */
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
#define PREVIOUS_NS_PNG "./files/previous.png"
#define PREVIOUS_S_PNG "./files/previous_selected.png"
#define TITLE "HEX"
#define TITLE_COLOR 200,0,0

typedef struct curseur_s {
    int x;
    int y;
} Curseur;

typedef struct item_s {
    SDL_Surface *surface;
    bool on_screen;
} Item;

#endif //HEX_SCC_MAIN_H
