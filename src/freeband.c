#include "freeband.h"
#include "graphics/graphics.h"
#include "input/input.h"
#include "screens/game.h"
#include "screens/instruments.h"
#include "screens/main.h"

#define WIDTH 800
#define HEIGHT 600
#define BPP 32

bool menuQuit;

char windowTitle[] = "Freeband";

GLfloat text_SinglePlayerY[] = { -0.035f, 0.20f, 0.20f, -0.035f }; /* 'Single Player' text's default position */
GLfloat text_MultiplayerY[4], text_OnlineY[4], text_OptionsY[4], text_QuitY[4];

GLuint nPlayers; /* Number of players */
GLuint texture[MAX_IMAGES]; /* Normal images */
GLuint text[MAX_TEXT]; /* Text only! */

SDL_Surface *fbSurface; /* Main game surface */

tCurrentScreen currentScreen; /* The current screen */

GLvoid quitGame(GLint retnCode) {
  glDeleteTextures( MAX_IMAGES, &texture[0] );
  TTF_Quit();
  SDL_Quit();     /* Clean window */
#ifdef __DEBUG__
  fprintf(stdout, "Quitting...\n");
#endif
  exit(retnCode);
}

GLint main(GLint argc, char *argv[]) {
  GLuint i;
  for (i = 0; i < 10; i++)
    texture[i] = -1;
  
  /* GLUT */
  glutInit(&argc, argv);
  
  int videoFlags;                   /* Flags to send to SDL */
  bool hasQuit = false;             /* Main game loop variable */
  SDL_Event freeband;               /* Event collector */

  const SDL_VideoInfo *videoInfo;   /* Holds info about current display */

  /* Initialise SDL */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Video initialisation failed: %s.\n", SDL_GetError());
    quitGame(1);
  }
  
  if(TTF_Init() < 0) {
    fprintf(stderr, "Could not initialise SDL_ttf: %s.\n", TTF_GetError());
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
  
  setupColors(); /* Initialise colours */
  
  currentScreen.mainMenu = true; /* Set to main screen */
  menuQuit = false; /* Have we left a menu yet? */
  
  /* Load main menu textures and text */
  setMainImages();
  setMainText();
  
  /* Generate arrays of Y coordinates for each text, based upon initial position of Single Player */
  for ( i = 0; i < 4; i++ ) text_MultiplayerY[i] = text_SinglePlayerY[i] + 0.2;
  for ( i = 0; i < 4; i++ ) text_OnlineY[i] = text_MultiplayerY[i] + 0.2;
  for ( i = 0; i < 4; i++ ) text_OptionsY[i] = text_OnlineY[i] + 0.2;
  for ( i = 0; i < 4; i++ ) text_QuitY[i] = text_OptionsY[i] + 0.21;
  
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
          break;
          
        case SDL_KEYDOWN: /* Handle key down event */
          if (!menuQuit)
            menuKeys(&freeband.key.keysym, fbSurface);
          else if (!gamePaused)
            gameKeys(&freeband.key.keysym, fbSurface, nPlayers);
          break;
          
        case SDL_QUIT: /* Only allow to exit via ^C or close button if at main menu */
          if (currentScreen.mainMenu)
            hasQuit = true;
          else if (currentScreen.instruments) {
            menuQuit = loading = true;
            clearScreen();
            setMainImages();
            setMainText();
            currentScreen.instruments = loading = menuQuit = false;
            currentScreen.mainMenu = true;
#ifdef __DEBUG__
            fprintf(stdout, "Successfully switched back to screenMain.\n");
#endif
          }
          else if (currentScreen.songs) {
            menuQuit = loading = true;
            clearScreen();
            setInstrumentsImages_1P();
            setInstrumentsText_1P();
            currentScreen.instruments = loading = menuQuit = false;
            currentScreen.instruments = true;
          }
          else if (currentScreen.game)
            hasQuit = true;
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
