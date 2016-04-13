#include "jeu.h"
#include "plateau.h"
#include "pion.h"
#include "coordonnee.h"

//~ #include "plateau.h"


void choix_mode(player *joueur_1, player *joueur_2) {
	int choix=0;
	
	do {
		printf("Veuillez choisir un mode de jeu (HvH : 0, HvIA : 1, IAvIA : 2) : ");
		scanf("%d", &choix);
		getchar();
	} while ((choix < 0) || (choix > 2));
	
	printf("\nVous avez choisi le mode de jeu ");
	if (choix == 2) {
		joueur_1->role = IA;
		joueur_2->role = IA;
		printf("IA vs IA.\n");
	}
	else if (choix == 1) {
		joueur_1->role = HUMAIN;
		joueur_2->role = IA;
		printf("Humain vs IA.\n");
	}
	else {
		joueur_1->role = HUMAIN;
		joueur_2->role = HUMAIN;
		printf("Humain vs Humain.\n");
	}
	
	return;
}


void initialiser_jeu(player *J1, player *J2, Plateau* p) {
	J1->num_joueur = JOUEUR_1;
	J2->num_joueur = JOUEUR_2;
	
	*p = plateau_init();
}


void gestion_joueur(player *joueur_actuel, player J1, player J2) {
	if (joueur_actuel->num_joueur == J1.num_joueur) {
		*joueur_actuel = J2;
	}
	else if (joueur_actuel->num_joueur == J2.num_joueur) {
		*joueur_actuel = J1;
	}
	else {
		fprintf(stderr, "%s[ERR] : probleme de gestion du tour.%s\n", RED, NRM);
		exit(ERREUR_TOUR_JEU);
	}
	
	return;
}

void affichage_sommaire(Plateau p) {
    Coordonnee c = coord_init();
    Pion pion = NULL;
    int k = TAILLE-2;
    char espace[] = "          ";
    for (unsigned int i = 0; i < TAILLE; i++) {
        c = coord_set_x(c, i);
        printf("%s", espace);
        for (unsigned int j = 0; j < TAILLE; j++) {
            c = coord_set_y(c, j);
            pion = plateau_get_pion(p, c);
            if (pion != NULL)
                printf("%d/", pion_get_couleur(pion));
            else
                printf("N/");
        }
        espace[k--] = '\0';
        printf("\n");
    }
}

int main(void) {
	int fini=0;
	int tour=JOUEUR_1;
	player joueur_actuel;
	player J1, J2;
	Plateau p = NULL;
	
	choix_mode(&J1, &J2);
	initialiser_jeu(&J1, &J2, &p);
	joueur_actuel = J1;

    affichage_sommaire(p);
	
	do {
	/* Tour de jeu */
		if (joueur_actuel.role == HUMAIN) {
			printf("J%d : %sHumain%s\n", joueur_actuel.num_joueur+1, GRE, NRM);
		}
		else if (joueur_actuel.role == IA) {
			printf("J%d : %sIA%s\n", joueur_actuel.num_joueur+1, BLU, NRM);
		}
		else {
			fprintf(stderr, "%s[ERR] : le joueur attendu n'est ni un Humain, ni une IA.%s\n", RED, NRM);
			exit(ERREUR_TOUR_JEU);
		}
		
		if (joueur_actuel.num_joueur == JOUEUR_2)
			fini=1;
		
	/* Gestion du tour suivant */
		gestion_joueur(&joueur_actuel, J1, J2);
		
		//~ joueur++;
	} while (!fini);
	
	return FIN_DU_JEU;
}
