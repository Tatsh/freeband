#include "../freeband.h"
#include "graphics.h"
#include "text.h"
#include "../io/prefs.h"
#include "../screens/difficulty.h"
#include "../screens/game.h"
#include "../screens/instruments.h"
#include "../screens/main.h"
#include "../screens/pause.h"
#include "../screens/songs.h"

bool graphics_loading;

GLcolour buttonColour_green[] = { 0.137f, 0.585, 0.0f, 1.0f };
GLcolour buttonColour_red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLcolour buttonColour_yellow[] = { 1.0f, 1.0f, 0.0, 1.0f };
GLcolour buttonColour_blue[] = { 0.059f, 0.0f, 0.71f, 1.0f};
GLcolour buttonColour_orange[] = { 1.0f, 0.647, 0.114, 1.0f };

GLcolour colour_blue_7CA4F6[] = { 0.484f, 0.643f, 0.964f, 1.0f }; /* approximations */
GLcolour colour_yellow_F0FF07[] = { 0.941, 1.0f, 0.027f, 1.0f };

/* Negative is to the left, positive is to the right when horizontal (x)
   Negative is to the top, positive is to the bottom when vertical (y)
   Negative is to the outside, positive is going inside (z)
   Order of corners: top-left, bottom-left, bottom-right, top-right */
