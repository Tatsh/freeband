#ifndef FREEBAND_H
#define FREEBAND_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define SCREENHEADTEXTHT 0.31f

typedef struct {
  bool mainMenu;
  bool multiPlayer;
  bool online;
  bool options;
  bool instruments;
  bool songs;
  bool difficulty;
  bool game;
  bool pause;
} tCurrentScreen;

extern bool menuQuit;

extern GLuint fb_nPlayers;

extern tCurrentScreen fb_screen;

/* General functions only */
GLvoid fb_quit(GLint retnCode);

#endif
