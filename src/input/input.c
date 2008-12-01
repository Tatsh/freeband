#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../screens/game.h"
#include "../screens/instruments.h"
#include "../screens/main.h"
#include "../screens/songs.h"

GLvoid menuKeys(SDL_keysym *keysym, SDL_Surface *surface) {

  Uint8 *keystates = SDL_GetKeyState(NULL);
  GLuint i;
  online = options = false;
  
  switch (keysym->sym) {
    
    case SDLK_DOWN:
      if (currentScreen.mainMenu) {

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

      else if (currentScreen.instruments) {

        if (nPlayers < 2) {
          instSelection++;
          setInstrument(instSelection);

          if ( instSelection < 4 );
          else {
            instSelection = 0;
            setInstrument(instSelection);
          }
        }

      }
      break;
      
    case SDLK_UP:
      if (currentScreen.mainMenu) {
 
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

      else if (currentScreen.instruments) {

        if (nPlayers < 2) {
          if (instSelection > 0) {
            instSelection--;
            setInstrument(instSelection);
          }
          else if (instSelection < 1 ) {
            instSelection = 3; /* Vocals */
            setInstrument(instSelection);
          }

        }

      }
      break;

    case SDLK_RETURN:
      if (keystates[SDLK_LALT] || keystates[SDLK_RALT]) /* Switch to full screen only if Alt+Enter is pressed */
        SDL_WM_ToggleFullScreen(surface);
      else {

        if (currentScreen.mainMenu) {
          handleMainMenu();
          if (!nonGame)
            screenInstrumentsBuffer(nPlayers); /* Note: 1 player screen is significantly different from multiplayer */
          else
            fprintf(stdout, "Not implemented yet.\n");
        }

        else if (currentScreen.instruments) {
          handleInstrumentsMenu();
          screenSongsBuffer();
          /* screenCharactersBuffer(nPlayers); someday */
        }
        else if (currentScreen.songs) {
          menuQuit = loading = true;
          currentScreen.songs = false;
          clearScreen();
          currentScreen.difficulty = true;
#ifdef __DEBUG__
          fprintf(stdout, "Would be at screenDifficulty() currently. Not implemented yet.\n");
#endif
          /* screenDifficulty(); */
          loading = menuQuit = false;
        }
        else if (currentScreen.difficulty) {
          menuQuit = loading = true;
          currentScreen.difficulty = false;
          clearScreen();
#ifdef __DEBUG__
          fprintf(stdout, "Loading screenGame().\n");
#endif
          screenGameBuffer();
          currentScreen.game = true;
          screenGame();
#ifdef __DEBUG__
          fprintf(stdout, "Now in screenGame() function.\n");
#endif
          loading = false;
        }

      }
      break;

    case SDLK_ESCAPE:
      if (currentScreen.mainMenu)
        quitGame(0);
      else if (currentScreen.instruments) {
        menuQuit = loading = true;
        clearScreen();
        setMainImages();
        setMainText();
        currentScreen.instruments = loading = menuQuit = false;
        currentScreen.mainMenu = true;
#ifdef __DEBUG__
        fprintf(stdout, "Successfully switched back to screenMain.\n");
#endif
        instSelection = 0;
        for (i = 0; i < 4; i++) selectedGradientY[i] = selectedGradientY_reset[i]; /* Reset gradient to guitar position */
      }
      else if (currentScreen.songs) {
        menuQuit = loading = true;
        clearScreen();
        setInstrumentsImages_1P();
        setInstrumentsText_1P();
        currentScreen.instruments = loading = menuQuit = false;
        currentScreen.instruments = true;
      }
      break;
      
    case SDLK_q: /* Can anyone say 'easter egg'? Maybe things like this will help themers */
      if (currentScreen.mainMenu) {
        for ( i = 0; i < 4; i++ )
          logoVertexX[i] = logoVertexX[i] - 0.01;
      }
      break;
      
    case SDLK_w:
      if (currentScreen.mainMenu) {
        for ( i = 0; i < 4; i++ )
          logoVertexX[i] = logoVertexX[i] + 0.01;
      }
      break;

    default:
      break;
  }

  return;
}

GLvoid gameKeys(SDL_keysym *keysym, SDL_Surface *surface, GLuint nPlayers) {
  
  Uint8 *keystates = SDL_GetKeyState(NULL);

  if (keystates[SDLK_F1])
    button.g = true;
  else
    button.g = false;
  
  if (keystates[SDLK_F2])
    button.r = true;
  else
    button.r = false;
  
  if (keystates[SDLK_F3])
    button.y = true;
  else
    button.y = false;
  
  if (keystates[SDLK_F4])
    button.b = true;
  else
    button.b = false;
  
  if (keystates[SDLK_F5])
    button.o = true;
  else
    button.o = false;
  
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
