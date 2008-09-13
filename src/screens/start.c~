#include "../freeband.h"

#define SELECTBLENDSRC  0.30
#define SELECTBLENDDEST 0.60

#ifdef __GL__
int loadBG_GL()
{
  GLuint texture;     /* This is a handle to our texture object */
  SDL_Surface *surface; /* This surface will tell us the details of the image */
  GLenum texture_format;
  GLint nOfColors;

  if ((surface = IMG_Load_RW(SDL_RWFromFile("themes/default/global/bg.png", "rb"), 1)))
  { 

    /* Check that the image's width is a power of 2 */
    if ((surface->w & (surface->w - 1)) != 0)
    {
      printf("warning: image.png's width is not a power of 2\n");
    }

    /* Also check if the height is a power of 2 */
    if ((surface->h & (surface->h - 1)) != 0)
    {
      printf("warning: image.png's height is not a power of 2\n");
    }
 
    /* get the number of channels in the SDL surface */
    nOfColors = surface->format->BytesPerPixel;
    if (nOfColors == 4)     /* contains an alpha channel */
    {
      if (surface->format->Rmask == 0x000000ff)
        texture_format = GL_RGBA;
      else
        texture_format = GL_BGRA;
    }
    else if (nOfColors == 3)     /* no alpha channel */
    {
      if (surface->format->Rmask == 0x000000ff)
        texture_format = GL_RGB;
      else
        texture_format = GL_BGR;
    } 
    else
    {
      printf("warning: the image is not truecolor..  this will probably break\n");
      return 1;
    }

    glGenTextures(1, &texture);
 
    /* Bind the texture object */
    glBindTexture(GL_TEXTURE_2D, texture);
 
    /* Set the texture's stretching properties */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
    /* Edit the texture object's image data using the information SDL_Surface gives us */
    glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                 texture_format, GL_UNSIGNED_BYTE, surface->pixels);
  } 
  else
  {
    printf("SDL could not load image.png: %s\n", SDL_GetError());
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
 
  glBegin(GL_QUADS);
  /* For flat objects, glTexCoord3i is ALWAYS (0, 0), (1, 0), (1, 1), (0, 1) consecutively when in this order (TL, TR, BR, BL) */
  glTexCoord2i(0, 0); glVertex2i(0, 0); /* Top-left vertex (corner) */
  glTexCoord2i(1, 0); glVertex2i(800, 0); /* Top-right vertex */
  glTexCoord2i(1, 1); glVertex2i(800, 600); /* Bottom-right vertex (corner) */
  glTexCoord2i(0, 1); glVertex2i(0, 600); /* Bottom-left vertex (x offset, same y offset as above) */
  glEnd();

  SDL_GL_SwapBuffers();
  
  glDeleteTextures(1, &texture);

  return 0;
}

