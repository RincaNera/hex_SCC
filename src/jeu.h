#ifndef JEU_H
#define JEU_H

#include <stdio.h>
#include <stdlib.h>

#define RED  "\x1B[31m"
#define GRE  "\x1B[32m"
//~ #define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
//~ #define PUR  "\x1B[35m"
//~ #define CYA  "\x1B[36m"
//~ #define WHI  "\x1B[37m"
#define NRM  "\x1B[0m"


#define FIN_DU_JEU		0
#define ERREUR_TOUR_JEU	1

#define JOUEUR_1	0
#define JOUEUR_2	1

#define HUMAIN		0
#define IA			1


typedef struct _player {
	int num_joueur;
	int role;
} player;


#endif
