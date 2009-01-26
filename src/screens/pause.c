#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../graphics/text.h"
#include "../input/input.h"
#include "game.h"
#include "main.h"
#include "pause.h"

bool screenPause_resumeHl;

/* Pause header */
GLcoordsX text_pausedX[4];
GLcoordsY text_pausedY[] = { 0.0f, 0.2f, 0.2f, 0.0f };

GLcoordsX text_resumeX[4];
GLcoordsY text_resumeY[] = { 0.0f, 0.15f, 0.15f, 0.0f };

text_i text_paused, text_resume;

bool screenPause_buffer() {
  GLuint i;
  GLfloat width;
  TTF_Font *bitstream;
  
  screenPause_resumeHl = true;
  
  if ((bitstream = TTF_OpenFont(path_bold_bitstreamVeraSans, DEFAULT_TEXT_PT))) {
    text_paused = text_load(en_paused, bitstream, white, 0);
    width = text_scaleWidth(en_paused, bitstream, DEFAULT_TEXT_PT, 0.2f);
    for ( i = 0; i < 2; i++ ) text_pausedX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_pausedX[i] = text_pausedX[i-2] + width;
    
    text_resume = text_load(en_resume, bitstream, white, 1);
    width = text_scaleWidth(en_resume, bitstream, DEFAULT_TEXT_PT, 0.15f);
    for ( i = 0; i < 2; i++ ) text_resumeX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_resumeX[i] = text_resumeX[i-2] + width;
  }
  if (bitstream)
    TTF_CloseFont(bitstream);
  
  return true;
}

GLvoid screenPause() {
  glPushMatrix(); {
    glTranslatef(0.0f, -0.5f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture( GL_TEXTURE_2D, text_paused );
    graphics_positionTexture(text_pausedX, text_pausedY, defVertexZ);
  } glPopMatrix();
  
  glPushMatrix(); {
    glTranslatef(0.0f, -0.3f, 0.0f);
    if (screenPause_resumeHl)
      glColor4f( buttonColour_yellow[0], buttonColour_yellow[1], buttonColour_yellow[2], buttonColour_yellow[3] );
    else
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture( GL_TEXTURE_2D, text_resume );
    graphics_positionTexture(text_resumeX, text_pausedY, defVertexZ);
  } glPopMatrix();
  
  return;
}
