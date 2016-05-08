#ifndef HEX_SCC_MENU_H
#define HEX_SCC_MENU_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "menuItem.h"

#define NMENU 4 /* Nombre de menuItem */
#define PLAY 0 /* Passe � l'�cran de jeu */
#define QUIT 3 /* Demande de fermeture du jeu */
#define BACKGROUND_MENU 0,188,255 /* Couleur du fond d'�cran */
#define TEXT_SELECTED 255,255,255 /* Couleur du texte lorsqu'il est selectionn� */
#define TEXT_N_SELECTED 0,0,0 /* Couleur du texte lorsqu'il n'est pas selectionn� */

/** \brief Render de la 1�re page d'affichage le menu
 *
 * \param SDL_Surface* screen La surface SDL sur lequel afficher le menu
 * \param TTF_Font * font La police d'�criture d�sir�
 * \return int Un entier allant de 0 � NMENU qui retourne l'�lement selectionn�
 *
 */
int drawMenu(SDL_Surface *screen, TTF_Font *font);

int drawMenuGameType(SDL_Surface *screen, TTF_Font *font);

#endif // HEX_SCC_MENU_H
