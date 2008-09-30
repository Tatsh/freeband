#include "../freeband.h"

#ifdef __GL__
void init_GL()
{
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
}

#endif
