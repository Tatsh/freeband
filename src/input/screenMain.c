#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../screens/instruments.h"
#include "../screens/main.h"
#include "input.h"
#include "screenMain.h"

GLvoid input_screenMain(GLuint direction) {
  GLuint i;
  
  switch (direction) {
    case DOWN:
      screenMain_nSelection++;
      screenMain_highlighted(screenMain_nSelection);

      if ( screenMain_nSelection < 5 )
        for ( i = 0; i < 4; i++ ) screenMain_selectionY[i] = screenMain_selectionY[i] + 0.2;
      else {
        screenMain_nSelection = 0;
        screenMain_highlighted(screenMain_nSelection);
        screenMain_selectionY[0] = 0.18f; screenMain_selectionY[1] = 0.0f;
        screenMain_selectionY[2] = 0.0f ; screenMain_selectionY[3] = 0.18f;
      }
      break;
      
    case UP:
      if (screenMain_nSelection > 0) {
        screenMain_nSelection--;
        screenMain_highlighted(screenMain_nSelection);
        for ( i = 0; i < 4; i++ ) screenMain_selectionY[i] = screenMain_selectionY[i] - 0.2;
      }
      else if (screenMain_nSelection < 1 ) {
        screenMain_nSelection = 4;
        screenMain_highlighted(screenMain_nSelection);
        for ( i = 0; i < 4; i++ ) screenMain_selectionY[i] = screenMain_selectionY[i] + 0.8;
      }
      break;
      
    case RETURN:
      screenMain_accept();
      if (!nonGame) {
        if (!(screenInstruments_buffer())) /* Note: 1 player screen is significantly different from multiplayer */
          fprintf(stderr, "Failed to buffer screenInstruments.\n");
        else
          fprintf(stdout, "Buffering screenInstruments.\n");
      }
      else
        fprintf(stdout, "Not implemented yet.\n");
      break;
      
    /* Escape key is handled in input.c */
    /*case ESC:
      break;*/
      
    default:
      break;
  }
  
  return;
}