int loadLogo_GL()
{
  GLuint texture;
  SDL_Surface *surface;
  GLenum texture_format;
  GLint nOfColors;
  
  if ((surface = IMG_Load_RW(SDL_RWFromFile("themes/default/screenStart/banner.png", "rb"), 1)))
  { 

    if ( (surface->w & (surface->w - 1)) != 0 ) {
      printf("warning: image.png's width is not a power of 2\n");
    }

    if ( (surface->h & (surface->h - 1)) != 0 ) {
      printf("warning: image.png's height is not a power of 2\n");
    }

    nOfColors = surface->format->BytesPerPixel;
    if (nOfColors == 4) /* has an alpha channel */
    {
      if (surface->format->Rmask == 0x000000ff)
        texture_format = GL_RGBA;
      else
        texture_format = GL_BGRA;
    }
    else if (nOfColors == 3) /* no alpha channel */
    {
      if (surface->format->Rmask == 0x000000ff)
        texture_format = GL_RGB;
      else
        texture_format = GL_BGR;
    } 
    else
    {
      printf("Warning: the image is not true colour. This will probably break.\n");
      return 1;
    }

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                 texture_format, GL_UNSIGNED_BYTE, surface->pixels);
  } 
  else {
    printf("SDL could not load image.png: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  if (surface)
  {
    SDL_FreeSurface(surface);
  }

  glBindTexture(GL_TEXTURE_2D, texture);
 
  glBegin(GL_QUADS);
  /* For flat objects, glTexCoord3i is ALWAYS (0, 0), (1, 0), (1, 1), (0, 1) consecutively when in this order */
  glTexCoord2i(0, 0); glVertex2i(10+82, 10+82); /* Top-left vertex (corner); 82 pixels is the offset away from top-corner */
  glTexCoord2i(1, 0); glVertex2i(638+82, 10+82); /* Top-right vertex */
  glTexCoord2i(1, 1); glVertex2i(638+82, 245+82); /* Bottom-right vertex (corner) */
  glTexCoord2i(0, 1); glVertex2i(10+82, 245+82); /* Bottom-left vertex (x offset, same y offset as above) */
  glEnd();

  SDL_GL_SwapBuffers();
  
  glDeleteTextures(1, &texture);
  return 0;
}

int loadSelector_GL()
{
  GLuint texture;
  SDL_Surface *surface;
  GLenum texture_format;
  GLint nOfColors;
  
  char *image = "themes/default/screenStart/selector.png";
  
  if ((surface = IMG_Load_RW(SDL_RWFromFile(image, "rb"), 1)))
  { 

    if ((surface->w & (surface->w - 1)) != 0)
    {
      printf("warning: %s's width is not a power of 2\n", image);
    }

    if ((surface->h & (surface->h - 1)) != 0)
    {
      printf("warning: %s's width is not a power of 2\n", image);
    }


    nOfColors = surface->format->BytesPerPixel;
    if (nOfColors == 4)     /* contains an alpha channel */
    {
      if (surface->format->Rmask == 0x000000ff)
        texture_format = GL_RGBA;
      else
        texture_format = GL_BGRA;
    }
    else if (nOfColors == 3)     /* no alpha channel */
    {
      if (surface->format->Rmask == 0x000000ff)
        texture_format = GL_RGB;
      else
        texture_format = GL_BGR;
    }
    else
    {
      printf("warning: the image is not truecolor..  this will probably break\n");
      return 1;
    }

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);
  }
  else
  {
    printf("SDL could not load image.png: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  if (surface)
  {
    SDL_FreeSurface(surface);
  }

  glBindTexture(GL_TEXTURE_2D, texture);
  glColor4f(1.0, 1.0, 1.0, SELECTBLENDSRC); /* Set alpha to SELECTBLENDSRC but keep all other colours the same, before loop */

  glBegin(GL_QUADS);
  glColor4f(1.0f, 1.0f, 1.0f, SELECTBLENDSRC);
  /* For flat objects, glTexCoord2i is ALWAYS (0, 0), (1, 0), (1, 1), (0, 1) consecutively when in this order */
  glTexCoord2i(0, 0); glVertex2i(425, 300); /* Top-left vertex (top-left position away from top-left part of screen) */
  glTexCoord2i(1, 0); glVertex2i(340+425, 300); /* Top-right vertex */
  glTexCoord2i(1, 1); glVertex2i(340+425, 360); /* Bottom-right vertex */
  glTexCoord2i(0, 1); glVertex2i(425, 360); /* Bottom-left vertex (x offset, same y offset as above) */
  glEnd();
  
  SDL_GL_SwapBuffers();
  glDeleteTextures(1, &texture);
  
  return 0;
}
#endif

struct selection {
  int singlePlayer;
  int multiplayer;
  int online;
  int options;
  int quit;
} mainMenu;

void showMainMenu()
{
#ifdef __GL__
  enableMenuGL();
  loadBG_GL();
  loadLogo_GL();
  loadSelector_GL();
/*  showMainMenuOptions_GL(); */
#endif

  SDL_Event startmenu;
  int running = 1;
  mainMenu.singlePlayer = 1;

  /* Main loop to keep window running */
  while(running) {
    while(SDL_PollEvent(&startmenu)) {
      switch(startmenu.type){
        /* End loop if user hits ESC or closes the window */
        case SDL_KEYDOWN:
          if (startmenu.key.keysym.sym == SDLK_ESCAPE)
            running = 0;
          else if (startmenu.key.keysym.sym == SDLK_DOWN) {
            if (mainMenu.singlePlayer == 1) {
              mainMenu.singlePlayer = 0;
              mainMenu.multiplayer = 1;
              printf("Multiplayer selected.\n");
            }
            else if (mainMenu.multiplayer == 1) {
              mainMenu.multiplayer = 0;
              mainMenu.online = 1;
              printf("Online selected.\n");
            }
            else if (mainMenu.online == 1) {
              mainMenu.online = 0;
              mainMenu.options = 1;
              printf("Options selected.\n");
            }
            else if (mainMenu.options == 1) {
              mainMenu.options = 0;
              mainMenu.quit = 1;
              printf("Quit selected.\n");
            }
            /* Cycled through all menu options using just the down arrow */
            else {
              mainMenu.quit = 0;
              mainMenu.singlePlayer = 1;
              printf("Single player selected.\n");
            }
          }
          else if (startmenu.key.keysym.sym == SDLK_UP) {
            /* Backwards of above code */
            if (mainMenu.singlePlayer == 1) {
              mainMenu.singlePlayer = 0;
              mainMenu.quit = 1;
              printf("Quit selected.\n");
            }
            else if (mainMenu.quit == 1) {
              mainMenu.quit = 0;
              mainMenu.options = 1;
              printf("Options selected.\n");
            }
            else if (mainMenu.options == 1) {
              mainMenu.options = 0;
              mainMenu.online = 1;
              printf("Online selected.\n");
            }
            else if (mainMenu.online == 1) {
              mainMenu.online = 0;
              mainMenu.multiplayer = 1;
              printf("Multiplayer selected.\n");
            }
            /* Cycled through all menu options using just the up arrow */
            else {
              mainMenu.multiplayer = 0;
              mainMenu.singlePlayer = 1;
              printf("Single player selected.\n");
            }
          }
          /* User selects mode to play */
          else if (startmenu.key.keysym.sym == SDLK_RETURN) {
              if (mainMenu.singlePlayer == 1) {
                printf("Starting single player mode.\n");
                /* startGame(1); */
              }
              else if (mainMenu.multiplayer == 1) {
                printf("Starting multiplayer mode.\n");
                /* int numPlayers;
                  Check if enumControllers found any, otherwise set value to 2
                if (enumControllers() == -1)
                  numPlayers = 2;
                else
                  numPlayers = enumControllers();
                startGame(numPlayers); */
              }
              else if (mainMenu.online == 1)
                printf("Starting online mode.\n");
              /* int numPlayers;
                 Check if enumControllers found any, otherwise set value to 1
                if (enumControllers() == -1)
                  numPlayers = 1;
                else
                  numPlayers = enumControllers();
                startGame(numPlayers); */
              else if (mainMenu.options == 1)
                printf("Going to options menu.\n");
/*
#ifdef __GL__
                showOptionsMenu_GL();
#else
                showOptionsMenu();
#endif */
              else /* Assume selection is Quit */ {
                printf("Quitting...\n");
                running = 0;
              }
          }
          break;
        case SDL_QUIT:
          running = 0;
          break;
      }
    }
  }
}
