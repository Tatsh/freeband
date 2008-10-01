#include "freeband.h"

/* Defaults for video */
#define DEFSCREENWIDTH  800
#define DEFSCREENHEIGHT 600
#define COLORBITDEPTH   24

bool testSDL()
{
  /* Test SDL video */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Unable to initialise SDL: %s\n", SDL_GetError());
    return false;
  }
  /* Test SDL_ttf */
  else if (TTF_Init() == -1) {
    printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
    return false;
  }
  else
    return true;
}

void startGame(int gameMode) {}

#ifdef __GL__
void goOnline_GL() {}

void showOptionsMenu_GL() {}
#endif

int main(int arg, char *argv[]) {
  /* Test SDL first */
  if (testSDL() != true) {
    printf("SDL test failed.\n");
    return 1;
  }
  else
    printf("SDL test succeeded. Game starting.\n");

  SDL_WM_SetCaption("Freeband", "Freeband"); /* Set window title */

#ifdef __GL__
  /* These are SDL/OpenGL functions */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); /* Enable SDL OpenGL Double-buffering */
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); /* Force hardware acceleration */
  SDL_GL_SetAttribute(SDL_HWACCEL, 1);
  SDL_GL_SetAttribute(SDL_HWPALETTE, 1); /* Store palette in hardware */

  /* Set window 800x600 with 24-bit colours, with OpenGL enabled */
  SDL_Surface *screen;
  /* Later read this information from file */
  screen = SDL_SetVideoMode(DEFSCREENWIDTH, DEFSCREENHEIGHT, COLORBITDEPTH, SDL_OPENGL);
  if (screen == NULL)
  {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    return 1;
  }

  /* Initialise OpenGL */
  init_GL();
#endif

  /* Obviously we start the game at the main menu. Later on, listen to arguments like --testmode for testing files. */
  showMainMenu();

  return EXIT_SUCCESS;
}
