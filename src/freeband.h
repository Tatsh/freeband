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

void showMainMenu(); /* Main menu, returns game mode */
int mainMenuUpDown(SDL_keysym *keysym); /* Handle up and down on the main menu, return game mode */

#ifdef __GL__
#include "SDL/SDL_opengl.h"
void init_GL(); /* General OpenGL functionality */
int loadTexture_GL(char *image, int *vertexW, int *vertexH, float *alphaValues);  /* General load texture function */

void reloadStaticMenuItems_GL();  /* Refresh main menu */

void useSelector_GL(int translateV);

void loadSongsMenu_GL();  /* Songs menu */

void goOnline_GL(); /* Online menu */

void showOptionsMenu_GL(); /* Options menu */

void selectInstrument_GL(int instances); /* Menu to select instrument */
#endif
