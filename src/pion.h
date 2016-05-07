#ifndef HEX_SCC_PION_H
#define HEX_SCC_PION_H

#include "coordonnee.h"

#define ROUGE 1
#define BLEU 2

typedef struct pion_s* Pion;

/**
 * \brief Initialise un pion
 * \return Un pion correctement initialisé
 */
Pion pion_init();

/**
 * \brief Définit un pion de coordonnée déjà définie
 * \param p Le pion à définir
 * \param coord Les nouvelles coordonnées du pion
 * \param couleur La nouvelle couleur du pion
 * \return Le pion correctement définit
 */
Pion pion_set(Pion p, Coordonnee coord, int couleur);

/**
 * \brief Définit un pion en fonction de x et y
 * \param p Le pion à définir
 * \param x Coordonnée x du pion
 * \param y Coordonnée y du pion
 * \param couleur La nouvelle couleur du pion
 * \return Le pion correctement définit
 */
Pion pion_set2(Pion p, unsigned int x, unsigned int y, int couleur);

/**
 * \brief Définit la couleur d'un pion
 * \param p Le pion dont on veut modifier la couleur
 * \param c La nouvelle couleur du pion
 *          (0 pour rouge, 1 pour bleu)
 * \return Le pion modifié
 */
Pion pion_set_couleur(Pion p, int c);

/**
 * \brief Renvoie la couleur d'un pion
 * \param p Le pion dont on veut connaitre la couleur
 * \return 0 si rouge, 1 si bleu
 */
int pion_get_couleur(Pion p);

/**
 * \brief Modifie les coordonnées d'un pion en fonction de coordonnée déja définie
 *        ATTENTION A LA MODIFICATION D'UN PION DEJA PLACE
 *        RISQUE D'INCOHERENCE DES DONNEES
 * \param p Le pion dont on veut modifier les coordonnées
 * \param coord La nouvelle coordonnée du pion
 * \return Le pion modifié
 */
Pion pion_set_coord(Pion p, Coordonnee coord);

/**
 * \brief Modifie les coordonnées d'un pion en fonction de x et y
 *        ATTENTION A LA MODIFICATION D'UN PION DEJA PLACE
 *        RISQUE D'INCOHERENCE DES DONNEES
 * \param p Le pion dont on veut modifier les coordonnées
 * \param x Coordonnée x du pion
 * \param y Coordonnée y du pion
 * \return Le pion modifié
 */
Pion pion_set_coord2(Pion p, unsigned int x, unsigned int y);

/**
 * \brief Renvoie les coordonnées d'un pion
 * \param p Le pion dont on veut connaitre les coordonnées
 * \return Les coordonnées du pion
 */
Coordonnee pion_get_coord(Pion p);

SDL_Rect pion_to_hex(Pion p);

Pion hex_to_pion(int x, int y);

#endif //HEX_SCC_PION_H
