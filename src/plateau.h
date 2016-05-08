#ifndef HEX_SCC_PLATEAU_H
#define HEX_SCC_PLATEAU_H

#include <stdbool.h>
#include "pion.h"
#include "coordonnee.h"

#define TAILLE 11

typedef struct plateau_s* Plateau;

/**
 * \brief Initialise un plateau
 * \return Un plateau correctement initialisé
 */
Plateau plateau_init();

void plateau_destroy(Plateau* p);

/**
 * \brief Indique si une case du plateau est vide
 * \param p Un plateau de jeu
 * \param coord Les coordonnées de la case à vérifier
 * \return true si vide, false sinon
 */
bool plateau_case_vide(Plateau p, Coordonnee coord);

/**
 * \brief Indique si une case du plateau est vide
 * \param p Un plateau de jeu
 * \param x Coordonnée x de la case à vérifier
 * \param y Coordonnée y de la case à vérifier
 * \return true si vide, false sinon
 */
bool plateau_case_vide2(Plateau p, unsigned int x, unsigned int y);

/**
 * \brief Place un pion sur le plateau
 * \param *p Le plateau de jeu sur lequel placer le pion
 * \param pion Le pion à placer
 * \return 1 si le pion a été placé, 2 si coup gagnant, 0 sinon
 */
int plateau_placer_pion(Plateau* p, Pion pion);

/**
 * \brief Renvoie le pion d'une case d'un plateau
 * \param p Le plateau de jeu
 * \param coord Les coordonnées du pion à récupérer
 * \return Le pion aux coordonnées voulues ou NULL si aucun
 *      pion n'est présent a ces coordonnées
 */
Pion plateau_get_pion(Plateau p, Coordonnee coord);

/**
 * \brief Renvoie le pion d'une case d'un plateau
 * \param p Le plateau de jeu
 * \param x Coordonnée x du pion à récupérer
 * \param y Coordonnée y du pion à récupérer
 * \return Le pion aux coordonnées voulues ou NULL si aucun
 *         pion n'est présent a ces coordonnées
 */
Pion plateau_get_pion2(Plateau p, unsigned int x, unsigned int y);

#endif //HEX_SCC_PLATEAU_H
