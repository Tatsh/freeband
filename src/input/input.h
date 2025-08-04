#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define RETURN 4
#define ESC 5

void input_menuKeys(SDL_keysym *keysym, SDL_Surface *surface);

#endif
