#include "../freeband.h"
#include "../audio/audio.h"
#include "../graphics/graphics.h"
#include "../screens/difficulty.h"
#include "../screens/game.h"
#include "../screens/instruments.h"
#include "../screens/main.h"
#include "../screens/songs.h"

GLvoid input_menuKeys(SDL_keysym *keysym, SDL_Surface *surface) {

  Uint8 *keystates = SDL_GetKeyState(NULL);
  GLuint i;
  online = options = false;
  
  switch (keysym->sym) {
    
    case SDLK_DOWN:
      if (fb_screen.mainMenu) {

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

      }

      else if (fb_screen.instruments) {

        if (fb_nPlayers < 2) {
          screenInstruments_nSelection++;
          screenInstruments_highlighted(screenInstruments_nSelection);

          if ( screenInstruments_nSelection < 4 );
          else {
            screenInstruments_nSelection = 0;
            screenInstruments_highlighted(screenInstruments_nSelection);
          }
        }

      }
      else if (fb_screen.difficulty) {
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
      }
      break;
      
    case SDLK_UP:
      if (fb_screen.mainMenu) {
 
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

      }

      else if (fb_screen.instruments) {

        if (fb_nPlayers < 2) {
          if (screenInstruments_nSelection > 0) {
            screenInstruments_nSelection--;
            screenInstruments_highlighted(screenInstruments_nSelection);
          }
          else if (screenInstruments_nSelection < 1 ) {
            screenInstruments_nSelection = 3; /* Vocals */
            screenInstruments_highlighted(screenInstruments_nSelection);
          }

        }

      }
      
      else if (fb_screen.difficulty) {
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
      }
      break;

    case SDLK_RETURN:
      if (keystates[SDLK_LALT] || keystates[SDLK_RALT]) /* Switch to full screen only if Alt+Enter is pressed */
        SDL_WM_ToggleFullScreen(surface);
      else {

        if (fb_screen.mainMenu) {
          screenMain_accept();
          if (!nonGame) {
            if (!(screenInstruments_buffer())) /* Note: 1 player screen is significantly different from multiplayer */
              fprintf(stderr, "Failed to buffer screenInstruments.\n");
            else
              fprintf(stdout, "Buffering screenInstruments.\n");
          }
          else
            fprintf(stdout, "Not implemented yet.\n");
        }

        else if (fb_screen.instruments) {
          screenInstruments_accept();
          screenSongs_buffer();
          /* screenCharactersBuffer(nPlayers); someday */
        }
        else if (fb_screen.songs) {
          menuQuit = graphics_loading = true;
          fb_screen.songs = false;
          graphics_clear();
          screenDifficulty_buffer();
          fb_screen.difficulty = true;
#ifdef __DEBUG__
          fprintf(stdout, "Now in screenDifficulty().\n");
#endif
          graphics_loading = menuQuit = false;
        }
        else if (fb_screen.difficulty) {
          menuQuit = graphics_loading = true;
          fb_screen.difficulty = false;
          graphics_clear();
          screenGame_buffer();
          fb_screen.game = true;
          graphics_loading = gamePaused = false;
#ifdef __DEBUG__
          fprintf(stdout, "Now in screenGame() function.\n");
#endif
        }

      }
      break;

    case SDLK_ESCAPE:
      if (fb_screen.mainMenu)
        fb_quit(0);
      else if (fb_screen.instruments) {
        menuQuit = graphics_loading = true;
        graphics_clear();
        screenMain_buffer();
        fb_screen.instruments = graphics_loading = menuQuit = false;
        fb_screen.mainMenu = true;
#ifdef __DEBUG__
        fprintf(stdout, "Successfully switched back to screenMain.\n");
#endif
        screenInstruments_nSelection = 0;
        for (i = 0; i < 4; i++) screenInstruments_selectionY[i] = screenInstruments_selectionReset[i]; /* Reset gradient to guitar position */
      }
      else if (fb_screen.songs) {
        menuQuit = graphics_loading = true;
        graphics_clear();
        screenInstruments_buffer();
        fb_screen.instruments = graphics_loading = menuQuit = false;
        fb_screen.instruments = true;
      }
      else if (fb_screen.difficulty) {
        menuQuit = graphics_loading = true;
        graphics_clear();
        screenSongs_buffer();
        fb_screen.difficulty = graphics_loading = menuQuit = false;
        fb_screen.songs = true;
#ifdef __DEBUG__
        fprintf(stdout, "Switched back to screenSongs.\n");
#endif
      }
      break;
      
    case SDLK_KP_ENTER:
      if (fb_screen.mainMenu || fb_screen.instruments || fb_screen.songs) {
        if (fb_nPlayers < 4)
          fb_nPlayers++;
#ifdef __DEBUG__
        fprintf(stdout, "Added another player. Number of players: %d.\n", fb_nPlayers);
#endif
      }
      break;
      
    case SDLK_q: /* Can anyone say 'easter egg'? Maybe things like this will help themers */
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
