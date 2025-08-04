#include "freeband.h"
#include "graphics/graphics.h"
#include "io/prefs.h"
#include "screens/difficulty.h"
#include "screens/game.h"
#include "screens/instruments.h"
#include "screens/main.h"
#include "screens/pause.h"
#include "screens/songs.h"
#include "input.h"
#include "screenPause.h"

#define PREF_DEFAULT_INSTRUMENT prefs_chars[2].iValue

void input_screenPause(ushort direction) {
  switch (direction) {
    case DOWN:
      if (pause_menuState.resume) {
        pause_menuState.resume = false;
        pause_menuState.restart = true;
      }
      else if (pause_menuState.restart) {
        pause_menuState.restart = false;
        pause_menuState.change_difficulty = true;
      }
      else if (pause_menuState.change_difficulty) {
        pause_menuState.change_difficulty = false;
        pause_menuState.change_mic_volume = true;
      }
      else if (pause_menuState.change_mic_volume) {
        pause_menuState.change_mic_volume = false;
        pause_menuState.lefty_mode = true;
      }
      else if (pause_menuState.lefty_mode) {
        pause_menuState.lefty_mode = false;
        pause_menuState.quit = true;
      }
      else {
        pause_menuState.quit = false;
        pause_menuState.resume = true;
      }
      break;
      
    case UP:
      if (pause_menuState.resume) {
        pause_menuState.resume = false;
        pause_menuState.quit = true;
      }
      else if (pause_menuState.quit) {
        pause_menuState.quit = false;
        pause_menuState.lefty_mode = true;
      }
      else if (pause_menuState.lefty_mode) {
        pause_menuState.lefty_mode = false;
        pause_menuState.change_mic_volume = true;
      }
      else if (pause_menuState.change_mic_volume) {
        pause_menuState.change_mic_volume = false;
        pause_menuState.change_difficulty = true;
      }
      else if (pause_menuState.change_difficulty) {
        pause_menuState.change_difficulty = false;
        pause_menuState.restart = true;
      }
      else {
        pause_menuState.restart = false;
        pause_menuState.resume = true;
      }
      break;
      
    case RETURN:
      if (pause_menuState.resume)
        gamePaused = false;
      else if (pause_menuState.restart) {
        pause_menuState.restart = fb_screen.game = false;
        graphics_loading = true;
        graphics_clear();
        screenGame_buffer();
        fb_screen.game = true;
        graphics_loading = gamePaused = false;
#ifndef NDEBUG
        fprintf(stdout, "screenGame() called. Song restarted\n");
#endif
      }
      else if (pause_menuState.change_difficulty) {
        pause_menuState.change_difficulty = false;
        pause_menuState.resume = true;
#ifndef NDEBUG
        fprintf(stdout, "Not implemented yet.\n");
#endif
      }
      else if (pause_menuState.change_mic_volume) {
        pause_menuState.change_mic_volume = false;
        pause_menuState.resume = true;
#ifndef NDEBUG
        fprintf(stdout, "Not implemented yet.\n");
#endif
      }
      else if (pause_menuState.lefty_mode) {
        pause_menuState.lefty_mode = false;
        pause_menuState.resume = true;
#ifndef NDEBUG
        fprintf(stdout, "Not implemented yet.\n");
#endif
      }
      else {
        pause_menuState.quit = false;
        pause_menuState.resume = menuQuit = graphics_loading = true;
        graphics_clear();
        SDL_EnableKeyRepeat(100, SDL_DEFAULT_REPEAT_INTERVAL); /* Re-enable key repeat */
        screenMain_buffer();
        fb_screen.instruments = graphics_loading = menuQuit = false;
        fb_screen.mainMenu = true;
#ifndef NDEBUG
        fprintf(stdout, "Quit stage. Now at screenMain().\n");
#endif
        current_instrument = PREF_DEFAULT_INSTRUMENT;
      }
    
    case ESC:
      gamePaused = false;
      fb_screen.game = true;
      pause_menuState.resume = true; /* Reset default option */
      pause_menuState.restart = false;
      pause_menuState.change_difficulty = pause_menuState.change_mic_volume = false;
      pause_menuState.lefty_mode = pause_menuState.quit = false;
#ifndef NDEBUG
      fprintf(stdout, "Now in screenGame() function.\n");
#endif
      break;
      
    default:
      break;
  }
  
}
