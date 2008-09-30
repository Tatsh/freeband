/* Nearly all source files need these headers */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

/* For convenience only */
bool testSDL();/* Basic SDL test */

/* Game main functions */
void startGame(int gameMode);

int showMainMenu(); /* Main menu, returns game mode */

#ifdef __GL__
#include "SDL/SDL_opengl.h"
void enableMenu_GL(); /* General OpenGL functionality for the 2D menus */
int loadFlatTexture_GL(char *image, int *vertexW, int *vertexH, float *alphaValues);  /* General load flat texture function */
void reloadStaticMenuItems_GL();  /* To reset screen to refresh main menu */
void useSelector_GL(int translateV);

void showSongsMenu_GL();  /* Songs menu */

void goOnline_GL(); /* Online menu */

void showOptionsMenu_GL(); /* Options menu */

void selectInstrument_GL(int instances); /* Menu to select instrument */
#endif
