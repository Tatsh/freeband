#include "screenInstruments.h"
#include "freeband.h"
#include "graphics/graphics.h"
#include "input.h"
#include "io/prefs.h"
#include "screens/instruments.h"
#include "screens/main.h"
#include "screens/songs.h"

void input_screenInstruments(ushort direction) {
  switch (direction) {
    case DOWN:
      if (fb_nPlayers < 2) {
        if (current_instrument > INSTRUMENT_DRUMS)
          current_instrument = INSTRUMENT_GUITAR;
        else
          current_instrument++;
      }
      break;

    case UP:
      if (fb_nPlayers < 2) {
        if (current_instrument < INSTRUMENT_BASS)
          current_instrument = INSTRUMENT_VOCALS;
        else
          current_instrument--;
      }
      break;

    case RETURN:
      screenInstruments_accept();
      screenSongs_buffer();
      /* screenCharactersBuffer(nPlayers); someday */
      break;

    case ESC:
      menuQuit = graphics_loading = true;
      graphics_clear();
      screenMain_buffer();
      fb_screen.instruments = graphics_loading = menuQuit = false;
      fb_screen.mainMenu = true;
#ifndef NDEBUG
      fprintf(stdout, "Successfully switched back to screenMain.\n");
#endif
      /*      prefs_Freeband.default_instrument_u = 0;*/
      break;

    default:
      break;
  }
}
