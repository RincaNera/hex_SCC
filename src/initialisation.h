#ifndef _INITIALISATION_H
#define _INITIALISATION_H

#include <SDL/SDL_ttf.h>
#include "SDL/SDL.h"
#include "menuItem.h"

#define SCREEN_WIDTH 800 /* Largeur de la fenêtre d'affichage */
#define SCREEN_HEIGHT 600 /* Hauteur de la fenêtre d'affichage */
#define SCREEN_BPP 32 /* Bit-Per-Pixel profondeur des couleurs */
#define TITRE "HEX"

/**
 * \brief Initialise la SDL
 */
void initialize(SDL_Surface **screen);

menuItem init_menu(menuItem menu, SDL_Surface *screen, TTF_Font* font, SDL_Color color[], char* name, int y);

#endif
