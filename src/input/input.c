#include "input.h"
#include "audio/audio.h"
#include "freeband.h"
#include "graphics/graphics.h"
#include "io/joypad.h"
#include "io/keys.h"
#include "screenDifficulty.h"
#include "screenGame.h"
#include "screenInstruments.h"
#include "screenMain.h"
#include "screenPause.h"
#include "screenSongs.h"
#include "screens/difficulty.h"
#include "screens/game.h"
#include "screens/instruments.h"
#include "screens/main.h"
#include "screens/pause.h"
#include "screens/songs.h"

/* Preferences */
#define FBKEY_OPERATOR keyPrefs[0].user_value
#define KBENABLED keyPrefs[1].user_value
#define DISABLEPICK keyPrefs[2].user_value
#define FBKEY_GREEN keyPrefs[3].user_value
#define FBKEY_RED keyPrefs[4].user_value
#define FBKEY_YELLOW keyPrefs[5].user_value
#define FBKEY_BLUE keyPrefs[6].user_value
#define FBKEY_ORANGE keyPrefs[7].user_value
#define FBKEY_PICKUP keyPrefs[8].user_value
#define FBKEY_PICKDOWN keyPrefs[9].user_value
#define FBKEY_START keyPrefs[10].user_value
#define FBKEY_BACK keyPrefs[11].user_value
#define FBKEY_LEFT keyPrefs[12].user_value
#define FBKEY_RIGHT keyPrefs[13].user_value
#define FBKEY_UP keyPrefs[14].user_value
#define FBKEY_DOWN keyPrefs[15].user_value
#define FBKEY_WHAMMYDOWN keyPrefs[16].user_value
#define FBKEY_WHAMMYUP keyPrefs[17].user_value
#define FBKEY_STARPOWER keyPrefs[18].user_value
#define FBKEY_SCREENSHOT keyPrefs[19].user_value

void input_menuKeys(SDL_keysym *keysym, SDL_Surface *surface) {
  online = options = false;

  if (keysym->sym == FBKEY_PICKDOWN || keysym->sym == FBKEY_DOWN) {
    if (fb_screen.mainMenu)
      input_screenMain(DOWN);
    else if (fb_screen.instruments)
      input_screenInstruments(DOWN);
    else if (fb_screen.difficulty)
      input_screenDifficulty(DOWN);
    else if (fb_screen.game && gamePaused)
      input_screenPause(DOWN);
  }

  if (keysym->sym == FBKEY_PICKUP || keysym->sym == FBKEY_UP) {
    if (fb_screen.mainMenu)
      input_screenMain(UP);
    else if (fb_screen.instruments)
      input_screenInstruments(UP);
    else if (fb_screen.difficulty)
      input_screenDifficulty(UP);
    else if (fb_screen.game && gamePaused)
      input_screenPause(UP);
  }

  if (keysym->sym == FBKEY_GREEN || keysym->sym == FBKEY_START) {
    if (keysym->mod & KMOD_ALT) /* Switch to full screen only if Alt+Enter is pressed, hard-coded */
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
      else if (fb_screen.game && gamePaused)
        input_screenPause(RETURN);
    }
  }

  if (keysym->sym == SDLK_ESCAPE) {
    if (fb_screen.game && !gamePaused)
      input_screenGamePause();
    else if (fb_screen.game && gamePaused)
      input_screenPause(ESC);
  }

  if (keysym->sym == FBKEY_RED || keysym->sym == SDLK_ESCAPE) { /* Hard-coded Escape for back */
    if (fb_screen.mainMenu)
      fb_quit(EXIT_SUCCESS);
    else if (fb_screen.instruments)
      input_screenInstruments(ESC);
    else if (fb_screen.songs)
      input_screenSongs(ESC);
    else if (fb_screen.difficulty)
      input_screenDifficulty(ESC);
  }

  if (keysym->sym == FBKEY_YELLOW) /* Change sort of song screen */
    if (fb_screen.songs)
      input_screenSongs(SONG_SORT);

  /*  if (prefs_Input_Keyboard[1].enabled && keysym->sym == prefs_Input_Keyboard[1].button_start) {
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
  }*/
}
