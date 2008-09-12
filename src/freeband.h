/* Nearly all source needs this header */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
int SDLtest();

/* Optional includes */
/* #ifdef __D3D__
#include <windows.h>
int d3dTest();
#endif */

#ifdef __GL__
#include "SDL/SDL_opengl.h"
void enableMenuGL();
#endif

/* Function definitions */
/* Main menu */
void showMainMenu();
void retnMainMenu();

