#ifndef _INITIALISATION_H
#define _INITIALISATION_H

#include "SDL/SDL.h"
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

bool initialize_screen(SDL_Surface **myScreen);

bool initialize_TTF();

#endif
