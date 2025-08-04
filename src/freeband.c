#include "freeband.h"
#include "audio/audio.h"
#include "graphics/graphics.h"
#include "graphics/text.h"
#include "input/input.h"
#include "input/screenGame.h"
#include "io/keys.h"
#include "io/languages.h"
#include "io/prefs.h"
#include "screens/game.h"
#include "screens/instruments.h"
#include "screens/main.h"
#include "screens/songs.h"

bool menuQuit;

char windowTitle[] = "Freeband";

GLcoordsY text_SinglePlayerY[] = {0.0f, MENUITEMSHT, MENUITEMSHT, 0.0f};
GLcoordsY text_MultiplayerY[4], text_OnlineY[4], text_OptionsY[4], text_QuitY[4];

ushort fb_nPlayers = 1;     /* Number of players */
GLuint texture[MAX_IMAGES]; /* Normal images */
GLuint text[MAX_TEXT];      /* Text only! */

SDL_Event freeband;     /* Main event collector */
SDL_Surface *fbSurface; /* Main game surface */
SDL_Joystick *joy;      /* Space for controllers */

screen_s fb_screen; /* The current screen */

void fb_quit(GLint retnCode) {
  ushort i;
  PaError err;

  err = Pa_Terminate();
  if (err != paNoError)
    fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
#ifndef NDEBUG
  else
    fprintf(stdout, "PortAudio terminated successfully.\n");
#endif

  glDeleteTextures(MAX_IMAGES, &texture[0]);
  glDeleteTextures(MAX_TEXT, &text[0]);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  gluDeleteQuadric(quadratic);

  for (i = 0; i < 3; i++) {
    if (SDL_JoystickOpened(i))
      SDL_JoystickClose(joy);
  }

  iniparser_freedict(lang_d);
  iniparser_freedict(prefs);
#ifndef NDEBUG
  fprintf(stdout, "Freed language INI dictionary.\n");
  fprintf(stdout, "Freed preferences INI dictionary.\n");
#endif

  TTF_Quit();
  SDL_Quit(); /* Clean window */
#ifndef NDEBUG
  fprintf(stdout, "Quitting...\n");
#endif
  exit(retnCode);
}

