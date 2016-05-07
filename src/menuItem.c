#include <assert.h>
#include "menuItem.h"

struct menuItem_s {
    char *name;
    SDL_Surface *menuScreen;
    SDL_Rect *position;
    bool selected;
};typedef struct menuItem_s* menuItem;



menuItem mnit_init() {
    menuItem mn = (menuItem)malloc(sizeof(struct menuItem_s));
    assert(mn != NULL);
    mn->name = NULL;
    mn->menuScreen = NULL;
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
    free(mn->name);
    free(mn->position);
    free(mn);
}

menuItem mnit_set_name(menuItem mn, char *name) {
    mn->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    assert(mn->name != NULL);
    strcpy(mn->name, name);
    return mn;
}

char *mnit_get_name(menuItem mn) {
    return mn->name;
}

menuItem mnit_set_surface(menuItem mn, SDL_Surface *surface) {
    mn->menuScreen = surface;
    return mn;
}

SDL_Surface *mnit_get_surface(menuItem mn) {
    return mn->menuScreen;
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

bool mnit_get_selected(menuItem mn) {
    return mn->selected;
}