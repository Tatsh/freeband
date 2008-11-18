#include "../freeband.h"

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

GLuint nPow2(int x) {
  GLint pow2 = 1;

  while (pow2 < x)
    pow2 <<= 1;

  return pow2;
}

GLuint getNumColors(SDL_Surface *surface) {
  int nOfColors;
  nOfColors = surface->format->BytesPerPixel;

  return nOfColors;
}

GLuint loadTexture(char *filename) {
  GLuint texID; /* Store handle here */
  SDL_Surface *imageInfo; /* Store information here, size, etc */
  GLenum textureFormat;
  GLuint nOfColors; /* Used to figure out if texture has an alpha channel */
  GLuint newWidth, newHeight; /* Dimensions of the texture since texture must be pow2 x pow2 */
  
  if ((imageInfo = IMG_Load_RW(SDL_RWFromFile(filename, "rb"), 1))) {

    /* Check that a texture's width is a power of two */
    if ((imageInfo->w & (imageInfo->w - 1)) != 0) { /* We cannot use boolean values here */
#ifdef __DEBUG__
      fprintf(stderr, "%s's width is not a power of 2. Scaling...\n", filename);
#endif
      newWidth = nPow2(imageInfo->w);
    }

    /* Also check that heigh is a power of 2 */
    if ((imageInfo->h & (imageInfo->h - 1)) != 0) {
#ifdef __DEBUG__
      fprintf(stderr, "%s's height is not a power of 2. Scaling...\n", filename);
#endif
      newHeight = nPow2(imageInfo->h);
    }
    
    if (newWidth >= 2048 && newHeight >= 2048) { /* limitation of OpenGL; textures cannot be 2048x2048 and textures may not exceed 2048 in width or height */
      newWidth = 2048;
      newHeight = 1024;
    }
    else if (newWidth >= 2048 && newHeight <= 1024)
      newWidth = 2048;
    else if (newHeight >= 2048 && newWidth <= 1024)
      newHeight = 2048;

    /* Set special modes based upon alpha channel presence */
    nOfColors = getNumColors(imageInfo);
    if (nOfColors == 4) {
      /* Does contain an alpha channel */
      if (imageInfo->format->Rmask == 0x000000ff)
        textureFormat = GL_RGBA;
      else
        textureFormat = GL_BGRA;
    }
    else if (nOfColors == 3) {
      /* Does not contain an alpha channel */
      if (imageInfo->format->Rmask == 0x000000ff)
        textureFormat = GL_RGB;
      else
        textureFormat = GL_BGR;
    }
    else {
      fprintf(stderr, "Warning: %s is not true colour. This may cause a problem.\n", filename);
      return 1;
    }

    glGenTextures(MAX_TEXTURES, &texture[0]);

    /* Bind the texture object */
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    /* Set the texture's stretching properties */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Edit the texture object's image data using the information SDL_Surface gives us */
    glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, newWidth, newHeight, 0, textureFormat, GL_UNSIGNED_BYTE, imageInfo->pixels);
  }
  else {
    fprintf(stderr, "SDL could not load %s.\n%s\n", filename, SDL_GetError());
    SDL_Quit();
    return 1;
  }
 
  /* Free the SDL_Surface only if it was successfully created */
  if (imageInfo) {
#ifdef __DEBUG__
    fprintf(stdout, "%s: nPow2(imageInfo->w) = %d; nPow2(imageInfo->h) = %d\n", filename, nPow2(imageInfo->w), nPow2(imageInfo->h));
    fprintf(stdout, "%s: texID: %d\n", filename, texID);
#endif
    SDL_FreeSurface(imageInfo);
  }
  else {
    return -1;
  }

  return texture[0];
}

GLvoid drawGLCube( GLvoid ) {
  glBegin(GL_QUADS);
  /* Back Face */
  glNormal3f( 0.0f, 0.0f, -0.5f);
  glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
  glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f,  1.0f, -1.0f );
  glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  1.0f,  1.0f, -1.0f );
  glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  1.0f, -1.0f, -1.0f );
  
  glEnd();

  return;
}

bool resizeWindow(int width, int height) {
  GLfloat ratio; /* Height/width ration */

  if (height == 0)  /* Protect against a divide by zero */
    height = 1;

  ratio = ( GLfloat )width / ( GLfloat )height;
  glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height ); /* Setup our viewport. */
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
  glTranslatef( 0.0f, 0.0f, -2.0f );
  glScalef(1, -1, 1); /* Flip texture because of SDL's upside down issue */
  
  glBindTexture( GL_TEXTURE_2D, texture[0] );

    drawGLCube();

  SDL_GL_SwapBuffers();

#ifdef __DEBUG__
  /* Gather our frames per second */
  static GLint T0     = 0;
  static GLint Frames = 0;
  GLint t = SDL_GetTicks();
  Frames++; {
    if (t - T0 >= 1000) {
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
