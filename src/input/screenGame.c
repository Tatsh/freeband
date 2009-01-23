#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../screens/difficulty.h"
#include "../screens/game.h"
#include "../screens/instruments.h"
#include "../screens/main.h"
#include "../screens/pause.h"
#include "../screens/songs.h"
#include "input.h"
#include "screenGame.h"

GLvoid input_screenGamePause() {
  graphics_loading = true;
  menuQuit = fb_screen.game = false;
  graphics_clear();
  screenPause_buffer();
  fb_screen.pause = gamePaused = true;
  graphics_loading = false;
#ifdef __DEBUG__
  fprintf(stdout, "Now in screenGame() function.\n");
#endif
  
  return;
}

GLvoid input_screenGame() {
  Uint8 *keystates = SDL_GetKeyState(NULL);

  if (keystates[SDLK_F1])
    screenGame_button.g = true;
  else
    screenGame_button.g = false;
  
  if (keystates[SDLK_F2])
    screenGame_button.r = true;
  else
    screenGame_button.r = false;
  
  if (keystates[SDLK_F3])
    screenGame_button.y = true;
  else
    screenGame_button.y = false;
  
  if (keystates[SDLK_F4])
    screenGame_button.b = true;
  else
    screenGame_button.b = false;
  
  if (keystates[SDLK_F5])
    screenGame_button.o = true;
  else
    screenGame_button.o = false;
  
  return;
}
