#include "menu.h"


int drawMenu(SDL_Surface *screen, TTF_Font *font)
{

	Uint32 time; /* Permet de réguler le temps d'affichage d'une image */
    int x, y; /* Position enregistré du curseur */

	/* Définition des couleurs d'affichage du texte non sélectionné et séléctionné */
    SDL_Color color[2] = { {TEXT_SELECTED}, {TEXT_N_SELECTED} };

	/* Définition de l'élement "Jouer" */
    menuItem play = mnit_init();
    play = mnit_set_name(play, "Jouer");
    mnit_set_surface(play, TTF_RenderText_Blended(font,mnit_get_name(play),color[0]));
    mnit_get_position(play)->x = screen->clip_rect.w/2 - mnit_get_surface(play)->clip_rect.w/2;
    mnit_get_position(play)->y = screen->clip_rect.h/NMENU - mnit_get_surface(play)->clip_rect.h;

    /* Définition de l'élément "Charger" */
    menuItem load = mnit_init();
    load = mnit_set_name(load, "Charger");
    mnit_set_surface(load, TTF_RenderText_Blended(font,mnit_get_name(load),color[0]));
    mnit_get_position(load)->x = screen->clip_rect.w/2 - mnit_get_surface(load)->clip_rect.w/2;
    mnit_get_position(load)->y = screen->clip_rect.h/NMENU + mnit_get_surface(load)->clip_rect.h;

    /* Définition de l'élément "Sauvegarder" */
    menuItem save = mnit_init();
    save = mnit_set_name(save, "Sauvegarder");
    mnit_set_surface(save, TTF_RenderText_Blended(font,mnit_get_name(save),color[0]));
    mnit_get_position(save)->x = screen->clip_rect.w/2 - mnit_get_surface(save)->clip_rect.w/2;
    mnit_get_position(save)->y = screen->clip_rect.h/NMENU + mnit_get_surface(save)->clip_rect.h * 3;

	/* Définition de l'élement "Quitter" */
    menuItem quit = mnit_init();
    mnit_set_name(quit, "Quitter");
    mnit_set_surface(quit, TTF_RenderText_Blended(font,mnit_get_name(quit),color[0]));
    mnit_get_position(quit)->x = screen->clip_rect.w/2 - mnit_get_surface(quit)->clip_rect.w/2;
    mnit_get_position(quit)->y = screen->clip_rect.h/NMENU + mnit_get_surface(quit)->clip_rect.h * 5;

	/* Mise en place du fond d'écran propre au Menu*/
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, BACKGROUND_MENU));

    menuItem menu[NMENU] = {play,save,load,quit};
    SDL_Event event;

    int running = true;
    while (running)
    {
		time = SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for(int i = 0; i < NMENU; ++i)
                    {
						/* Si l'élément est sélectionné il est supprimé puis réécrit en surbrillance*/
                        if(x >= mnit_get_position(menu[i])->x &&
                           x <= mnit_get_position(menu[i])->x + mnit_get_position(menu[i])->w &&
                           y >= mnit_get_position(menu[i])->y &&
                           y <= mnit_get_position(menu[i])->y + mnit_get_position(menu[i])->h)
                        {
                            if(!mnit_get_selected(menu[i]))
                            {
                                mnit_set_selected(menu[i], true);
                                SDL_FreeSurface(mnit_get_surface(menu[i]));
                                mnit_set_surface(menu[i], TTF_RenderText_Blended(font,mnit_get_name(menu[i]),color[1]));
                            }
                        }
						/* Cas où l'élément a été mis en surbrillance mais n'est plus sélectionné*/
                        else
                        {
                            if(mnit_get_selected(menu[i]))
                            {
                                mnit_set_selected(menu[i], false);
                                SDL_FreeSurface(mnit_get_surface(menu[i]));
                                mnit_set_surface(menu[i], TTF_RenderText_Blended(font,mnit_get_name(menu[i]),color[0]));
                            }
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for(int i = 0; i < NMENU; ++i)
                    {
						/* Retourne l'indice de l'élément sélectionné */
                        if(x >= mnit_get_position(menu[i])->x &&
                           x <= mnit_get_position(menu[i])->x + mnit_get_position(menu[i])->w &&
                           y >= mnit_get_position(menu[i])->y &&
                           y <= mnit_get_position(menu[i])->y + mnit_get_position(menu[i])->h)
                        {
                            for (int j = 0; j < NMENU; ++j)
                            {
                                SDL_FreeSurface(mnit_get_surface(menu[j]));
                                mnit_destroy(menu[j]);
                            }
                            return i;
                        }
                    }
                    break;

                case SDL_KEYDOWN:
					/* Ferme l'écran du menu */
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        for (int j = 0; j < NMENU; ++j)
                        {
                            SDL_FreeSurface(mnit_get_surface(menu[j]));
                            mnit_destroy(menu[j]);
                        }
                        return 4;
                    }
					break;

                case SDL_QUIT:
                    for(int i = 0; i < NMENU; ++i)
                    {
                        SDL_FreeSurface(mnit_get_surface(menu[i]));
                        mnit_destroy(menu[i]);
                    }
                    return QUIT;
            }
        }

		/* Affichage des surfaces mises à jour */
        for(int i = 0; i < NMENU; ++i)
            SDL_BlitSurface(mnit_get_surface(menu[i]),NULL,screen, mnit_get_position(menu[i]));
        SDL_Flip(screen);

		if(1000/30 > (SDL_GetTicks()-time))
                        SDL_Delay(1000/30 - (SDL_GetTicks()-time));
    }
    for(int i = 0; i < NMENU; ++i)
    {
        SDL_FreeSurface(mnit_get_surface(menu[i]));
        mnit_destroy (menu[i]);
    }
    return -1; /* Cas d'erreur */
}

