#ifndef HEX_SCC_DISPLAY_H
#define HEX_SCC_DISPLAY_H

#include "menuItem.h"
#include "plateau.h"
#include "menu.h"

/**
 * \brief Affiche le menu
 * \param screen La surface SDL sur lequel afficher le menu
 * \param m La liste des items du menu
 */
void drawMenu(Menu* m, int nb_menu, SDL_Surface *screen, menuItem previous);

/**
 * \brief Affiche le plateau
 * \param items La liste des items à afficher
 * \param screen La surface SDL sur lequel afficher le menu
 */
void drawPlateau(Item* items[], SDL_Surface* screen, Plateau p);

#endif //HEX_SCC_DISPLAY_H
