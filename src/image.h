#ifndef _IMAGE_H
#define _IMAGE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string.h>

/** \brief Optimise une image pour un affichage sur l'écran
 *
 * \param char *filepath
 * \return SDL_Surface* Surface contenant la nouvelle image optimisé
 */

SDL_Surface *load_image( char *filepath );

/** \brief Applique une surface à une autre
 *
 * \param int x Offset en abscisse
 * \param int y Offset en ordonnée
 * \param SDL_Surface *source Surface à appliquer
 * \param SDL_Surface *destination Surface à laquelle on applique la surface source
 */

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination );



#endif
