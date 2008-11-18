#include "../freeband.h"

void menuKeys(SDL_keysym *keysym, SDL_Surface *surface) {

  Uint8 *keystates = SDL_GetKeyState(NULL);
  
  switch (keysym->sym) {

    case SDLK_ESCAPE:
#ifdef __DEBUG__
      fprintf(stdout, "Quitting...\n");
#endif
      quitGame(0);
      break;

    case SDLK_RETURN:
      if (keystates[SDLK_LALT] || keystates[SDLK_RALT]) /* Switch to full screen only if Alt+Enter is pressed */
        SDL_WM_ToggleFullScreen(surface);
      break;

    default:
      break;

  }

  return;

}

void gameKeys(SDL_keysym *keysym, SDL_Surface *surface, bool note, int nPlayers) {
  
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

int getNumPlayers() {
  return 0;
}
