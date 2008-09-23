#include "../freeband.h"

#define SELECTBLENDSRC  0.30f
#define SELECTBLENDDEST 0.60f

#ifdef __GL__
int getNumColors(SDL_Surface *surface) {
  int nOfColors;
  nOfColors = surface->format->BytesPerPixel;
  return nOfColors;
}

int loadFlatTexture_GL(char *image, int *vertexW, int *vertexH, float *alphaValues) {
  GLuint texture;         /* Handle to texture object */
  SDL_Surface *surface;   /* Surface from SDL to reveal details of image */
  GLenum texture_format;
  GLint nOfColors;        /* This value is the number of channels in the SDL surface, will reveal if alpha channel exists or not (4) */

  if ((surface = IMG_Load_RW(SDL_RWFromFile(image, "rb"), 1))) {

    /* Check that a texture's width is a power of two, eventually convert on-the-fly */
    if ((surface->w & (surface->w - 1)) != 0) { /* We cannot use boolean values here */
      printf("Warning: %s's width is not a power of 2.\n", image);
    }

    /* Also check that heigh is a power of 2 */
    if ((surface->h & (surface->h - 1)) != 0) {
      printf("Warning: %s's height is not a power of 2.\n", image);
    }

    /* Set special modes based upon alpha channel existence. */
    nOfColors = getNumColors(surface);
    if (nOfColors == 4) {
      /* Does contain an alpha channel */
      if (surface->format->Rmask == 0x000000ff)
        texture_format = GL_RGBA;
      else
        texture_format = GL_BGRA;
    }
    else if (nOfColors == 3) {
      /* Does not contain an alpha channel */
      if (surface->format->Rmask == 0x000000ff)
        texture_format = GL_RGB;
      else
        texture_format = GL_BGR;
    }
    else {
      printf("Warning: %s is not true colour. This may cause a problem.\n", image);
      return 1;
    }

    glGenTextures(1, &texture);

    /* Bind the texture object */
    glBindTexture(GL_TEXTURE_2D, texture);

    /* Set the texture's stretching properties */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Edit the texture object's image data using the information SDL_Surface gives us */
    glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);
  }
  else {
    printf("SDL could not load %s.\n%s\n", image, SDL_GetError());
    SDL_Quit();
    return 1;
  }
 
  /*Free the SDL_Surface only if it was successfully created */
  if (surface)
  {
    SDL_FreeSurface(surface);
  }

  /* Bind the texture to which subsequent calls refer to */
  glBindTexture(GL_TEXTURE_2D, texture);

#ifdef __DEBUG__
  int i;
  printf("%s properties:\n", image);
  for (i = 0; i < 4; i++) {
    printf("vertexW[%d]: %d\n", i, vertexW[i]);
  }

  int j;
  for (j = 0; j < 4; j++) {
    printf("vertexH[%d]: %d\n", j, vertexH[j]);
  }
#endif
  
  if (alphaValues[3] != 1.0f)
    glColor4f(alphaValues[0], alphaValues[1], alphaValues[2], alphaValues[3]);
  
  glBegin(GL_QUADS);
    /* glTexCoord2i order CANNOT be changed unless you want to deal with the consequences */
    glTexCoord2i(0, 0); glVertex2i(vertexW[0], vertexH[0]); /* Top-left vertex (top-left position away from top-left part of screen) */
    glTexCoord2i(1, 0); glVertex2i(vertexW[2], vertexH[2]); /* Top-right vertex */
    glTexCoord2i(1, 1); glVertex2i(vertexW[3], vertexH[3]); /* Bottom-right vertex */
    glTexCoord2i(0, 1); glVertex2i(vertexW[1], vertexH[1]); /* Bottom-left vertex */
  glEnd();

  SDL_GL_SwapBuffers();

  glDeleteTextures(1, &texture);

  return 0;
}
#endif

/* Use bool to save memory :) */

struct selection {
  bool singlePlayer;
  bool multiplayer;
  bool online;
  bool options;
  bool quit;
} mainMenu;

