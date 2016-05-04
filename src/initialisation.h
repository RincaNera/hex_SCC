#ifndef _INITIALISATION_H
#define _INITIALISATION_H

#include "SDL/SDL.h"
#include <stdbool.h>

#define SCREEN_WIDTH 800 /* Largeur de la fenêtre d'affichage */
#define SCREEN_HEIGHT 600 /* Hauteur de la fenêtre d'affichage */
#define SCREEN_BPP 32 /* Bit-Per-Pixel profondeur des couleurs */

/** \brief Initialise la fênetre d'affichage ainsi que les fonctions SDL
 *
 * \param SDL_Surface **myScreen L'écran à initialiser
 * \return Un booléen : true si réussite false sinon
 *
 */

bool initialize_screen(SDL_Surface **myScreen);

/** \brief Initialise les polices d'écritures
 * \return Un booléen : true si réussite false sinon
 *
 */

bool initialize_TTF();

#endif
