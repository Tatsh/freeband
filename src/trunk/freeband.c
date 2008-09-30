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

void startGame(int gameMode) {
}

#ifdef __GL__
void goOnline_GL(){}

void showOptionsMenu_GL(){}
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

  int mainMenuSelection;

#ifdef __GL__
  /* These are SDL/OpenGL functions */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); /* Enable SDL OpenGL Double-buffering */
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); /* Force hardware acceleration */

  /* Set window 800x600 with 24-bit colours, with OpenGL enabled */
  SDL_Surface *screen;
  /* Later read this information from file */
  screen = SDL_SetVideoMode(DEFSCREENWIDTH, DEFSCREENHEIGHT, COLORBITDEPTH, SDL_OPENGL);
  if (screen == NULL)
  {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    return 1;
  }
#endif

  /* First we find out what user selected on the Main Menu. Then, we start the game or any other functionality.
     The startGame() function is a loop that can result in coming back to main menu, but can never quit the game on its own. */
  mainMenuSelection = showMainMenu(); /* screens/start.c */
  if (mainMenuSelection == 1) { /* Single player mode */
#ifdef __DEBUG__
    printf("Starting single player game.\n");
#endif
    startGame(1);
  }
  else if (mainMenuSelection == 2) { /* Multiplayer mode */
#ifdef __DEBUG__
    printf("Starting multiplayer game.\n");
#endif
    startGame(2);
  }
  else if (mainMenuSelection == 3) { /* Online menu */
#ifdef __DEBUG__
    printf("Displaying online menu.\n");
#endif
#ifdef __GL__
    goOnline_GL();
#endif
  }
  else if (mainMenuSelection == 4) { /* Options menu */
#ifdef __DEBUG__
    printf("Displaying options menu.\n");
#endif
#ifdef __GL__
    showOptionsMenu_GL();
#endif
  }

  return EXIT_SUCCESS;
}
