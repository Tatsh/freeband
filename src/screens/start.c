#include "../freeband.h"

#ifdef __GL__

#define SELECTBLENDSRC  0.30f
#define SELECTBLENDDEST 0.60f

/* Background, static till game is themeable */
char *bgTexture = "GameData/themes/default/global/bg.png";
/* Top-left width, bottom-left width, top-right width, bottom-right width */
int bgArrayW[] = { 0, 0, 800, 800 };
/* Top-left height, bottom-left height, top-right height, bottom-right height */
int bgArrayH[] = { 0, 600, 0, 600 };
float bgAlpha[] = { 1.0f, 1.0f, 1.0f, 1.0f };

/* Logo */
char *logoTexture = "GameData/themes/default/screenStart/banner.png";
int logoArrayW[] = { 92, 92, 720, 720 };
int logoArrayH[] = { 92, 327, 92, 327 };
float logoAlpha[] = { 1.0f, 1.0f, 1.0f, 1.0f };

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
    printf("vertexH[%d]: %d\n", i, vertexW[i]);
  }

  int j;
  for (j = 0; j < 4; j++) {
    printf("vertexV[%d]: %d\n", j, vertexH[j]);
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

  /* Flush GL rendering pipeline */
  glFlush ();

  return 0;
}

void reloadStaticMenuItems_GL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* Clear buffers to draw next frame efficiently */
  glColor4f(1.0, 1.0, 1.0, 1.0); /* Transparent colour */
  loadFlatTexture_GL(bgTexture, bgArrayW, bgArrayH, bgAlpha); /* Reload background */
  loadFlatTexture_GL(logoTexture, logoArrayW, logoArrayH, logoAlpha); /* Reload logo */
}

void useSelector_GL(int translateV) {
  /* Selector's default position, horizontal, vertical, and default alpha values */
  char *selectorTexture = "GameData/themes/default/screenStart/selector.png";
  int selectorArrayH[] = { 425, 425, 765, 765 };
  int selectorArrayV[] = { 300, 350, 300, 350 };
  float selectorAlpha[] = { 1.0f, 1.0f, 1.0f, SELECTBLENDSRC };

  int i;
  if (translateV != 0) {
    for (i = 0; i < 4; i++) {
      selectorArrayV[i] = selectorArrayV[i]+translateV;
    }
    loadFlatTexture_GL(selectorTexture, selectorArrayH, selectorArrayV, selectorAlpha);
  }
  else {
    loadFlatTexture_GL(selectorTexture, selectorArrayH, selectorArrayV, selectorAlpha);
  }
}
#endif

struct selection {
  bool singlePlayer;
  bool multiplayer;
  bool online;
  bool options;
  bool quit;
} mainMenu;

