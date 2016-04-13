#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sauvegarde.h"
#include "coordonnee.h"
#include "pion.h"

struct save_s {
    Plateau p;
    bool tour;
};

Save save_init() {
    Save s = (Save)malloc(sizeof(struct save_s));
    assert(s != NULL);
    return s;
}

Save save_set(Save s, Plateau p, bool tour) {
    s->p = p;
    s->tour = tour;
    return s;
}

bool save_sauvegarder(Save s, char *fichier) {
    FILE* file = NULL;
    if ((file = fopen(fichier, "w")) != NULL) {
        Coordonnee coord = coord_init();
        for (unsigned int i = 0; i < TAILLE; i++) {
            coord = coord_set_x(coord, i);
            for (unsigned int j = 0; j < TAILLE; j++) {
                coord = coord_set_y(coord, j);
                Pion p = plateau_get_pion(s->p, coord);
                if (p == NULL)
                    fprintf(file, "%d", 0);
                else {
                    if (pion_get_couleur(p) == ROUGE)
                        fprintf(file, "%d", 1);
                    else
                        fprintf(file, "%d", 2);
                }
            }
            fprintf(file, "%c", '\n');
        }
        if (s->tour)
            fprintf(file, "%d", 0);
        else
            fprintf(file, "%d", 1);
        fclose(file);
        return true;
    } else
        perror("fopen()");
    return false;
}

bool save_charger(Plateau* p, bool* tour, char *fichier) {
    FILE* file = NULL;
    if ((file = fopen(fichier, "r")) != NULL) {
        Coordonnee coord = coord_init();
        for (unsigned int i = 0; i < TAILLE; i++) {
            coord = coord_set_x(coord, i);
            for (unsigned int j = 0; j < TAILLE; j++) {
                coord = coord_set_y(coord, j);
                int joueur;
                Pion pion = pion_init();
                fscanf(file, "%d", &joueur);
                pion = pion_set(pion, coord, joueur);
                if (!plateau_placer_pion(p, pion))
                    fprintf(stderr, "Erreur de lecture du fichier !\n");
            }
            fseek(file, 1, SEEK_CUR);
        }
        fclose(file);
        return true;
    } else
        perror("fopen()");
    return false;
}
