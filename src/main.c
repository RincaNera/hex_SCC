#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "SDL/SDL_ttf.h"
#include "initialisation.h"
#include "image.h"
#include "menuItem.h"
#include "coordonnee.h"
#include "jeu.h"
#include "plateau.h"
#include <stdio.h>


#define R 15
#define S 18
#define H 7
#define HEXPOS_X 270
#define HEXPOS_Y 100
#define FONT_NAME "./files/OpenSans-Light.ttf"
#define FONT_SIZE 43
#define FPS 60
#define BACKGROUND_GAME 255,255,255
#define HEXFILE_PNG "./files/hex_inverse.png"
#define HEXFILE_BMP "./files/saves/hex_updated.bmp"
#define REDPAWN_PNG "./files/button-red22.png"
#define BLUEPAWN_PNG "./files/button-blue22.png"




int main( int argc, char *argv[ ] )
{
	Uint32 time;
    SDL_Surface *screen = NULL;
    SDL_Surface *hexBoard = NULL;
    SDL_Surface *bluePawn = NULL;
    SDL_Surface *redPawn = NULL;
    unsigned int mouseX, mouseY;
	TTF_Font *font;
	int running;
	int i;
	int joueur = 0;
    Coordonnee hexagon, hexagonCenter;
    hexagon = coord_init();
    hexagonCenter = coord_init();
    int winner = 0;
	int turn = JOUEUR_1;
	player joueur_actuel;
	player J1, J2;
	Plateau p = NULL;

	initialiser_jeu(&J1, &J2, &p);
	joueur_actuel = J1;

    if (initialize_screen(&screen) == 0)
    {
        printf("ERROR: screen not properly initialized");
        exit(1);
    }

    if( initialize_TTF() == 0)
    {
        printf("ERROR: font not properly initialized");
        exit(2);
    }

    font = TTF_OpenFont(FONT_NAME,FONT_SIZE);
    running = true;
    i = drawMenu(screen, font);
    if(i==1)
    {
        running = false;
    }

    /* Fond de l'écran de jeu */
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, BACKGROUND_GAME));

    /* Application de l'image HEX */
    hexBoard = IMG_Load(HEXFILE_PNG);
    apply_surface(HEXPOS_X,HEXPOS_Y,hexBoard,screen);

    /* Chargement des images de pions */
    bluePawn = load_image(BLUEPAWN_PNG);
    redPawn = load_image(REDPAWN_PNG);

    SDL_Flip(screen);

    /* Mise à jour de l'écran */
    SDL_Event event;
    while (running)
    {
        time = SDL_GetTicks();
        while ( SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouseX = event.motion.x;
                        mouseY = event.motion.y;
                        hexagon = pixel_to_rect(mouseX,mouseY,R,H,S);
                        hexagonCenter = hexa_to_pixel(coord_get_x(hexagon),coord_get_y(hexagon),R,H,S);
                    }
                    break;

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        SDL_LockSurface(screen);
                        SDL_SaveBMP(screen,HEXFILE_BMP);
                        SDL_UnlockSurface(screen);
                        i = drawMenu(screen, font);
                        if(i==1)
                            running = false;
                        hexBoard = load_image(HEXFILE_BMP);
                        apply_surface(0,0,hexBoard,screen);
                        SDL_Flip(screen);
                    }
                    break;

                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        SDL_Flip(screen);
        if(1000/FPS > (SDL_GetTicks()-time))
            SDL_Delay(1000/FPS-(SDL_GetTicks()-time));
    }

    //Quit SDL
    SDL_FreeSurface(screen);
    SDL_FreeSurface(hexBoard);
    SDL_FreeSurface(bluePawn);
    SDL_FreeSurface(redPawn);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
