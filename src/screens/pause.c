#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../graphics/text.h"
#include "../input/input.h"
#include "game.h"
#include "main.h"
#include "pause.h"

GLcoordsX text_pausedX[4];
GLcoordsY text_pausedY[] = { 0.0f, 0.21f, 0.21f, 0.0f };

text_i text_paused;

bool screenPause_buffer() {
  GLuint i;
  GLfloat width;
  TTF_Font *bitstream;
  
  if ((bitstream = TTF_OpenFont(path_bold_bitstreamVeraSans, DEFAULT_TEXT_PT))) {
    text_paused = text_load(en_paused, bitstream, white, 0);
    width = text_scaleWidth(en_paused, bitstream, DEFAULT_TEXT_PT, 0.21f);
    for ( i = 0; i < 2; i++ ) text_pausedX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_pausedX[i] = text_pausedX[i-2] + width;
  }
  if (bitstream)
    TTF_CloseFont(bitstream);
  
  return true;
}

GLvoid screenPause() {
  glPushMatrix(); {
    glTranslatef(0.0f, -0.35f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture( GL_TEXTURE_2D, text_paused );
    graphics_positionTexture(text_pausedX, text_pausedY, defVertexZ);
  } glPopMatrix();
  
  return;
}
