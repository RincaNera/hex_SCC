#include "jeu.h"
#include "IA.h"

void afficher_message(Item** message, int n) {
    switch (n) {
        case 0:
            message[0]->on_screen = true;
            message[1]->on_screen = false;
            message[2]->on_screen = false;
            message[3]->on_screen = false;
            message[4]->on_screen = false;
		    message[5]->on_screen = false;
		    message[6]->on_screen = false;
            break;
        case 1:
            message[0]->on_screen = false;
            message[1]->on_screen = true;
            message[2]->on_screen = false;
            message[3]->on_screen = false;
            message[4]->on_screen = false;
		    message[5]->on_screen = false;
		    message[6]->on_screen = false;
            break;
        case 2:
            message[0]->on_screen = false;
            message[1]->on_screen = false;
            message[2]->on_screen = true;
            message[3]->on_screen = false;
            message[4]->on_screen = false;
		    message[5]->on_screen = false;
		    message[6]->on_screen = false;
            break;
        case 3:
            message[0]->on_screen = false;
            message[1]->on_screen = false;
            message[3]->on_screen = true;
            message[2]->on_screen = false;
            message[4]->on_screen = false;
		    message[5]->on_screen = false;
		    message[6]->on_screen = false;
            break;
        case 4:
            message[4]->on_screen = true;
		    message[5]->on_screen = false;
		    message[6]->on_screen = false;
	    case 5:
		    message[4]->on_screen = false;
		    message[6]->on_screen = true;
		    message[5]->on_screen = false;
	    case 6:
		    message[4]->on_screen = false;
		    message[6]->on_screen = false;
		    message[5]->on_screen = true;
            break;
        default:
            break;
    }
}

void res_placer_pion(Plateau p, int res, bool* tourJ1, Item** message, bool* game, Pion pion, int mode) {
    switch (res) {
        case 0:
            afficher_message(message, 4);
            pion_destroy(&pion);
            break;
        case 1:
            *tourJ1 = !(*tourJ1);
            if (*tourJ1)
                afficher_message(message, 0);
            else
                afficher_message(message, 1);
            break;
        case 2:
            *game = false;
            if (*tourJ1)
                afficher_message(message, 2);
            else
                afficher_message(message, 3);
            break;
        default:
            break;
    }
}

void clic_plateau(Plateau p, Curseur curseur, Item *hexBoard, unsigned int r, unsigned int h, unsigned int s, bool *tourJ1, Item **message, bool *game, int mode) {
    if (curseur.x >= HEXPOS_X && curseur.x <= HEXPOS_X + hexBoard->surface->clip_rect.w && curseur.y >= HEXPOS_Y && curseur.y <= HEXPOS_Y + hexBoard->surface->clip_rect.h) {
        Coordonnee coord = pixel_to_coord(p, HEXPOS_X + 25, HEXPOS_Y + 18, (unsigned int) curseur.x, (unsigned int) curseur.y, r, h, s);
        if (coord != NULL) {
            Pion pion = pion_init();
            pion = pion_set(pion, coord, *tourJ1);
            int res = plateau_placer_pion(&p, pion);
            res_placer_pion(p, res, tourJ1, message, game, pion, mode);
        }
    }
}
