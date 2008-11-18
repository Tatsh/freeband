#include "freeband.h"

#define WIDTH 800
#define HEIGHT 600
#define BPP 32

char windowTitle[] = "Freeband";

char *bgTexture = "GameData/themes/default/global/bg.png";
char *logoTexture = "GameData/themes/default/screenStart/banner.png";
char *mainSelector = "GameData/themes/default/screenStart/selector.png";

SDL_Surface *fbSurface; /* Main game surface */

tCurrentScreen currentScreen;

void quitGame(int retnCode) {
  glDeleteTextures( MAX_TEXTURES, &texture[0] );
  SDL_Quit();     /* Clean window */
  exit(retnCode);
}

int main(int argc, char *argv[]) {
  int i;
  for (i = 0; i < 10; i++)
    texture[i] = -1;
  
  int videoFlags;                   /* Flags to send to SDL */
  bool hasQuit = false;             /* Main game loop variable */
  SDL_Event freeband;               /* Event collector */

  const SDL_VideoInfo *videoInfo;   /* Holds info about current display */

  /* Initialise SDL */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Video initialisation failed: %s.\n", SDL_GetError());
    quitGame(1);
  }
  
  videoInfo = SDL_GetVideoInfo(); /* Get video information */
  if (!videoInfo) {
    fprintf(stderr, "Video query failed: %s.\n", SDL_GetError());
    quitGame(1);
  }

  videoFlags = SDL_OPENGL;            /* Enable OpenGL */
  videoFlags |= SDL_GL_DOUBLEBUFFER;  /* Enable double-buffering */
  videoFlags |= SDL_HWPALETTE;        /* Enable storing palettes in hardware */
  videoFlags |= SDL_RESIZABLE;        /* Enable window resizing */

  if (videoInfo->hw_available) /* Check if surfaces can be stored in video memory */
    videoFlags |= SDL_HWSURFACE;
  else
    videoFlags |= SDL_SWSURFACE;

  if (videoInfo->blit_hw) /* Check if hardware blits can be done */
    videoFlags |= SDL_HWACCEL;

  fbSurface = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, videoFlags); /* Get a SDL surface */
  if (!fbSurface) {
    fprintf(stderr,  "Video mode set failed: %s.\n", SDL_GetError());
    quitGame(1);
  }
  
  if ((SDL_EnableKeyRepeat(100, SDL_DEFAULT_REPEAT_INTERVAL))) { /* Enable key repeat */
    fprintf(stderr, "Setting keyboard repeat failed: %s\n", SDL_GetError());
    quitGame(1);
  }

  if (initGL() != true) {
    fprintf(stderr, "Unable to initialise OpenGL.\n");
    quitGame(1);
  }
  
  SDL_WM_SetCaption(windowTitle, windowTitle); /* Set window title */

  resizeWindow(WIDTH, HEIGHT);
  
  currentScreen.mainMenu = true; /* Set to main screen */
  
  /* Load main menu textures */
  if ((texture[0] = loadTexture(bgTexture, 0)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", bgTexture);

  if ((texture[1] = loadTexture(logoTexture, 1)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", logoTexture);
  
  if ((texture[2] = loadTexture(mainSelector, 2)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", mainSelector);
  
  while (!hasQuit) {
    
    while (SDL_PollEvent(&freeband)) {
      
      switch(freeband.type) {

        case SDL_VIDEORESIZE: /* Handle resize event */
          fbSurface = SDL_SetVideoMode(freeband.resize.w, freeband.resize.h, 32, videoFlags);
          if (!fbSurface) {
            fprintf(stderr, "Could not get a surface after resize: %s.\n", SDL_GetError());
            quitGame(1);
          }
          resizeWindow(freeband.resize.w, freeband.resize.h);
#ifdef __DEBUG__
          fprintf(stdout, "Window resized.\n");
#endif
          break;
          
        case SDL_KEYDOWN: /* Handle key down event */
          menuKeys(&freeband.key.keysym, fbSurface);
#ifdef __DEBUG__
          fprintf(stdout, "Key pressed.\n");
#endif
          break;
          
        case SDL_QUIT:
          hasQuit = true;
#ifdef __DEBUG__
          fprintf(stdout, "Quitting...\n");
#endif
          break;
          
        default:
          break;

      }

    }

    drawFreeband();

  }

  quitGame(0);
  
  return 0;
}
