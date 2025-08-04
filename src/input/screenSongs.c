#include "freeband.h"
#include "graphics/graphics.h"
#include "screens/difficulty.h"
#include "screens/instruments.h"
#include "screens/songs.h"
#include "input.h"
#include "screenSongs.h"

void input_screenSongs(ushort direction) {
  switch(direction) {
    case SONG_SORT:
      if (byTier_s) {
        byTier_s = false;
        /* screenSongs_sort(SORT_AZ_TITLE); */
        titleAZ_s = true;
#ifndef NDEBUG
        fprintf(stdout, "Songs sorted alphabetically by title.\n");
#endif
      }
      else if (titleAZ_s) {
        titleAZ_s = false;
        /* screenSongs_sort(SORT_AZ_ARTIST); */
        artistAZ_s = true;
#ifndef NDEBUG
        fprintf(stdout, "Songs sorted alphabetically by artist.\n");
#endif
      }
      else if (artistAZ_s) {
        artistAZ_s = false;
        /* screenSongs_sort(SORT_BPM); */
        byBPM_s = true;
#ifndef NDEBUG
        fprintf(stdout, "Songs sorted ascendingly by BPM.\n");
#endif
      }
      else {
        byBPM_s = false;
        /* screenSongs_sort(SORT_BY_TIER); */
        byTier_s = true;
#ifndef NDEBUG
        fprintf(stdout, "Songs sorted by Tier.\n");
#endif
      }
      break;
    
    case RETURN:
      menuQuit = graphics_loading = true;
      fb_screen.songs = false;
      graphics_clear();
      screenDifficulty_buffer();
      fb_screen.difficulty = true;
#ifndef NDEBUG
      fprintf(stdout, "Now in screenDifficulty().\n");
#endif
      graphics_loading = menuQuit = false;
      break;
    
    case ESC:
      menuQuit = graphics_loading = true;
      graphics_clear();
      screenInstruments_buffer();
      fb_screen.songs = graphics_loading = menuQuit = false;
      fb_screen.instruments = true;
      break;
      
    default:
      break;
  }
  
}
