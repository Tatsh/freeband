#include "../freeband.h"
#include "../audio/audio.h"
#include "../graphics/graphics.h"
#include "../screens/main.h"
#include "../screens/difficulty.h"
#include "../screens/game.h"
#include "../screens/instruments.h"
#include "../screens/songs.h"
#include "input.h"
#include "screenDifficulty.h"
#include "screenInstruments.h"
#include "screenMain.h"
#include "screenSongs.h"

GLvoid input_menuKeys(SDL_keysym *keysym, SDL_Surface *surface) {
  Uint8 *keystates = SDL_GetKeyState(NULL);
  GLuint i;
  online = options = false;
  
  switch (keysym->sym) {
    
    case SDLK_DOWN:
      if (fb_screen.mainMenu)
        input_screenMain(DOWN);
      else if (fb_screen.instruments)
        input_screenInstruments(DOWN);
      else if (fb_screen.difficulty)
        input_screenDifficulty(DOWN);
      break;
      
    case SDLK_UP:
      if (fb_screen.mainMenu)
        input_screenMain(UP);
      else if (fb_screen.instruments)
        input_screenInstruments(UP);
      else if (fb_screen.difficulty)
        input_screenDifficulty(UP);
      break;

    case SDLK_RETURN:
      if (keystates[SDLK_LALT] || keystates[SDLK_RALT]) /* Switch to full screen only if Alt+Enter is pressed */
        SDL_WM_ToggleFullScreen(surface);
      else {
        if (fb_screen.mainMenu)
          input_screenMain(RETURN);
        else if (fb_screen.instruments)
          input_screenInstruments(RETURN);
        else if (fb_screen.songs)
          input_screenSongs(RETURN);
        else if (fb_screen.difficulty)
          input_screenDifficulty(RETURN);
      }
      break;

    case SDLK_ESCAPE:
      if (fb_screen.mainMenu)
        fb_quit(0);
      else if (fb_screen.instruments)
        input_screenInstruments(ESC);
      else if (fb_screen.songs)
        input_screenSongs(ESC);
      else if (fb_screen.difficulty)
        input_screenDifficulty(ESC);
      break;
      
    case SDLK_F8:
      if (fb_screen.songs)
        input_screenSongs(SONG_SORT);
      break;
      
    case SDLK_KP_ENTER:
      if (fb_screen.mainMenu || fb_screen.instruments || fb_screen.songs) {
        if (fb_nPlayers < 4) {
          fb_nPlayers++;
          fprintf(stdout, "Added another player. Number of players: %d.\n", fb_nPlayers);
        }
        else
          fprintf(stderr, "Maximum players is 4.\n");
      }
      break;
      
    case SDLK_q: /* Easter egg. Maybe things like this will help themers in the future */
      if (fb_screen.mainMenu) {
        for ( i = 0; i < 4; i++ )
          screenMain_logoX[i] = screenMain_logoX[i] - 0.01;
      }
      break;
      
    case SDLK_w:
      if (fb_screen.mainMenu) {
        for ( i = 0; i < 4; i++ )
          screenMain_logoX[i] = screenMain_logoX[i] + 0.01;
      }
      break;

    default:
      break;
  }

  return;
}

GLvoid input_gameKeys(SDL_keysym *keysym, SDL_Surface *surface) {
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
  
  switch (keysym->sym) {

    case SDLK_RETURN:
      if (keysym->mod & KMOD_ALT) /* Switch to full screen only if Alt+Enter is pressed */
        SDL_WM_ToggleFullScreen(surface);
      break;
      
    case SDLK_ESCAPE:
      bringDownAngle = 90.0f; /* Reset track */
      NE_coord_neg = 0.0f;
      NE_coord_pos = 1.0f;
      graphics_loading = gamePaused = true;
      fb_screen.game = menuQuit = false;
      graphics_clear();
      screenSongs_buffer();
      graphics_loading = false;
      fb_screen.songs = true;
#ifdef __DEBUG__
      fprintf(stdout, "Switched back to screenSongs.\n");
#endif
      break;

    default:
      break;

  }
  
  return;
}
