#ifndef _IMAGE_H
#define _IMAGE_H

#include "SDL/SDL.h"
#include <string.h>

SDL_Surface *load_image( char *filepath );

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination );



#endif
