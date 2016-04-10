#ifndef HEX_SCC_COORDONNEE_H
#define HEX_SCC_COORDONNEE_H

typedef struct coordonnee_s* Coordonnee;

/**
 * \brief Initialise une coordonnée
 * \return Une coordonnée correctement initialisée
 *         (0, 0) par défaut
 */
Coordonnee coord_init();

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

#endif //HEX_SCC_COORDONNEE_H
