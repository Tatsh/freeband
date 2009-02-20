#include "../freeband.h"
#include "../audio/audio.h"
#include "../graphics/graphics.h"
#include "../io/joypad.h"
#include "../io/keys.h"
#include "../screens/main.h"
#include "../screens/difficulty.h"
#include "../screens/game.h"
#include "../screens/instruments.h"
#include "../screens/pause.h"
#include "../screens/songs.h"
#include "input.h"
#include "screenDifficulty.h"
#include "screenGame.h"
#include "screenInstruments.h"
#include "screenMain.h"
#include "screenPause.h"
#include "screenSongs.h"

void input_menuKeys(SDL_keysym *keysym, SDL_Surface *surface) {
  online = options = false;

  if (keysym->sym == prefs_Input_Keyboard[0].button_pick_down || keysym->sym == prefs_Input_Keyboard[0].button_direction_down) {
    if (fb_screen.mainMenu) input_screenMain(DOWN);
    else if (fb_screen.instruments) input_screenInstruments(DOWN);
    else if (fb_screen.difficulty) input_screenDifficulty(DOWN);
    else if (fb_screen.game && gamePaused) input_screenPause(DOWN);
  }
  
  if (keysym->sym == prefs_Input_Keyboard[0].button_pick_up || keysym->sym == prefs_Input_Keyboard[0].button_direction_up) {
    if (fb_screen.mainMenu) input_screenMain(UP);
    else if (fb_screen.instruments) input_screenInstruments(UP);
    else if (fb_screen.difficulty) input_screenDifficulty(UP);
    else if (fb_screen.game && gamePaused) input_screenPause(UP);
  }
  

  
  if (keysym->sym == prefs_Input_Keyboard[0].button_start || keysym->sym == prefs_Input_Keyboard[0].button_green) {
    if (keysym->mod & KMOD_ALT) /* Switch to full screen only if Alt+Enter is pressed, hard-coded */
      SDL_WM_ToggleFullScreen(surface);
    else {
      if (fb_screen.mainMenu) input_screenMain(RETURN);
      else if (fb_screen.instruments) input_screenInstruments(RETURN);
      else if (fb_screen.songs) input_screenSongs(RETURN);
      else if (fb_screen.difficulty) input_screenDifficulty(RETURN);
      else if (fb_screen.game && gamePaused) input_screenPause(RETURN);
    }
  }
  
  if (keysym->sym == SDLK_ESCAPE) {
    if (fb_screen.game && !gamePaused) input_screenGamePause();
    else if (fb_screen.game && gamePaused) input_screenPause(ESC);
  }
  
  if (keysym->sym == prefs_Input_Keyboard[0].button_red || keysym->sym == SDLK_ESCAPE) { /* Hard-coded Escape for back */
    if (fb_screen.mainMenu) fb_quit(EXIT_SUCCESS);
    else if (fb_screen.instruments) input_screenInstruments(ESC);
    else if (fb_screen.songs) input_screenSongs(ESC);
    else if (fb_screen.difficulty) input_screenDifficulty(ESC);
  }
  
  if (keysym->sym == prefs_Input_Keyboard[0].button_yellow) /* Change sort of song screen */
    if (fb_screen.songs) input_screenSongs(SONG_SORT);
 
  if (prefs_Input_Keyboard[1].enabled && keysym->sym == prefs_Input_Keyboard[1].button_start) {
    if (fb_screen.mainMenu || fb_screen.instruments || fb_screen.songs) {
      if (fb_nPlayers < 4) {
        fb_nPlayers++;
        fprintf(stdout, "Added another player. Number of players: %d.\n", fb_nPlayers);
      }
      else
        fprintf(stderr, "Maximum players is 4.\n");
    }
  }
  
  if (prefs_Input_Keyboard[2].enabled && keysym->sym == prefs_Input_Keyboard[2].button_start) {
    if (fb_screen.mainMenu || fb_screen.instruments || fb_screen.songs) {
      if (fb_nPlayers < 4) {
        fb_nPlayers++;
        fprintf(stdout, "Added another player. Number of players: %d.\n", fb_nPlayers);
      }
      else
        fprintf(stderr, "Maximum players is 4.\n");
    }
  }
  
  if (prefs_Input_Keyboard[3].enabled && keysym->sym == prefs_Input_Keyboard[3].button_start) {
    if (fb_screen.mainMenu || fb_screen.instruments || fb_screen.songs) {
      if (fb_nPlayers < 4) {
        fb_nPlayers++;
        fprintf(stdout, "Added another player. Number of players: %d.\n", fb_nPlayers);
      }
      else
        fprintf(stderr, "Maximum players is 4.\n");
    }
  }

  return;
}
