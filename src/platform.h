#ifndef FREEBAND_PLATFORM_H
#define FREEBAND_PLATFORM_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#endif
#include <GL/glut.h>

#endif
