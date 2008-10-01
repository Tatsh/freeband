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

int loadTexture_GL(char *image, int *vertexW, int *vertexH, float *alphaValues) {
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
 
  /* Free the SDL_Surface only if it was successfully created */
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

  /* Draw it to the screen */
  SDL_GL_SwapBuffers();

#ifdef __DEBUG__
  /* Get frames per second */
  GLint frames = 0;
  GLint t_0 = 0;
  frames++;
  {
    GLint t = SDL_GetTicks();
    if (t - t_0 >= 1000) {
      GLfloat seconds = (t - t_0) / 1000.0;
      GLfloat fps = frames / seconds;
      printf("%d frames in %g seconds = %g FPS\n", frames, seconds, fps);
      t_0 = t;
      frames = 0;
    }
  }
#endif

  glDeleteTextures(1, &texture);

  /* Flush GL rendering pipeline */
  glFlush ();

  return 0;
}

void reloadStaticMenuItems_GL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* Clear buffers to draw next frame efficiently */
  glColor4f(1.0, 1.0, 1.0, 1.0); /* Transparent colour */
  loadTexture_GL(bgTexture, bgArrayW, bgArrayH, bgAlpha); /* Reload background */
  loadTexture_GL(logoTexture, logoArrayW, logoArrayH, logoAlpha); /* Reload logo */
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
    loadTexture_GL(selectorTexture, selectorArrayH, selectorArrayV, selectorAlpha);
  }
  else {
    loadTexture_GL(selectorTexture, selectorArrayH, selectorArrayV, selectorAlpha);
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

int mainMenuUpDown(SDL_keysym *keysym) {

  int gameMode = 1; /* Single player is selected  by default */

  switch (keysym->sym) {

    case SDLK_ESCAPE:
      gameMode = -1;
      break;

    case SDLK_DOWN:
      if (mainMenu.singlePlayer == true) {
        mainMenu.singlePlayer = false;
        mainMenu.multiplayer = true; /* Switch to Multiplayer */
        gameMode = 2;
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
        gameMode = 3;
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
        gameMode = 4;
#ifdef __GL__
        reloadStaticMenuItems_GL();
        useSelector_GL(55 * 3);
#endif
        printf("Options selected.\n");
      }
      else if (mainMenu.options == true) {
        mainMenu.options = false;
        mainMenu.quit = true; /* Switch to Quit */
        gameMode = -1;
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
        gameMode = 1;
#ifdef __GL__
        reloadStaticMenuItems_GL();
        useSelector_GL(0);
#endif
#ifdef __DEBUG__
        printf("Single player selected.\n");
#endif
      }
      break;

    case SDLK_UP:
      /* Backwards of above code */
      if (mainMenu.singlePlayer == true) {
        mainMenu.singlePlayer = false;
        mainMenu.quit = true; /* Switch to Quit */
        gameMode = -1;
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
        gameMode = 4;
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
        gameMode = 3;
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
        gameMode = 2;
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
        gameMode = 1;
#ifdef __GL__
        reloadStaticMenuItems_GL();
        useSelector_GL(0);
#endif
#ifdef __DEBUG__
        printf("Single player selected.\n");
#endif
      }
      break;

    /* User selects mode to play, gameMode determined by above code */
/*    case SDLK_RETURN:
      selecting = false;
      return gameMode; */

    default:
      break;
  }

  return gameMode;
}

void showMainMenu()
{
#ifdef __GL__
  /* Initial loading of background and logo */
  loadTexture_GL(bgTexture, bgArrayW, bgArrayH, bgAlpha);
  loadTexture_GL(logoTexture, logoArrayW, logoArrayH, logoAlpha);

  /* Selector function (OpenGL), argument is the value to translate vertically */
  useSelector_GL(0); /* Initial position */
#endif
  
  SDL_Event freebandMenu;
  bool hasQuit = false;
  bool windowActive = true;
  int menuSelection = 1;

  while(!hasQuit) {

    while(SDL_PollEvent(&freebandMenu)) {

      switch(freebandMenu.type) {

        case SDL_QUIT: /* Handle quit requests */
          hasQuit = true;
#ifdef __DEBUG__
          printf("Quitting...\n");
#endif
          break;

        case SDL_ACTIVEEVENT: /* Check if window is active. If not, stop rendering */
          if (freebandMenu.active.gain == 0) {
            windowActive = false;
#ifdef __DEBUG__
          printf("Rendering paused.\n");
#endif
          }
          else
            windowActive = true;
          break;

        case SDL_KEYDOWN:
          menuSelection = mainMenuUpDown(&freebandMenu.key.keysym); /* Handle key presses */
          if (menuSelection == 1) {
            startGame(1);
#ifdef __DEBUG__
            printf("Starting single player game.\n");
#endif
          }
          else if (menuSelection == 2) {
            startGame(2);
#ifdef __DEBUG__
            printf("Starting multiplayer game.\n");
#endif
          }
          else if (menuSelection == 3) {
#ifdef __GL__
            goOnline_GL();
#endif
#ifdef __DEBUG__
            printf("Loading online menu.\n");
#endif
          }
          else if (menuSelection == 4) {
#ifdef __GL__
            showOptionsMenu_GL();
#endif
#ifdef __DEBUG__
            printf("Loadings options screen.\n");
#endif
          }
          else {
#ifdef __DEBUG__
            printf("Quitting...\n");
#endif
          }
          break;

        default:
          /* Keep loading graphics */
          reloadStaticMenuItems_GL();
          if (menuSelection == 1) {
#ifdef __GL__
            useSelector_GL(menuSelection);
#endif
          }
          else if (menuSelection == 2) {
#ifdef __GL__
            useSelector_GL(55);
#endif
          }
          else if (menuSelection == 3) {
#ifdef __GL__
            useSelector_GL(55 * 2);
#endif
          }
          else if (menuSelection == 4) {
#ifdef __GL__
            useSelector_GL(55 * 3);
#endif
          }
          else { /* Assume quit */
#ifdef __GL__
            useSelector_GL(55 * 4);
#endif
          }
          break;
      }

    }

  }

  return;
}