GLcoordsZ defVertexZ[] = { 0.0f, 0.0f, 0.0f, 0.0f };    /* All flat facing user textures use this z value */
GLcoordsX fillBGVertexX[] = {  -1.4f, -1.4f,  1.4f,   1.4f }; /* Fill entire background position */
GLcoordsY fillBGVertexY[] = { -1.04f, 1.04f, 1.04f, -1.04f };
GLcoordsX offscreenVertexXY[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat z = -2.5f;

GLUquadricObj *quadratic;

SDL_Color blue_7CA4F6;
SDL_Color yellow;
SDL_Color white;

bool graphics_initGL() {
  /* OpenGL functions */
  glEnable(GL_TEXTURE_2D);                /* Enable texture mapping */
  glShadeModel(GL_SMOOTH);                /* Enable smooth shading */
  glEnable(GL_BLEND);                     /* Enable Alpha channel mapping */
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   /* Black background */
  glViewport(0, 0, prefs_Graphics.width, prefs_Graphics.height);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                       /* Reset the current matrix */
  glOrtho(0.0f, prefs_Graphics.width, prefs_Graphics.height, 0.0f, -1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearDepth(1.0f);                     /* Depth buffer setup */
  glEnable(GL_DEPTH_TEST);                /* Enables depth testing */
  glDepthFunc(GL_LEQUAL);                 /* Type of depth testing */

  quadratic = gluNewQuadric();
  /* Create Smooth Normals */
  gluQuadricNormals(quadratic, GLU_SMOOTH);
  /* Create Texture Coords */
  gluQuadricTexture(quadratic, GL_TRUE);

  return true;
}

bool graphics_resizeWindow(GLuint width, GLuint height) {
  GLfloat ratio; /* Height/width ratio */

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

/* Currently only working with x-axis */
GLfloat graphics_centreAtX(GLfloat x, GLfloat width) {
  GLfloat offset;

  offset = (width / 2.0f) - x;

  if ((offset < 0.0f && x > 0.0f) || (width >= (x * 2)))
    return -offset;
  else
    return offset;
}

GLint graphics_getTextureHeight(const char filename[]) {
  GLint height;
  SDL_Surface *temp;
  
  if ((temp = IMG_Load(filename))) {
    height = temp->h;
  }
  else
    return -1.0f;
  
  if (temp)
    SDL_FreeSurface(temp);
  
  return height;
}

GLint graphics_getTextureWidth(const char filename[]) {
  GLint width;
  SDL_Surface *temp;
  
  if ((temp = IMG_Load(filename))) {
    width = temp->w;
  }
  else
    return -1.0f;
  
  if (temp)
    SDL_FreeSurface(temp);
  
  return width;
}

/* These scaling functions have nothing to do with below loading functions
   Use only when you know the image's original dimensions; this helps with theming; more functionality later
   This is also useful for text, specify any height or width (in pixels) and get the correct corresponding width or height for an
     texture */
GLfloat graphics_scaleTextureHeight(GLuint pWidth, GLuint pHeight, GLfloat destWidth) {
  GLfloat destHeight;
  
  destHeight = ((GLfloat)pHeight / (GLfloat)pWidth) * destWidth;
  
  return destWidth;
}

GLfloat graphics_scaleTextureWidth(GLuint pWidth, GLuint pHeight, GLfloat destHeight) {
  GLfloat destWidth;
  
  destWidth = ((GLfloat)pWidth / (GLfloat)pHeight) * destHeight;
  
  return destWidth;
}

GLint graphics_loadTexture(const char filename[], GLuint i) {
  SDL_Surface *surface; /* Store information here, size, etc */
  
  if ((surface = IMG_Load(filename))) {
    /* GLU will convert textures to POT before sending to GL */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &texture[i]);
    glBindTexture(GL_TEXTURE_2D, texture[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    SDL_PixelFormat *format = surface->format;

    if (format->Amask) /* Check for alpha channel */
      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, surface->w, surface->h, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    else
      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
  }
  else {
    fprintf(stderr, "SDL could not load %s.\n%s\n", filename, SDL_GetError());
    fb_quit(1);
  }
 
  /* Free the SDL_Surface only if it was successfully created */
  if (surface)
    SDL_FreeSurface(surface);
  else
    return -1;

  return texture[i];
}

GLvoid graphics_clear() {
  glDeleteTextures(MAX_IMAGES, &texture[0]); /* Clean up old screen */
  glDeleteTextures(MAX_TEXT, &text[0]);
  return;
}

GLvoid graphics_positionTexture(GLfloat *vertexX, GLfloat *vertexY, GLfloat *vertexZ) {

  glBegin(GL_QUADS); /* Do not change this order */
    glTexCoord2f( 0.0f, 0.0f ); glVertex3f( vertexX[0], vertexY[0], vertexZ[0] ); /* Top left corner */
    glTexCoord2f( 0.0f, 1.0f ); glVertex3f( vertexX[1], vertexY[1], vertexZ[1] ); /* Bottom left corner */
    glTexCoord2f( 1.0f, 1.0f ); glVertex3f( vertexX[2], vertexY[2], vertexZ[2] ); /* Bottom right corner */
    glTexCoord2f( 1.0f, 0.0f ); glVertex3f( vertexX[3], vertexY[3], vertexZ[3] ); /* Top right corner */
  glEnd();

  return;
}

GLvoid graphics_initColours() {
  blue_7CA4F6.r = 253;
  blue_7CA4F6.g = 166;
  blue_7CA4F6.b = 118;
  
  white.r = 255; /* White */
  white.g = 255;
  white.b = 255;
    
  yellow.r = 7; /* r and b are reversed because we load a BGR space with OpenGL */
  yellow.g = 255;
  yellow.b = 240;
  
  return;
}

GLvoid graphics_draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* Clear the screen and the depth buffer */
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, z);
  
  glScalef(1, -1, 1); /* Flip framebuffer because of SDL's upside down issue */

  if (graphics_loading); /* Do nothing and wait till loading = false */
  else if (fb_screen.mainMenu && !menuQuit)
    screenMain();
  else if (fb_screen.instruments && !menuQuit)
    screenInstruments(fb_nPlayers);
  else if (fb_screen.songs && !menuQuit)
    screenSongs();
  else if (fb_screen.difficulty && !menuQuit)
    screenDifficulty(fb_nPlayers);
  else if (fb_screen.game)
    screenGame();

  SDL_GL_SwapBuffers();

  /* Gather our frames per second */
  static GLuint Frames = 0;
  Frames++;
#ifdef __DEBUG__
  static GLuint T0     = 0;
  GLuint t = SDL_GetTicks();
  if (t - T0 >= 5000) {
    GLfloat seconds = (t - T0) / 1000.0;
    GLfloat fps = Frames / seconds;
    printf("%d frames in %.0f seconds = %g FPS\n", Frames, seconds, fps);
    T0 = t;
    Frames = 0;
  }
#endif

  return;
}
