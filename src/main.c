#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "initialisation.h"
#include "image.h"
#include "menuItem.h"

int drawMenu(SDL_Surface *screen, TTF_Font *font)
{
    int x, y;
    #define NMENU 2
    #define PLAY 0
    #define QUIT 1

    SDL_Color color[NMENU] = { {255,255,255}, {0,255,0} };

    menuItem play = mnit_init();
    play = mnit_set_name(play, "Jouer");
    mnit_set_surface(play, TTF_RenderText_Blended(font,mnit_get_name(play),color[0]));
    mnit_get_position(play)->x = screen->clip_rect.w/2 - mnit_get_surface(play)->clip_rect.w/2;
    mnit_get_position(play)->y = screen->clip_rect.h/2 - mnit_get_surface(play)->clip_rect.h;

    menuItem quit = mnit_init();
    mnit_set_name(quit, "Quitter");
    mnit_set_surface(quit, TTF_RenderText_Blended(font,mnit_get_name(quit),color[0]));
    mnit_get_position(quit)->x = screen->clip_rect.w/2 - mnit_get_surface(quit)->clip_rect.w/2;
    mnit_get_position(quit)->y = screen->clip_rect.h/2 + mnit_get_surface(quit)->clip_rect.h;

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,191,255));

    menuItem menu[NMENU] = {play,quit};
    SDL_Event event;
    int running = true;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for(int i = 0; i < NMENU; ++i)
                    {
                        if(x >= mnit_get_position(menu[i])->x && x <= mnit_get_position(menu[i])->x + mnit_get_position(menu[i])->w && y >= mnit_get_position(menu[i])->y && y <= mnit_get_position(menu[i])->y + mnit_get_position(menu[i])->h)
                        {
                            if(!mnit_get_selected(menu[i]))
                            {
                                mnit_set_selected(menu[i], true);
                                SDL_FreeSurface(mnit_get_surface(menu[i]));
                                mnit_set_surface(menu[i], TTF_RenderText_Solid(font,mnit_get_name(menu[i]),color[1]));
                            }
                        }
                        else
                        {
                            if(mnit_get_selected(menu[i]))
                            {
                                mnit_set_selected(menu[i], false);
                                SDL_FreeSurface(mnit_get_surface(menu[i]));
                                mnit_set_surface(menu[i], TTF_RenderText_Solid(font,mnit_get_name(menu[i]),color[1]));
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for(int i = 0; i < NMENU; ++i)
                    {
                        if(x >= mnit_get_position(menu[i])->x && x <= mnit_get_position(menu[i])->x + mnit_get_position(menu[i])->w && y >= mnit_get_position(menu[i])->y && y <= mnit_get_position(menu[i])->y + mnit_get_position(menu[i])->h)
                        {
                            for (int j = 0; j < NMENU; ++j)
                                SDL_FreeSurface(mnit_get_surface(menu[j]));
                            return i;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        for (int j = 0; j < NMENU; ++j)
                            SDL_FreeSurface(mnit_get_surface(menu[j]));
                        return 0;
                    }
                case SDL_QUIT:
                    for(int i = 0; i < NMENU; ++i)
                        mnit_destroy(menu[i]);
                    return 1;
            }
        }
        for(int i = 0; i < NMENU; ++i)
            SDL_BlitSurface(mnit_get_surface(menu[i]),NULL,screen, mnit_get_position(menu[i]));
        SDL_Flip(screen);
    }
    return -1;
}


int main( int argc, char *argv[ ] )
{
    SDL_Surface *screen = NULL;
    SDL_Rect hexBoard;
    hexBoard.x = 270;
    hexBoard.y = 100;

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

    int running = true;
    TTF_Font *font;
    font = TTF_OpenFont("CAC-Champagne/cac_champagne.ttf",30);
    int i = drawMenu(screen, font);
    if(i==1)
    {
        running = false;
    }

    // Fond d'�cran du jeu 0,191,255

    SDL_Flip(screen);

    SDL_Event event;
    while (running)
    {
        while ( SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        int mouseX = event.motion.x;
                        int mouseY = event.motion.y;
                        printf("X=%d Y=%d\n",mouseX,mouseY); // on r�cup�re les coordonn�es du clic
                    }
                    break;

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        i = drawMenu(screen, font);
                        if(i==1)
                            running = false;
                    }
                    break;

                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        // refresh screen
        // mettre ici tous les blit utiles s'il y a des changements dans les surfaces, board, nouveaux pions
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,191,255));
        SDL_Surface *hex = IMG_Load("Images/hex.png");

        apply_surface(hexBoard.x,hexBoard.y,hex,screen);
        SDL_Flip(screen); //maj des surfaces pour affichage
    }

    //Quit SDL
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
