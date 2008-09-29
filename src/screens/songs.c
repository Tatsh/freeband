#include "../freeband.h"

#ifdef __GL__
bool showSongsMenu_GL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* Clear buffers to draw next frame efficiently */
#ifdef __DEBUG__
  printf("Whoa we really have got this far!\n");
#endif

  SDL_Event songMenu;
  bool running = true;
  bool selecting = false;

  while (running) {
    while(SDL_PollEvent(&songMenu)) {
      switch(songMenu.type) {

        case SDL_KEYDOWN:
          selecting = true;

          if (songMenu.key.keysym.sym == SDLK_ESCAPE) {
            running = false;
            return running;
          }

          break;

        case SDL_QUIT:
          running = false;
          reloadStaticMenuItems();
          showMainMenu();
          break;

      }
    }
  }
  
  return true;
}
#endif
