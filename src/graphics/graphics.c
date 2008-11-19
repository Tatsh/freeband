#include "../freeband.h"
#include "../screens/main.h"
#include "graphics.h"

/* Negative is to the left, positive is to the right when horizontal (x)
   Negative is to the top, positive is to the bottom when vertical (y)
   Negative is to the outside, positive is going inside (z) */
GLfloat defVertexZ[] = { -2.5f,  -2.5f, -2.5f, -2.5f };    /* All flat facing user textures use this z value */
GLfloat fillBGVertexX[] = {  -1.4f, -1.4f,  1.4f,   1.4f }; /* Fill entire background position */
GLfloat fillBGVertexY[] = { -1.04f, 1.04f, 1.04f, -1.04f };

bool initGL() {
  /* OpenGL functions */
  glEnable(GL_TEXTURE_2D);                /* Enable Texture mapping */
  glShadeModel(GL_SMOOTH);                /* Enable smooth shading */
  glEnable(GL_BLEND);                     /* Enable Alpha channel mapping */
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   /* Black background */
  glViewport(0, 0, 800, 600);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                       /* Reset the current matrix */
  glOrtho(0.0f, 800, 600, 0.0f, -1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glClearDepth(1.0f);                     /* Depth buffer setup */
  glEnable(GL_DEPTH_TEST);                /* Enables Depth Testing */
  glDepthFunc(GL_LEQUAL);                 /* Type of depth testing */

  return true;
}

GLuint loadTexture(const char *filename, int index) {
  SDL_Surface *surface; /* Store information here, size, etc */
  
  if ((surface = IMG_Load(filename))) {
    /* GLU will convert textures to POT before sending to GL */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &texture[index]);
    glBindTexture(GL_TEXTURE_2D, texture[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_PixelFormat *format = surface->format;

    if (format->Amask) /* Check for alpha channel */
      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, surface->w, surface->h, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    else
      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

  }
  else {
    fprintf(stderr, "SDL could not load %s.\n%s\n", filename, SDL_GetError());
    SDL_Quit();
    return -1;
  }
 
  /* Free the SDL_Surface only if it was successfully created */
  if (surface)
    SDL_FreeSurface(surface);
  else
    return -1;

  return texture[index];
}

GLuint loadText(char *text, TTF_Font *font, SDL_Color color, int index) {
  SDL_Surface *textTexture;
  
  /* Use SDL_TTF to render our text */
  if ( (textTexture = TTF_RenderText_Blended(font, text, color)) ) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &texture[index]);
    glBindTexture(GL_TEXTURE_2D, texture[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, textTexture->w, textTexture->h, GL_RGBA, GL_UNSIGNED_BYTE, textTexture->pixels);
  }
  else {
    fprintf(stderr, "SDL_ttf could render %s.\n%s\n", text, TTF_GetError());
    SDL_Quit();
    return -1;
  }

  /* Clean up */
  if (textTexture)
    SDL_FreeSurface(textTexture);
  else
    return -1;
  
  return texture[index];
}

GLvoid positionTexture(GLfloat *vertexX, GLfloat *vertexY, GLfloat *vertexZ) {

  glBegin(GL_QUADS);
    glTexCoord2f( 0.0f, 0.0f ); glVertex3f( vertexX[0], vertexY[0], vertexZ[0] ); /* Top left corner */
    glTexCoord2f( 0.0f, 1.0f ); glVertex3f( vertexX[1], vertexY[1], vertexZ[1] ); /* Bottom left corner */
    glTexCoord2f( 1.0f, 1.0f ); glVertex3f( vertexX[2], vertexY[2], vertexZ[2] ); /* Bottom right corner */
    glTexCoord2f( 1.0f, 0.0f ); glVertex3f( vertexX[3], vertexY[3], vertexZ[3] ); /* Top right corner */
  glEnd();

  return;
}

bool resizeWindow(int width, int height) {
  GLfloat ratio; /* Height/width ration */

  if (height == 0)  /* Protect against a divide by zero */
    height = 1;

  ratio = (GLfloat)width / (GLfloat)height;
  glViewport(0, 0, (GLsizei)width, (GLsizei)height ); /* Setup our viewport. */
  glMatrixMode(GL_PROJECTION); /* change to the projection matrix and set our viewing volume. */
  glLoadIdentity();
  gluPerspective( 45.0f, ratio, 0.1f, 100.0f ); /* Set our perspective */
  glMatrixMode(GL_MODELVIEW); /* Make sure we're chaning the model view and not the projection */
  glLoadIdentity(); /* Reset the view */

  return true;
}

void drawFreeband(GLvoid) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* Clear the screen and the depth buffer */

  glLoadIdentity();
  glScalef(1, -1, 1); /* Flip framebuffer because of SDL's upside down issue */
  
  glPushMatrix();
  if (currentScreen.mainMenu == true)
    screenMain();
  glPopMatrix();

  SDL_GL_SwapBuffers();

#ifdef __DEBUG__
  /* Gather our frames per second */
  static GLint T0     = 0;
  static GLint Frames = 0;
  GLint t = SDL_GetTicks();
  Frames++; {
    if (t - T0 >= 5000) {
      GLfloat seconds = (t - T0) / 1000.0;
      GLfloat fps = Frames / seconds;
      printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
      T0 = t;
      Frames = 0;
    }
  }
#endif

  return;
}
