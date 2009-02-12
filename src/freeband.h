#ifndef FREEBAND_H
#define FREEBAND_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *nix and Mingw only */
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

#ifdef __WIN32__
#include <windows.h>
#endif

#define ERROR_VERIFYING_PREFS 10
#define ERROR_READING_PREFS 11

#define SCREENHEADTEXTHT 0.31f
#define SCREENHEADTEXTOFFSET -1.05f

#define BPP 32

#ifdef __WIN32__
typedef unsigned short ushort;
#endif

typedef ushort score_t;
typedef ushort combo_t;
typedef ushort stars_t;
typedef ushort multiplier_t;

typedef struct {
  bool mainMenu;
  bool multiPlayer;
  bool online;
  bool options;
  bool instruments;
  bool songs;
  bool difficulty;
  bool game;
} screen_s;

extern bool menuQuit;

extern ushort fb_nPlayers;

extern screen_s fb_screen;

/* General functions only */
GLvoid fb_quit(GLint retnCode);

#endif
