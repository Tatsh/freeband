#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "GL/gl.h"
#include "GL/glu.h"

#define MAX_TEXTURES 10

/* Variables */
typedef struct {
  bool mainMenu;
  bool multiPlayer;
  bool online;
  bool options;
  bool game;
} tCurrentScreen;

extern tCurrentScreen currentScreen;

GLuint texture[MAX_TEXTURES]; /* Storage space for textures; this is the maximum at any given time */

/* General functions */
void quitGame(int retnCode);

/* Graphics */
bool initGL();
bool resizeWindow(int width, int height);
void drawFreeband(GLvoid);
GLuint loadTexture(const char *filename, int index);
GLvoid positionTexture(GLfloat *vertexX, GLfloat *vertexY, GLfloat *vertexZ);

/* Input */
void gameKeys(SDL_keysym *keysym, SDL_Surface *surface, bool note, int nPlayers);
void menuKeys(SDL_keysym *keysym, SDL_Surface *surface);

/* Menus */
void screenMain();

/* Other screens */
void screenDemo();
