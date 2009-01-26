#ifndef FREEBAND_H
#define FREEBAND_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Mingw only */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <portaudio.h>

#include <sndfile.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define ERROR_CANNOT_CREATE_PREFS_DIRECTORY 10

#define SCREENHEADTEXTHT 0.31f
#define SCREENHEADTEXTOFFSET -1.05f

typedef unsigned int score_t;
typedef unsigned int combo_t;
typedef unsigned int stars_t;
typedef unsigned int multiplier_t;

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
} screen_s;

extern bool menuQuit;

extern GLuint fb_nPlayers;

extern screen_s fb_screen;

/* General functions only */
GLvoid fb_quit(GLint retnCode);

#endif
