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
 * \brief Définit un pion
 * \param p Le pion à définir
 * \param coord Les nouvelles coordonnées du pion
 * \param couleur La nouvelle couleur du pion
 * \return Le pion correctement définit
 */
Pion pion_set(Pion p, Coordonnee coord, int couleur);

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
 * \brief Modifie les coordonnées d'un pion
 *        ATTENTION A LA MODIFICATION D'UN PION DEJA PLACE
 *        RISQUE D'INCOHERENCE DES DONNEES
 * \param p Le pion dont on veut modifier les coordonnées
 * \param coord Les nouvelles coordonnées du pion
 * \return Le pion modifié
 */
Pion pion_set_coord(Pion p, Coordonnee coord);

/**
 * \brief Renvoie les coordonnées d'un pion
 * \param p Le pion dont on veut connaitre les coordonnées
 * \return Les coordonnées du pion
 */
Coordonnee pion_get_coord(Pion p);

#endif //HEX_SCC_PION_H
