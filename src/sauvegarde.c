#define __USE_MISC 1

#include <stdbool.h>
#include <stdio.h>
#include <dirent.h>
#include "sauvegarde.h"

bool save_sauvegarder(Plateau p, bool tourJ1, char *fichier) {
    FILE* file = NULL;
    if ((file = fopen(fichier, "w")) != NULL) {
        Coordonnee coord;
        Pion pion;
        for (unsigned int i = 0; i < TAILLE; i++) {
            for (unsigned int j = 0; j < TAILLE; j++) {
                coord = coord_init();
                coord = coord_set_y(coord, i);
                coord = coord_set_x(coord, j);
                pion = plateau_get_pion(p, coord);
                if (pion == NULL)
                    fprintf(file, "%d", 0);
                else {
                    if (pion_get_couleur(pion) == ROUGE)
                        fprintf(file, "%d", 1);
                    else
                        fprintf(file, "%d", 2);
                }
            }
            fprintf(file, "%c", '\n');
        }
        if (tourJ1)
            fprintf(file, "%d", 0);
        else
            fprintf(file, "%d", 1);
        fclose(file);
        return true;
    } else
        perror("fopen()");
    return false;
}

int save_charger(Plateau* p, bool* tour, char *fichier) {
    FILE* file = NULL;
    char c;
    Coordonnee coord = NULL;
    Pion pion = NULL;
    if ((file = fopen(fichier, "r")) != NULL) {
        for (unsigned int i = 0; i < TAILLE; i++) {
            for (unsigned int j = 0; j < TAILLE; j++) {
                coord = coord_init();
                coord = coord_set_y(coord, i);
                coord = coord_set_x(coord, j);
                pion = pion_init();
                fscanf(file, "%c", &c);
                if (c-48 != 0) {
                    pion = pion_set(pion, coord, (int)c-48);
                    int res = plateau_placer_pion(p, pion);
                    if (res == 0) {
                        fprintf(stderr, "Erreur de lecture du fichier !\n");
                        return 0;
                    } else if (res == 2) {
                        return pion_get_couleur(pion)+1;
                    }
                }
            }
            fseek(file, 1, SEEK_CUR);
        }
        fscanf(file, "%c", &c);
        if (c == 48)
            *tour = false;
        else
            *tour = true;
        fclose(file);
        return 1;
    } else
        perror("fopen()");
    return 0;
}

char** save_page(DIR ** dir, int page) {
    if (*dir == NULL)
        if((*dir = opendir("./saves")) == NULL) {
            fprintf(stderr, "ERROR: Folder files doesn't exist\n");
            exit(5);
        }
    char** names = (char**)malloc(sizeof(char*)*5);
    int i = 0;
    struct dirent* dirent;
    seekdir(dir, page*5);
    while(i < 5) {
        if ((dirent = readdir(*dir)) == NULL) {
            names[i] = (char*)malloc(sizeof(char)*(strlen("Aucun fichier")+1));
            strcpy(names[i++], "Aucun fichier");
        } else {
        names[i] = (char*)malloc(sizeof(char)*(strlen(dirent->d_name)+1));
        strcpy(names[i++], dirent->d_name);
        }
    }
    closedir(*dir);
    return names;
}