int main(int argc, char *argv[]) {
  ushort i;

  for (i = 0; i < MAX_IMAGES; i++)
    texture[i] = 0;
  for (i = 0; i < MAX_TEXT; i++)
    text[i] = 0;

  glutInit(&argc, argv); /* Initialise GLUT */

  if (!prefs_verify()) /* Verify preferences existence or create if does not exist (first launch) */
    fb_quit(ERROR_VERIFYING_PREFS);

  if (!prefs_load())
    fb_quit(ERROR_READING_PREFS);

  int videoFlags;       /* Flags to send to SDL */
  bool hasQuit = false; /* Main game loop variable */

  const SDL_VideoInfo *videoInfo; /* Holds info about current display */

  /* Initialise SDL */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Video initialisation failed: %s.\n", SDL_GetError());
    fb_quit(1);
  }

  /* Initialise SDL joystick subsystem */
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  SDL_JoystickEventState(SDL_ENABLE);
  if (SDL_NumJoysticks() > 0) { /* This only checks for 1 joystick */
    joy = SDL_JoystickOpen(0);
    if (joy) {
      fprintf(stdout, "Found joystick at port %d\n", 0);
      fprintf(stdout, "Name: %s\n", SDL_JoystickName(0));
      fprintf(stdout, "# of Axes: %d\n", SDL_JoystickNumAxes(joy));
      fprintf(stdout, "# of Buttons: %d\n", SDL_JoystickNumButtons(joy));
      fprintf(stdout, "# of Balls: %d\n", SDL_JoystickNumBalls(joy));
    } else
      printf("There is no joystick at port %d\n", 0);
  }

  /* Initialise SDL_ttf */
  if (TTF_Init() < 0) {
    fprintf(stderr, "Could not initialise SDL_ttf: %s.\n", TTF_GetError());
    fb_quit(1);
  }

  videoInfo = SDL_GetVideoInfo(); /* Get video information */
  if (!videoInfo) {
    fprintf(stderr, "Video query failed: %s.\n", SDL_GetError());
    fb_quit(1);
  }

  videoFlags = SDL_OPENGL;           /* Enable OpenGL */
  videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double-buffering */
  videoFlags |= SDL_HWPALETTE;       /* Enable storing palettes in hardware */
  videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

  if (videoInfo->hw_available) /* Check if surfaces can be stored in video memory */
    videoFlags |= SDL_HWSURFACE;
  else
    videoFlags |= SDL_SWSURFACE;

  if (videoInfo->blit_hw) /* Check if hardware blits can be done */
    videoFlags |= SDL_HWACCEL;

  if (PREF_FULLSCREEN)
    videoFlags |= SDL_FULLSCREEN;

  languages_loadLanguage(en_GB);

  fbSurface =
    SDL_SetVideoMode(PREF_WIDTH, PREF_HEIGHT, PREF_BPP, videoFlags); /* Get a SDL surface */
  if (!fbSurface) {
    fprintf(stderr, "Video mode set failed: %s.\n", SDL_GetError());
    fb_quit(1);
  }

  if (SDL_EnableKeyRepeat(100, SDL_DEFAULT_REPEAT_INTERVAL) != 0) { /* Enable key repeat */
    fprintf(stderr, "Setting keyboard repeat failed: %s\n", SDL_GetError());
    fb_quit(1);
  }

  if (!graphics_initGL()) {
    fprintf(stderr, "Unable to initialise OpenGL.\n");
    fb_quit(1);
  }

  SDL_WM_SetCaption(windowTitle, windowTitle); /* Set window title */

  SDL_Surface *icon = IMG_Load(
    "freeband.png"); /* Creates icon for window and task bar on Linux, but only task bar on Windows */
  SDL_WM_SetIcon(icon, NULL);

  graphics_resizeWindow(PREF_WIDTH, PREF_HEIGHT);
  graphics_initColours(); /* Initialise colours */

  fb_screen.mainMenu = true; /* Set to main screen */
  menuQuit = false;          /* Have we left a menu yet? */

  /* Buffer audio */
  if (!audio_buffer()) {
    fprintf(stderr, "Unable to initialise audio.\n");
    fb_quit(1);
  }

  /* Buffer main menu textures and text */
  if (!screenMain_buffer()) {
    fprintf(stderr, "Unable to buffer screenMain.\n");
    fb_quit(1);
  }

  /* Generate arrays of Y coordinates for each text, based upon initial position of Single Player */
  for (i = 0; i < 4; i++)
    text_MultiplayerY[i] = text_SinglePlayerY[i] + 0.2;
  for (i = 0; i < 4; i++)
    text_OnlineY[i] = text_MultiplayerY[i] + 0.2;
  for (i = 0; i < 4; i++)
    text_OptionsY[i] = text_OnlineY[i] + 0.2;
  for (i = 0; i < 4; i++)
    text_QuitY[i] = text_OptionsY[i] + 0.21;

  SDL_EnableKeyRepeat(0, 0);

  while (!hasQuit) {

    while (SDL_PollEvent(&freeband)) {

      switch (freeband.type) {

        case SDL_VIDEORESIZE: /* Handle resize event */
          fbSurface = SDL_SetVideoMode(freeband.resize.w, freeband.resize.h, PREF_BPP, videoFlags);
          if (!fbSurface) {
            fprintf(stderr, "Could not get a surface after resize: %s.\n", SDL_GetError());
            fb_quit(1);
          }
          if (!(graphics_resizeWindow(freeband.resize.w, freeband.resize.h))) {
            fprintf(stderr, "Could not resize window.\n");
            fb_quit(1);
          }
          break;

        case SDL_KEYDOWN: /* Handle key down event */
          if (!fb_screen.game)
            input_menuKeys(&freeband.key.keysym, fbSurface);
          else {
            input_menuKeys(&freeband.key.keysym, fbSurface);
            input_screenGame();
          }
          break;

        case SDL_KEYUP:
          if (fb_screen.game)
            input_screenGame();
          break;

#ifdef __XBOX360XPLORER__
        case SDL_JOYBUTTONDOWN: /* Xbox 360 controller only; non-production code! */
        case SDL_JOYBUTTONUP: /* This works ONLY if you have the xboxdrv-linux user-space driver running! */
          if (fb_screen.game) {
            screenGame_button.g = SDL_JoystickGetButton(joy, 7);
            screenGame_button.r = SDL_JoystickGetButton(joy, 8);
            screenGame_button.y = SDL_JoystickGetButton(joy, 9);
            screenGame_button.b = SDL_JoystickGetButton(joy, 10);
            screenGame_button.o = SDL_JoystickGetButton(joy, 11);
          }
          break;

          /*case SDL_JOYAXISMOTION:
          printf("jaxis: which=%u axis=%u value=%d\n", freeband.jaxis.which, freeband.jaxis.axis, freeband.jaxis.value);
          break;*/
#elif defined(__WIN32XBOX360XPLORER__)
        case SDL_JOYBUTTONDOWN: /* Xbox 360 controller only; non-production code! */
        case SDL_JOYBUTTONUP:   /* Do not define both of these! Windows only! */
          if (fb_screen.game) {
            screenGame_button.g = SDL_JoystickGetButton(joy, 0);
            screenGame_button.r = SDL_JoystickGetButton(joy, 1);
            screenGame_button.y = SDL_JoystickGetButton(joy, 3);
            screenGame_button.b = SDL_JoystickGetButton(joy, 2);
            screenGame_button.o = SDL_JoystickGetButton(joy, 4);
          }
          break;
#endif

        case SDL_QUIT: /* Only allow to exit via ^C or close button if at main menu */
          if (fb_screen.mainMenu)
            hasQuit = true;
          else if (fb_screen.instruments) {
            menuQuit = graphics_loading = true;
            graphics_clear();
            screenMain_buffer();
            fb_screen.instruments = graphics_loading = menuQuit = false;
            fb_screen.mainMenu = true;
#ifndef NDEBUG
            fprintf(stdout, "Switched back to screenMain.\n");
#endif
          } else if (fb_screen.songs) {
            menuQuit = graphics_loading = true;
            graphics_clear();
            screenInstruments_buffer();
            fb_screen.instruments = graphics_loading = menuQuit = false;
            fb_screen.instruments = true;
#ifndef NDEBUG
            fprintf(stdout, "Switched back to screenInstruments.\n");
#endif
          } else if (fb_screen.difficulty) {
            menuQuit = graphics_loading = true;
            graphics_clear();
            screenSongs_buffer();
            fb_screen.difficulty = graphics_loading = menuQuit = false;
            fb_screen.songs = true;
#ifndef NDEBUG
            fprintf(stdout, "Switched back to screenSongs.\n");
#endif
          } else if (fb_screen.game && gamePaused) {
            gamePaused = false;
#ifndef NDEBUG
            fprintf(stdout, "Game resumed.\n");
#endif
          } else if (fb_screen.game && !gamePaused) {
            gamePaused = true;
#ifndef NDEBUG
            fprintf(stdout, "Game paused.\n");
#endif
          }
          break;

        default:
          break;
      }
    }

    graphics_draw();
  }

  SDL_FreeSurface(icon);

  fb_quit(0);

  return 0;
}
