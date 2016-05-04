#include "image.h"
#include "initialisation.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>

SDL_Surface* load_image( char *filepath ) {
    SDL_Surface * loadedImage = NULL;
    SDL_Surface * optimisedImage = NULL;

    loadedImage = IMG_Load(filepath);

    //Si le chargement de l'image est r�ussie
    if( loadedImage != NULL ) {
        //Cr�ation de l'image optimis�e
        optimisedImage = SDL_DisplayFormat( loadedImage );
        //Supression de l'ancienne image
        SDL_FreeSurface( loadedImage );
    }

    return (optimisedImage);
}

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination ){
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, NULL, destination, &offset);
}
