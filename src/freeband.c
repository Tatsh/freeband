#include "freeband.h"

int SDLtest()
{
  /* Test SDL video */
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    printf("Unable to initialise SDL: %s\n", SDL_GetError());
    return 1;
  }
  /* Test SDL_ttf */
  else if (TTF_Init() == -1){
    printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
    return 1;
  }
  else
    return 0;
}

int startupTest()
{
  if (SDLtest() != 0){
    printf("Could not initialise SDL.\n");
    return 1;
  }
  else
    return 0;
}

int main(int argc, char *argv[])
{
  /* Find out results of startupTest, exit it if not successful */
  if (startupTest() != 0){
    printf("Start-up test failed. Quiting.\n");
    return 1;
  }
  else {
    printf("Start-up tests completed successfully.\n");
  }

  SDL_WM_SetCaption("Freeband", "Freeband");

#ifdef __GL__
  /* Enable SDL OpenGL Double-buffering */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  /* Set window 800x600 with 24-bit colours, with OpenGL enabled */
  SDL_Surface *screen;
  screen = SDL_SetVideoMode(800, 600, 24, SDL_OPENGL);
  if (screen == NULL)
  {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    return 1;
  }
#endif

  showMainMenu(); /* screens/start.c */

  return 0;
}
