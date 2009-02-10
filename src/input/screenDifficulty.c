#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../screens/difficulty.h"
#include "../screens/game.h"
#include "../screens/songs.h"
#include "input.h"
#include "screenDifficulty.h"

GLvoid input_screenDifficulty(GLuint direction) {
  GLushort i;
  
  switch (direction) {
    case DOWN:
      if (diffEasy) {
        diffMedium = true;
        diffEasy = false;
        for ( i = 0; i < 4; i++ ) screenDifficulty_selectionY[i] = screenDifficulty_selectionY[i] + DIFFHT;
      }
      else if (diffMedium) {
        diffHard = true;
        diffMedium = false;
        for ( i = 0; i < 4; i++ ) screenDifficulty_selectionY[i] = screenDifficulty_selectionY[i] + DIFFHT;
      }
      else if (diffHard) {
        diffExpert = true;
        diffHard = false;
        for ( i = 0; i < 4; i++ ) screenDifficulty_selectionY[i] = screenDifficulty_selectionY[i] + DIFFHT;
      }
      else if (diffExpert) {
        diffEasy = true;
        diffExpert = false;
        screenDifficulty_selectionY[0] = 0.0f; screenDifficulty_selectionY[1] = DIFFHT;
        screenDifficulty_selectionY[2] = DIFFHT; screenDifficulty_selectionY[3] = 0.0f;
      }
      break;
      
    case UP:
      if (diffEasy) {
        diffExpert = true;
        diffEasy = false;
        for ( i = 0; i < 4; i++ ) screenDifficulty_selectionY[i] = screenDifficulty_selectionY[i] + (3.0f * DIFFHT);
      }
      else if (diffExpert) {
        diffHard = true;
        diffExpert = false;
        for ( i = 0; i < 4; i++ ) screenDifficulty_selectionY[i] = screenDifficulty_selectionY[i] - DIFFHT;
      }
      else if (diffHard) {
        diffMedium = true;
        diffHard = false;
        for ( i = 0; i < 4; i++ ) screenDifficulty_selectionY[i] = screenDifficulty_selectionY[i] - DIFFHT;
      }
      else if (diffMedium) {
        diffEasy = true;
        diffMedium = false;
        for ( i = 0; i < 4; i++ ) screenDifficulty_selectionY[i] = screenDifficulty_selectionY[i] - DIFFHT;
      }
      break;
      
    case RETURN:
      menuQuit = graphics_loading = true;
      fb_screen.difficulty = false;
      graphics_clear();
      screenGame_buffer();
      fb_screen.game = true;
      graphics_loading = gamePaused = false;
#ifdef __DEBUG__
      fprintf(stdout, "Now in screenGame() function.\n");
#endif
      break;
      
    case ESC:
      menuQuit = graphics_loading = true;
      graphics_clear();
      screenSongs_buffer();
      fb_screen.difficulty = graphics_loading = menuQuit = false;
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