void showMainMenu()
{
#ifdef __GL__
  enableMenuGL();
  
  /* Background */
  char *bgTexture = "themes/default/global/bg.png";
  /* Top-left width, bottom-left width, top-right width, bottom-right width */
  int bgArrayW[] = { 0, 0, 800, 800 };
  /* Top-left height, bottom-left height, top-right height, bottom-right height */
  int bgArrayH[] = { 0, 600, 0, 600 };
  float bgAlpha[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  loadFlatTexture_GL(bgTexture, bgArrayW, bgArrayH, bgAlpha);

  /* Logo */
  char *logoTexture = "themes/default/screenStart/banner.png";
  int logoArrayW[] = { 92, 92, 720, 720 };
  int logoArrayH[] = { 92, 327, 92, 327 };
  float logoAlpha[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  loadFlatTexture_GL(logoTexture, logoArrayW, logoArrayH, logoAlpha);
  
  /* Selector default position */
  char *selectorTexture = "themes/default/screenStart/selector.png";
  int selectorArrayW[] = { 425, 425, 765, 765 };
  int selectorArrayH[] = { 300, 350, 300, 350 };
  float selectorAlpha[] = { 1.0f , 1.0f , 1.0f , SELECTBLENDSRC };
  loadFlatTexture_GL(selectorTexture, selectorArrayW, selectorArrayH, selectorAlpha);
  
  /* Other positions for selector */
  int mpSelectorArrayH[] =      { 355, 405, 355, 405 }; /* Multiplayer */
  int olSelectorArrayH[] =      { 410, 460, 410, 460 }; /* Online */
  int optionsSelectorArrayH[] = { 465, 515, 465, 515 }; /* Options */
  int quitSelectorArrayH[] =    { 520, 570, 520, 570 }; /* Quit */
/*  showMainMenuOptions_GL(); */
#endif

  SDL_Event startmenu;
  bool running = true;
  mainMenu.singlePlayer = true;

  /* Main loop to keep window running */
  while(running) {
    while(SDL_PollEvent(&startmenu)) {
      switch(startmenu.type){
        /* End loop if user hits ESC or closes the window */
        case SDL_KEYDOWN:
          if (startmenu.key.keysym.sym == SDLK_ESCAPE)
            running = false;
          else if (startmenu.key.keysym.sym == SDLK_DOWN) {
            if (mainMenu.singlePlayer == true) {
              mainMenu.singlePlayer = false;
              mainMenu.multiplayer = true;
              loadFlatTexture_GL(selectorTexture, selectorArrayW, mpSelectorArrayH, selectorAlpha);
#ifdef __DEBUG__
              printf("Multiplayer selected.\n");
#endif
            }
            else if (mainMenu.multiplayer == true) {
              mainMenu.multiplayer = false;
              mainMenu.online = true;
              loadFlatTexture_GL(selectorTexture, selectorArrayW, olSelectorArrayH, selectorAlpha);
#ifdef __DEBUG__
              printf("Online selected.\n");
#endif
            }
            else if (mainMenu.online == true) {
              mainMenu.online = false;
              mainMenu.options = true;

              loadFlatTexture_GL(selectorTexture, selectorArrayW, optionsSelectorArrayH, selectorAlpha);
              printf("Options selected.\n");
            }
            else if (mainMenu.options == true) {
              mainMenu.options = false;
              mainMenu.quit = true;
              loadFlatTexture_GL(selectorTexture, selectorArrayW, quitSelectorArrayH, selectorAlpha);
#ifdef __DEBUG__
              printf("Quit selected.\n");
#endif
            }
            /* Cycled through all menu options using just the down arrow */
            else {
              mainMenu.quit = false;
              mainMenu.singlePlayer = true;
#ifdef __DEBUG__
              printf("Single player selected.\n");
#endif
            }
          }
          else if (startmenu.key.keysym.sym == SDLK_UP) {
            /* Backwards of above code */
            if (mainMenu.singlePlayer == true) {
              mainMenu.singlePlayer = false;
              mainMenu.quit = true;
#ifdef __DEBUG__
              printf("Quit selected.\n");
#endif
            }
            else if (mainMenu.quit == true) {
              mainMenu.quit = false;
              mainMenu.options = true;
#ifdef __DEBUG__
              printf("Options selected.\n");
#endif
            }
            else if (mainMenu.options == true) {
              mainMenu.options = false;
              mainMenu.online = true;
#ifdef __DEBUG__
              printf("Online selected.\n");
#endif
            }
            else if (mainMenu.online == true) {
              mainMenu.online = false;
              mainMenu.multiplayer = true;
#ifdef __DEBUG__
              printf("Multiplayer selected.\n");
#endif
            }
            /* Cycled through all menu options using just the up arrow */
            else {
              mainMenu.multiplayer = false;
              mainMenu.singlePlayer = true;
#ifdef __DEBUG__
              printf("Single player selected.\n");
#endif
            }
          }
          /* User selects mode to play */
          else if (startmenu.key.keysym.sym == SDLK_RETURN) {
              if (mainMenu.singlePlayer == true) {
#ifdef __DEBUG__
                printf("Starting single player mode.\n");
#endif
                /* startGame(1); */
              }
              else if (mainMenu.multiplayer == true) {
#ifdef __DEBUG__
                printf("Starting multiplayer mode.\n");
#endif
                /* int numPlayers;
                  Check if enumControllers found any, otherwise set value to 2
                if (enumControllers() == -1)
                  numPlayers = 2;
                else
                  numPlayers = enumControllers();
                startGame(numPlayers); */
              }
              else if (mainMenu.online == true)
#ifdef __DEBUG__
                printf("Starting online mode.\n");
#endif
              /* int numPlayers;
                 Check if enumControllers found any, otherwise set value to 1
                if (enumControllers() == -1)
                  numPlayers = 1;
                else
                  numPlayers = enumControllers();
                startGame(numPlayers); */
              else if (mainMenu.options == true)
#ifdef __DEBUG__
                printf("Going to options menu.\n");
#endif
/*
#ifdef __GL__
                showOptionsMenu_GL();
#else
                showOptionsMenu();
#endif */
              else /* Assume selection is Quit */ {
                printf("Quitting...\n");
                running = false;
              }
          }
          break;
        case SDL_QUIT:
          running = false;
          break;
      }
    }
  }
}
