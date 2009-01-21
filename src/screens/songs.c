#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../graphics/text.h"
#include "main.h"
#include "songs.h"

/* Order of corners: top-left, bottom-left, bottom-right, top-right */
GLcoordsX text_songsX[4];
GLcoordsY text_songsY[4] = { 0.0f, SCREENHEADTEXTHT, SCREENHEADTEXTHT, 0.0f };
GLcoordsX text_byTierX[4];
GLcoordsY text_byTierY[4];

texture_i bg;
text_i text_songs, text_byTier, text_titleAZ, text_artistAZ, text_byBPM;

/* In the case of the songs screen, any character is possible; will be replaced with ? if there is no such texture */

bool screenSongs_buffer() {
  GLint width;
  GLuint i;
  TTF_Font *crillee;
  
  if ((bg = graphics_loadTexture(bgTexture, 0)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", bgTexture);
  
  if ((crillee = TTF_OpenFont(path_italic_crillee, DEFAULT_TEXT_PT))) {
    text_songs = text_load(en_songs, crillee, white, 4);
    width = text_scaleWidth(en_songs, crillee, DEFAULT_TEXT_PT, MENUITEMSHT);
    for ( i = 0; i < 2; i++ ) text_songsX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_songsX[i] = text_songsX[i-2] + width;
  }
  else {
    fprintf(stderr, "Could not open font %s: %s\n", path_italic_crillee, TTF_GetError());
    return false;
  }
  if (crillee)
    TTF_CloseFont(crillee);
  
  return true;
}

GLvoid screenSongs() {
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, bg );
  graphics_positionTexture(fillBGVertexX, fillBGVertexY, defVertexZ);
  
  glPushMatrix(); {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, -1.05f, 5.0f);
    glBindTexture( GL_TEXTURE_2D, text_songs ); /* Top screen title */
    graphics_positionTexture(text_songsX, text_songsY, defVertexZ);
  } glPopMatrix();
  
  return;
}
