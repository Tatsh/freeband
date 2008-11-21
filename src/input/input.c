#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../screens/instruments.h"
#include "../screens/main.h"

GLvoid menuKeys(SDL_keysym *keysym, SDL_Surface *surface) {

  Uint8 *keystates = SDL_GetKeyState(NULL);
  GLuint i;
  nonGame = true;
  online = options = false;
  
  switch (keysym->sym) {
    
    case SDLK_DOWN:
      if (currentScreen.mainMenu != false) {

        menuSelection++;
        setMainMenuState(menuSelection);

        if ( menuSelection < 5 )
          for ( i = 0; i < 4; i++ ) mSelectorVertexY[i] = mSelectorVertexY[i] + 0.2;
        else {
          menuSelection = 0;
          setMainMenuState(menuSelection);
          mSelectorVertexY[0] = 0.18f;
          mSelectorVertexY[1] = 0.0f;
          mSelectorVertexY[2] = 0.0f;
          mSelectorVertexY[3] = 0.18f;
        }

      }

      else if (currentScreen.instruments != false) {

        if (nPlayers < 2) {
          instSelection++;
          setInstrumentsMenuState_1P(instSelection);

          if ( instSelection < 4 )
            for ( i = 0; i < 4; i++ ) selectedGradientY[i] = selectedGradientY[i] + 0.23;
          else {
            instSelection = 0;
            setInstrumentsMenuState_1P(instSelection);
            for ( i = 0; i < 4; i++ ) selectedGradientY[i] = selectedGradientY_reset[i];
          }
        }

      }
      break;
      
    case SDLK_UP:
      if (currentScreen.mainMenu != false) {
 
        if (menuSelection > 0) {
          menuSelection--;
          setMainMenuState(menuSelection);
          for ( i = 0; i < 4; i++ ) mSelectorVertexY[i] = mSelectorVertexY[i] - 0.2;
        }
        else if (menuSelection < 1 ) {
          menuSelection = 4;
          setMainMenuState(menuSelection);
          for ( i = 0; i < 4; i++ ) mSelectorVertexY[i] = mSelectorVertexY[i] + 0.8;
        }

      }

      else if (currentScreen.instruments != false) {

        if (nPlayers < 2) {
          if (instSelection > 0) {
            instSelection--;
            setInstrumentsMenuState_1P(instSelection);
            for ( i = 0; i < 4; i++ ) selectedGradientY[i] = selectedGradientY[i] - 0.23;
          }
          else if (instSelection < 1 ) {
            instSelection = 3; /* Vocals */
            setInstrumentsMenuState_1P(instSelection);
            for ( i = 0; i < 4; i++ ) selectedGradientY[i] = selectedGradientY[i] + 0.69;
          }

        }

      }
      break;

    case SDLK_RETURN:
      if (keystates[SDLK_LALT] || keystates[SDLK_RALT]) /* Switch to full screen only if Alt+Enter is pressed */
        SDL_WM_ToggleFullScreen(surface);
      else {
        if (currentScreen.mainMenu != false) {
          handleMainMenu();

          if (nonGame != true)
            screenInstrumentsBuffer(nPlayers); /* Note: 1 player screen is significantly different from multiplayer */
          else
            fprintf(stdout, "Not implemented yet.\n");
        }

        else if (currentScreen.instruments != false) {

          handleInstrumentsMenu();
          
          if (instrument.guitar != false) {
            /* screenCharactersBuffer(nPlayers); someday */
            /* screenSongsBuffer(); */
#ifdef __DEBUG__
            fprintf(stdout, "Starting %d player guitar game.\n", nPlayers);
#endif
          }
          else
            fprintf(stdout, "Not implemented yet.\n");
        }

      }
      break;

    case SDLK_ESCAPE:
      if (currentScreen.mainMenu != false)
        quitGame(0);
      else if (currentScreen.instruments != false) {
        menuQuit = loading = true;
        clearScreen();
        setMainImages();
        setMainText();
        currentScreen.instruments = loading = menuQuit = false;
        currentScreen.mainMenu = true;
#ifdef __DEBUG__
        fprintf(stdout, "Successfully switched back to screenMain.\n");
#endif
      }
      break;
      
    case SDLK_q: /* Can anyone say 'easter egg'? Maybe things like this will help themers */
      if (currentScreen.mainMenu != false) {
        for ( i = 0; i < 4; i++ )
          logoVertexX[i] = logoVertexX[i] - 0.01;
      }
      break;
      
    case SDLK_w:
      if (currentScreen.mainMenu != false) {
        for ( i = 0; i < 4; i++ )
          logoVertexX[i] = logoVertexX[i] + 0.01;
      }
      break;

    default:
      break;
  }

  return;
}

GLvoid gameKeys(SDL_keysym *keysym, SDL_Surface *surface, bool note, GLuint nPlayers) {
  
  Uint8 *keystates = SDL_GetKeyState(NULL);
  
  switch (keysym->sym) {

    case SDLK_RETURN:
      if (keystates[SDLK_LALT] || keystates[SDLK_RALT]) /* Switch to full screen only if Alt+Enter is pressed */
        SDL_WM_ToggleFullScreen(surface);
      break;

    default:
      break;

  }
  
  return;
}