int drawMenuGameType(SDL_Surface *screen, TTF_Font *font)
{

	Uint32 time; /* Permet de réguler le temps d'affichage d'une image */
    int x, y; /* Position enregistré du curseur */

	/* Définition des couleurs d'affichage du texte non sélectionné et séléctionné */
    SDL_Color color[2] = { {TEXT_SELECTED}, {TEXT_N_SELECTED} };

	/* Définition de l'élement "Humain vs Humain" */
    menuItem human = mnit_init();
    human = mnit_set_name(human, "Humain vs Humain");
    mnit_set_surface(human, TTF_RenderText_Blended(font,mnit_get_name(human),color[0]));
    mnit_get_position(human)->x = screen->clip_rect.w/2 - mnit_get_surface(human)->clip_rect.w/2;
    mnit_get_position(human)->y = screen->clip_rect.h/3 - mnit_get_surface(human)->clip_rect.h;

    /* Définition de l'élément "Humain vs IA (FACILE)" */
    menuItem iaEasy = mnit_init();
    iaEasy = mnit_set_name(iaEasy, "Humain vs IA (facile)");
    mnit_set_surface(iaEasy, TTF_RenderText_Blended(font,mnit_get_name(iaEasy),color[0]));
    mnit_get_position(iaEasy)->x = screen->clip_rect.w/2 - mnit_get_surface(iaEasy)->clip_rect.w/2;
    mnit_get_position(iaEasy)->y = screen->clip_rect.h/3 + mnit_get_surface(iaEasy)->clip_rect.h;

    /* Définition de l'élément "Humain vs IA (DIFFICILE) */
    menuItem iaHard = mnit_init();
    iaHard = mnit_set_name(iaHard, "Humain vs IA (DIFFICILE)");
    mnit_set_surface(iaHard, TTF_RenderText_Blended(font,mnit_get_name(iaHard),color[0]));
    mnit_get_position(iaHard)->x = screen->clip_rect.w/2 - mnit_get_surface(iaHard)->clip_rect.w/2;
    mnit_get_position(iaHard)->y = screen->clip_rect.h/3 + mnit_get_surface(iaHard)->clip_rect.h * 3;

	/* Mise en place du fond d'écran propre au Menu*/
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, BACKGROUND_MENU));

    menuItem menu[3] = {human,iaEasy,iaHard};
    SDL_Event event;

    int running = true;
    while (running)
    {
		time = SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for(int i = 0; i < 3; ++i)
                    {
						/* Si l'élément est sélectionné il est supprimé puis réécrit en surbrillance*/
                        if(x >= mnit_get_position(menu[i])->x &&
                           x <= mnit_get_position(menu[i])->x + mnit_get_position(menu[i])->w &&
                           y >= mnit_get_position(menu[i])->y &&
                           y <= mnit_get_position(menu[i])->y + mnit_get_position(menu[i])->h)
                        {
                            if(!mnit_get_selected(menu[i]))
                            {
                                mnit_set_selected(menu[i], true);
                                SDL_FreeSurface(mnit_get_surface(menu[i]));
                                mnit_set_surface(menu[i], TTF_RenderText_Blended(font,mnit_get_name(menu[i]),color[1]));
                            }
                        }
						/* Cas où l'élément a été mis en surbrillance mais n'est plus sélectionné*/
                        else
                        {
                            if(mnit_get_selected(menu[i]))
                            {
                                mnit_set_selected(menu[i], false);
                                SDL_FreeSurface(mnit_get_surface(menu[i]));
                                mnit_set_surface(menu[i], TTF_RenderText_Blended(font,mnit_get_name(menu[i]),color[0]));
                            }
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for(int i = 0; i < 3; ++i)
                    {
						/* Retourne l'indice de l'élément sélectionné */
                        if(x >= mnit_get_position(menu[i])->x &&
                           x <= mnit_get_position(menu[i])->x + mnit_get_position(menu[i])->w &&
                           y >= mnit_get_position(menu[i])->y &&
                           y <= mnit_get_position(menu[i])->y + mnit_get_position(menu[i])->h)
                        {
                            for (int j = 0; j < 3; ++j)
                            {
                                SDL_FreeSurface(mnit_get_surface(menu[j]));
                                mnit_destroy(menu[j]);
                            }
                            return i;
                        }
                    }
                    break;

                case SDL_KEYDOWN:
					/* Ferme l'écran du menu */
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        for (int j = 0; j < 3; ++j)
                        {
                            SDL_FreeSurface(mnit_get_surface(menu[j]));
                            mnit_destroy(menu[j]);
                        }
                        return QUIT;
                    }
					break;

                case SDL_QUIT:
                    for(int i = 0; i < 3; ++i)
                    {
                        SDL_FreeSurface(mnit_get_surface(menu[i]));
                        mnit_destroy(menu[i]);
                    }
                    return QUIT;
            }
        }

		/* Affichage des surfaces mises à jour */
        for(int i = 0; i < 3; ++i)
            SDL_BlitSurface(mnit_get_surface(menu[i]),NULL,screen, mnit_get_position(menu[i]));
        SDL_Flip(screen);

		if(1000/30 > (SDL_GetTicks()-time))
                        SDL_Delay(1000/30 - (SDL_GetTicks()-time));
    }
    for(int i = 0; i < 3; ++i)
    {
        SDL_FreeSurface(mnit_get_surface(menu[i]));
        mnit_destroy (menu[i]);
    }
    return -1; /* Cas d'erreur */
}
