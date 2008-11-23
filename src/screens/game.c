#include "../freeband.h"
#include "../graphics/graphics.h"
#include "game.h"
#include "main.h"

bool gamePaused = false;

GLfloat bringDownAngle = 90.0f;
GLfloat NE_coord_neg = 0.0f;
GLfloat NE_coord_pos = 1.0f;

char trackloop_a[] = "GameData/themes/default/screenGame/loop_a.png";

/* Order of corners: top-left, bottom-left, bottom-right, top-right */
GLfloat score_digit1X[] = { 0.0f, 0.0f, 0.05f, 0.05f };
GLfloat score_digit1Y[] = { 0.0f, 0.1f, 0.1f, 0.0f };

GLvoid loadGameTextures() {
  if ((texture[0] = loadTexture(trackloop_a, 0)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", trackloop_a);
  
  return;
}

GLvoid loadGameText() {
  TTF_Font *combo, *score;
  score = TTF_OpenFont(freeSansFont, DEFAULT_TEXT_PT);
  combo = TTF_OpenFont(bitstreamMonoBoldFont, DEFAULT_TEXT_PT);
  if (!combo || !score)
    fprintf(stderr, "SDL_ttf: TTF_OpenFont() response: %s\n", TTF_GetError());
  else {
  
    /* Prepare score for score */
    loadText("0", score, white, 0);
    loadText("1", score, white, 1);
    loadText("2", score, white, 2);
    loadText("3", score, white, 3);
    loadText("4", score, white, 4);
    loadText("5", score, white, 5);
    loadText("6", score, white, 6);
    loadText("7", score, white, 7);
    loadText("8", score, white, 8);
    loadText("9", score, white, 9);
  
    /* Combo numbers */
    loadText("0", combo, white, 10);
    loadText("1", combo, white, 11);
    loadText("2", combo, white, 12);
    loadText("3", combo, white, 13);
    loadText("4", combo, white, 14);
    loadText("5", combo, white, 15);
    loadText("6", combo, white, 16);
    loadText("7", combo, white, 17);
    loadText("8", combo, white, 18);
    loadText("9", combo, white, 19);

  }
}

GLvoid screenGameBuffer() {
  loadGameTextures();
  loadGameText();

  return;
}

GLvoid screenGame() {
  /* Generate track */
  glPushMatrix();
  glRotatef( 90.0f, 0.0f, 0.5f, 0.0f );
  if (bringDownAngle > 0.0f)
    glRotatef( bringDownAngle, 0.0, 0.0f, -1.0f );
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, texture[0] );
  glBegin( GL_QUADS );
    glNormal3f( 0.0f, 0.5f, 0.0f );
    glTexCoord2f( NE_coord_pos, 1.0 ); glVertex3f( -3.5f, 0.5f, -0.5f );
    glTexCoord2f( NE_coord_pos, 0.0 ); glVertex3f( -3.5f, 0.5f,  0.5f );
    glTexCoord2f( NE_coord_neg, 0.0 ); glVertex3f( 2.0f, 0.5f,  0.5f );
    glTexCoord2f( NE_coord_neg, 1.0 ); glVertex3f( 2.0f, 0.5f, -0.5f );
  glEnd();
  glPopMatrix();

  glPushMatrix(); /* Left bumper */
  if (bringDownAngle > 0.0f)
    glRotatef( bringDownAngle, -1.0, 0.0f, 0.0f );
  glTranslatef( -0.5f, 0.5f, -2.0f );
  glColor4f( 0.5f, 0.5f, 0.5f, 1.0f );
  glBindTexture( GL_TEXTURE_2D, 0 );
  gluCylinder( quadratic, 0.01f, 0.01f, 5.0f, 32, 32 );
  glPopMatrix();

  glPushMatrix(); /* Right bumper */
  if (bringDownAngle > 0.0f)
    glRotatef( bringDownAngle, -1.0, 0.0f, 0.0f );
  glTranslatef( 0.5f, 0.5f, -2.0f );
  glColor4f( 0.5f, 0.5f, 0.5f, 1.0f );
  gluCylinder( quadratic, 0.01f, 0.01f, 5.0f, 32, 32 );
  glPopMatrix();
  
  if (bringDownAngle < 0.0f) { /* Only load after track, etc has been placed down entirely */
    /* Score */
    glPushMatrix();
    glTranslatef( -0.5f, 0.0f, 0.0f );
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    glBindTexture( GL_TEXTURE_2D, text[0] );
    positionTexture(score_digit1X, score_digit1Y, defVertexZ);
    glPopMatrix();
  }
  
  NE_coord_neg -= 0.001f;
  NE_coord_pos -= 0.001f;
  
  if (bringDownAngle > 0.0f)
    bringDownAngle -= 0.2f;
  
  return;
}
