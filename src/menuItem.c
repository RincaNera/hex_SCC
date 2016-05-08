#include <assert.h>
#include <string.h>
#include "menuItem.h"

struct menuItem_s {
    SDL_Surface *selected_s;
    SDL_Surface *not_selected_s;
    SDL_Rect *position;
    bool selected;
};

menuItem mnit_init() {
    menuItem mn = (menuItem)malloc(sizeof(struct menuItem_s));
    assert(mn != NULL);
    mn->selected_s = NULL;
    mn->not_selected_s = NULL;
    mn->position = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    assert(mn->position != NULL);
	mn->position->x = 0;
	mn->position->y = 0;
	mn->position->h = 0;
	mn->position->w = 0;
    mn->selected = false;
    return mn;
}

void mnit_destroy(menuItem mn) {
    if(mn != NULL) {
    SDL_FreeSurface(mn->selected_s);
    SDL_FreeSurface(mn->not_selected_s);
    free(mn->position);
    free(mn);
    }
}

menuItem mnit_set_selected_surface(menuItem mn, SDL_Surface *surface) {
    mn->selected_s = surface;
    return mn;
}

menuItem mnit_set_not_selected_surface(menuItem mn, SDL_Surface *surface) {
    mn->not_selected_s = surface;
    return mn;
}

SDL_Surface *mnit_get_selected_surface(menuItem mn) {
    return mn->selected_s;
}

SDL_Surface *mnit_get_not_selected_surface(menuItem mn) {
    return mn->not_selected_s;
}

menuItem mnit_set_position(menuItem mn, SDL_Rect *position) {
    mn->position = position;
    return mn;
}

SDL_Rect* mnit_get_position(menuItem mn) {
    return mn->position;
}

menuItem mnit_set_selected(menuItem mn, bool s) {
    mn->selected = s;
    return mn;
}

bool mnit_is_selected(menuItem mn) {
    return mn->selected;
}

bool mnit_is_over(menuItem mn, Curseur* c) {
    if (c->x >= mn->position->x && c->x <= mn->position->x + mn->position->w && c->y >= mn->position->y && c->y <= mn->position->y + mn->position->h)
        return true;
    else
        return false;
}
