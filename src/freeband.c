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

/*GLfloat text_SinglePlayerY[] = { -0.035f, 0.20f, 0.20f, -0.035f };*/ /* 'Single Player' text's default position */
GLfloat text_SinglePlayerY[] = { 0.0f, MENUITEMSHT, MENUITEMSHT, 0.0f };
GLfloat text_MultiplayerY[4], text_OnlineY[4], text_OptionsY[4], text_QuitY[4];

GLuint nPlayers; /* Number of players */
GLuint texture[MAX_IMAGES]; /* Normal images */
GLuint text[MAX_TEXT]; /* Text only! */

SDL_Event freeband;     /* Event collector */
SDL_Surface *fbSurface; /* Main game surface */
SDL_Joystick *joy;      /* Space for controllers */

tCurrentScreen currentScreen; /* The current screen */

GLuint crilleei = 0; /* Crillee */
GLuint bitstreami = 1; /* Bitstream Vera Sans */
GLuint bitstreamMonoBoldi = 2; /* Bitstream Vera Mono Bold */
GLuint freeSansi = 3; /* FreeSans */
GLuint freeSansBoldi = 4; /* FreeSans Bold */

TTF_Font *crillee, *bitstream, *bitstreamMonoBold, *freeSans, *freeSansBold;

GLvoid quitGame(GLint retnCode) {
  GLuint i;

  glDeleteTextures( MAX_IMAGES, &texture[0] );
  glDeleteTextures( MAX_TEXT, &text[0] );
  gluDeleteQuadric( quadratic );

  for ( i = 0; i < 3; i++ ) {
    if(SDL_JoystickOpened(i))
      SDL_JoystickClose(joy);
  }

  TTF_Quit();
  SDL_Quit();     /* Clean window */
#ifdef __DEBUG__
  fprintf(stdout, "Quitting...\n");
#endif
  exit(retnCode);
}

GLint main(GLint argc, char *argv[]) {
  GLuint i;
  for (i = 0; i < MAX_IMAGES; i++) texture[i] = -1;
  for (i = 0; i < MAX_TEXT; i++) text[i] = -1;

  alutInit(&argc, argv);  /* ALUT */
  glutInit(&argc, argv);  /* GLUT */
  
  int videoFlags;                   /* Flags to send to SDL */
  bool hasQuit = false;             /* Main game loop variable */

  const SDL_VideoInfo *videoInfo;   /* Holds info about current display */
  
  /* Initialise SDL */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Video initialisation failed: %s.\n", SDL_GetError());
    quitGame(1);
  }
  
  /* Initialise SDL joystick subsystem */
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  SDL_JoystickEventState(SDL_ENABLE);
  if(SDL_NumJoysticks() > 0) { /* This only checks for 1 joystick */
    joy=SDL_JoystickOpen(0);
    if(joy) {
      fprintf(stdout, "Found joystick at port %d\n", 0);
      fprintf(stdout, "Name: %s\n", SDL_JoystickName(0));
      fprintf(stdout, "# of Axes: %d\n", SDL_JoystickNumAxes(joy));
      fprintf(stdout, "# of Buttons: %d\n", SDL_JoystickNumButtons(joy));
      fprintf(stdout, "# of Balls: %d\n", SDL_JoystickNumBalls(joy));
    }
    else
      printf("There is no joystick at port %d\n", 0);
  }

  /* Initialise SDL_ttf */
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
          if (!menuQuit || gamePaused)
            menuKeys(&freeband.key.keysym, fbSurface);
          else
            gameKeys(&freeband.key.keysym, fbSurface, nPlayers);
          break;

        case SDL_KEYUP:
          if (currentScreen.game) {
            gameKeys(&freeband.key.keysym, fbSurface, nPlayers);
          }
          break;

#ifdef __XBOX360XPLORER__
        case SDL_JOYBUTTONDOWN: /* Xbox 360 controller only; non-production code! */
        case SDL_JOYBUTTONUP: /* This works ONLY if you have the xboxdrv-linux user-space driver running! */
          if (currentScreen.game) {
            button.g = SDL_JoystickGetButton(joy, 7);
            button.r = SDL_JoystickGetButton(joy, 8);
            button.y = SDL_JoystickGetButton(joy, 9);
            button.b = SDL_JoystickGetButton(joy, 10);
            button.o = SDL_JoystickGetButton(joy, 11);
          }
          break;

        /*case SDL_JOYAXISMOTION:
          printf("jaxis: which=%u axis=%u value=%d\n", freeband.jaxis.which, freeband.jaxis.axis, freeband.jaxis.value);
          break;*/
#endif

#ifdef __WIN32XBOX360XPLORER__
        case SDL_JOYBUTTONDOWN: /* Xbox 360 controller only; non-production code! */
        case SDL_JOYBUTTONUP: /* Do not define both of these! Windows only! */
          if (currentScreen.game) {
            button.g = SDL_JoystickGetButton(joy, 0);
            button.r = SDL_JoystickGetButton(joy, 1);
            button.y = SDL_JoystickGetButton(joy, 3);
            button.b = SDL_JoystickGetButton(joy, 2);
            button.o = SDL_JoystickGetButton(joy, 4);
          }
          break;
#endif

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
            fprintf(stdout, "Switched back to screenMain.\n");
#endif
          }
          else if (currentScreen.songs) {
            menuQuit = loading = true;
            clearScreen();
            setInstrumentsImages_1P();
            setInstrumentsText_1P();
            currentScreen.instruments = loading = menuQuit = false;
            currentScreen.instruments = true;
#ifdef __DEBUG__
            fprintf(stdout, "Switched back to screenInstruments.\n");
#endif
          }
          else if (currentScreen.difficulty) {
            menuQuit = loading = true;
            clearScreen();
            screenSongsBuffer();
            currentScreen.difficulty = loading = menuQuit = false;
            currentScreen.songs = true;
#ifdef __DEBUG__
            fprintf(stdout, "Switched back to screenSongs.\n");
#endif
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
