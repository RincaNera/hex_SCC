#ifndef HEX_SCC_COORDONNEE_H
#define HEX_SCC_COORDONNEE_H

#include <SDL/SDL_video.h>
#include "SDL/SDL.h"

typedef struct coordonnee_s* Coordonnee;

/**
 * \brief Initialise une coordonnée
 * \return Une coordonnée correctement initialisée
 *         (0, 0) par défaut
 */
Coordonnee coord_init();

void coord_destroy(Coordonnee* coord);

/**
 * \brief Définit une coordonnée
 * \param coord La coordonnée à définir
 * \param x La nouvelle valeur x de coord
 * \param y La nouvelle valeur y de coord
 * \return La coordonnée correctement modifiée
 */
Coordonnee coord_set(Coordonnee coord, unsigned int x, unsigned int y);

/**
 * \brief Modifie la valeur x d'une coordonnée
 * \param coord Les coordonnées à modifier
 * \param x La nouvelle x de coord
 * \return La coordonnée correctement modifiée
 */
Coordonnee coord_set_x(Coordonnee coord, unsigned int x);

/**
 * \brief Modifie la valeur y d'une coordonnée
 * \param coord Les coordonnées à modifier
 * \param y La nouvelle y de coord
 * \return La coordonnée correctement modifiée
 */
Coordonnee coord_set_y(Coordonnee coord, unsigned int y);

/**
 * \brief Renvoie la valeur x d'une coordonnée
 * \param coord La coordonnée dont on veut connaitre la valeur x
 * \return La valeur x de coord
 */
unsigned int coord_get_x(Coordonnee coord);

/**
 * \brief Renvoie la valeur y d'une coordonnée
 * \param coord La coordonnée dont on veut connaitre la valeur y
 * \return La valeur y de coord
 */
unsigned int coord_get_y(Coordonnee coord);

/**
 * \brief Renvoie les coordonnées de l'hexagone à partir des positions d'un clic
 * Les positions entrées sont en pixels et la sortie se fait par rapport à la grille
 * Exemple:
 * - X: 412 Y: 124 -> 0,0 (dehors)
 * - X: 520 Y: 236 -> 4,4

 * \param unsigned int x Abscisse
 * \param unsigned int y Ordonnée
 * \param unsigned int r Moitié de la largeur d'un hexagone
 * \param unsigned int h Hauteur entre la pointe et le haut d'un côté
 * \param unsigned int s Longueur d'un côté
 * \return La valeur en coordonnée de l'hexagone cliqué ou 0,0 si le clic est en dehors de la grille
 */
Coordonnee pixel_to_rect (unsigned int x, unsigned int y, unsigned int r, unsigned int h, unsigned int s);

/**
 * \brief Convertit une ligne et une colonne d'un hexagone en un rectangle avec les coordonées (x,y) en pixels du centre d'un hexagone
 * \param unsigned int col Colonne de l'hexagone
 * \param unsigned int line Ordonnée de l'hexagone
 * \param unsigned int r Moitié de la largeur d'un hexagone
 * \param unsigned int h Hauteur entre la pointe et le haut d'un côté
 * \param unsigned int s Longueur d'un côté
 * \return Les coordonnées en x,y du centre de l'hexagone
 */
SDL_Rect hexa_to_pixel (unsigned int col, unsigned int line, unsigned int r, unsigned int h, unsigned int s);
#endif //HEX_SCC_COORDONNEE_H