int showMainMenu()
{
#ifdef __GL__
  enableMenu_GL();

  /* Initial loading of background and logo */
  loadFlatTexture_GL(bgTexture, bgArrayW, bgArrayH, bgAlpha);
  loadFlatTexture_GL(logoTexture, logoArrayW, logoArrayH, logoAlpha);

  /* Selector function (OpenGL), argument is the value to translate vertically */
  useSelector_GL(0);

/*  showMainMenuOptions_GL(); */
#endif

  SDL_Event startmenu;
  bool running = true;
  bool selecting = false;
  mainMenu.singlePlayer = true;
  int gameMode = 1;

  /* Main loop to keep window running */
  while(running) {
    while(SDL_PollEvent(&startmenu)) {
      switch(startmenu.type){
        /* End loop if user hits ESC or closes the window */
        case SDL_KEYDOWN:
          selecting = true;
          if (startmenu.key.keysym.sym == SDLK_ESCAPE)
            running = false;
          else if (startmenu.key.keysym.sym == SDLK_DOWN) {
            if (mainMenu.singlePlayer == true) {
              mainMenu.singlePlayer = false;
              mainMenu.multiplayer = true; /* Switch to Multiplayer */
#ifdef __GL__
              reloadStaticMenuItems_GL();
              useSelector_GL(55);
#endif
#ifdef __DEBUG__
              printf("Multiplayer selected.\n");
#endif
            }
            else if (mainMenu.multiplayer == true) {
              mainMenu.multiplayer = false;
              mainMenu.online = true; /* Switch to Online */
#ifdef __GL__
              reloadStaticMenuItems_GL();
              useSelector_GL(55 * 2);
#endif
#ifdef __DEBUG__
              printf("Online selected.\n");
#endif
            }
            else if (mainMenu.online == true) {
              mainMenu.online = false;
              mainMenu.options = true; /* Switch to Options */
#ifdef __GL__
              reloadStaticMenuItems_GL();
              useSelector_GL(55 * 3);
#endif
              printf("Options selected.\n");
            }
            else if (mainMenu.options == true) {
              mainMenu.options = false;
              mainMenu.quit = true; /* Switch to Quit */
#ifdef __GL__
              reloadStaticMenuItems_GL();
              useSelector_GL(55 * 4);
#endif
#ifdef __DEBUG__
              printf("Quit selected.\n");
#endif
            }
            /* Cycled through all menu options using just the down arrow */
            else {
              mainMenu.quit = false;
              mainMenu.singlePlayer = true; /* Switch back to Single Player */
#ifdef __GL__
              reloadStaticMenuItems_GL();
              useSelector_GL(0);
#endif
#ifdef __DEBUG__
              printf("Single player selected.\n");
#endif
            }
          }
          else if (startmenu.key.keysym.sym == SDLK_UP) {
            /* Backwards of above code */
            if (mainMenu.singlePlayer == true) {
              mainMenu.singlePlayer = false;
              mainMenu.quit = true; /* Switch to Quit */
#ifdef __GL__
              reloadStaticMenuItems_GL();
              useSelector_GL(55 * 4);
#endif
#ifdef __DEBUG__
              printf("Quit selected.\n");
#endif
            }
            else if (mainMenu.quit == true) {
              mainMenu.quit = false;
              mainMenu.options = true; /* Switch to Options */
#ifdef __GL__
              reloadStaticMenuItems_GL();
              useSelector_GL(55 * 3);
#endif
#ifdef __DEBUG__
              printf("Options selected.\n");
#endif
            }
            else if (mainMenu.options == true) {
              mainMenu.options = false;
              mainMenu.online = true; /* Switch to Online */
#ifdef __GL__
              reloadStaticMenuItems_GL();
              useSelector_GL(55 * 2);
#endif
#ifdef __DEBUG__
              printf("Online selected.\n");
#endif
            }
            else if (mainMenu.online == true) {
              mainMenu.online = false;
              mainMenu.multiplayer = true; /* Switch to Multiplayer */
#ifdef __GL__
              reloadStaticMenuItems_GL();
              useSelector_GL(55);
#endif
#ifdef __DEBUG__
              printf("Multiplayer selected.\n");
#endif
            }
            /* Cycled through all menu options using just the up arrow */
            else {
              mainMenu.multiplayer = false;
              mainMenu.singlePlayer = true; /* Switch to Single Player */
#ifdef __GL__
              reloadStaticMenuItems_GL();
              useSelector_GL(0);
#endif
#ifdef __DEBUG__
              printf("Single player selected.\n");
#endif
            }
          }
          /* User selects mode to play */
          else if (startmenu.key.keysym.sym == SDLK_RETURN) {
              if (mainMenu.singlePlayer == true) {
                gameMode = 1;
                running = false;
              }
              else if (mainMenu.multiplayer == true) {
                gameMode = 2;
              }
              else if (mainMenu.online == true) {
                gameMode = 3;
              }
              else if (mainMenu.options == true) {
                gameMode = 4;
              }
              else { /* Assume selection is Quit */
                printf("Quitting...\n");
                gameMode = -1;
                running = false;
              }
          }
          break;
        case SDL_QUIT:
          running = false;
          break;
      }   /* matches switch(startmenu.type) */
    }     /* matches while(SDL_PollEvent(&startmenu)) */
  }       /* while(running) */
  return gameMode;
}         /* matches function */
