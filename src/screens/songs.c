#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../graphics/text.h"
#include "main.h"
#include "songs.h"
#include "songlist.h"

/* Order of corners: top-left, bottom-left, bottom-right, top-right */
GLcoordsX text_songsX[4];
GLcoordsY text_songsY[4] = { 0.0f, SCREENHEADTEXTHT, SCREENHEADTEXTHT, 0.0f  };

GLcoordsX text_byTierX[4];
GLcoordsX text_titleAZX[4];
GLcoordsX text_artistAZX[4];
GLcoordsX text_byBPMX[4];

GLcoordsY text_sortY[4] = { 0.0, SORT_TEXT_HT, SORT_TEXT_HT, 0.0f };

texture_i bg;
text_i text_songs, text_byTier, text_titleAZ, text_artistAZ, text_byBPM;
song_sort byTier_s, titleAZ_s, artistAZ_s, byBPM_s;

/* In the case of the songs screen, any character is possible (this should be multilingual as possible using Unicode)
  Unknown characters (ones not in the font being used) will be replaced with ' ' */

bool screenSongs_buffer() {
  GLfloat width;
  ushort i;
  TTF_Font *crillee, *freeSans;
  
  byTier_s = true; /* Set default sort */
  
  if ((bg = graphics_loadTexture(bgTexture, 0)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", bgTexture);
  
  if ((crillee = TTF_OpenFont(path_italic_crillee, DEFAULT_TEXT_PT))) {
    text_songs = text_load(en_songs, crillee, white);
    width = text_scaleWidth(en_songs, crillee, SCREENHEADTEXTHT);
    for ( i = 0; i < 2; i++ ) text_songsX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_songsX[i] = text_songsX[i-2] + width;
  }
  else {
    fprintf(stderr, "instruments.c: screenInstrumentsBuffer(): Could not open font %s: %s\n", path_italic_crillee, TTF_GetError());
    return false;
  }
  if (crillee)
    TTF_CloseFont(crillee);
  
  if ((freeSans = TTF_OpenFont(path_regular_freeSans, DEFAULT_TEXT_PT))) {
    text_byTier = text_load(en_songs_by_tier, freeSans, white);
    width = text_scaleWidth(en_songs_by_tier, freeSans, SORT_TEXT_HT);
    for ( i = 0; i < 2; i++ ) text_byTierX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_byTierX[i] = text_byTierX[i-2] + width;
    
    text_titleAZ = text_load(en_songs_az, freeSans, white); /* Why won't this load?! */
    width = text_scaleWidth(en_songs_az, freeSans, SORT_TEXT_HT);
    for ( i = 0; i < 2; i++ ) text_titleAZX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_titleAZX[i] = text_titleAZX[i-2] + width;
    
    text_artistAZ = text_load(en_songs_alpha_artist, freeSans, white);
    width = text_scaleWidth(en_songs_alpha_artist, freeSans, SORT_TEXT_HT);
    for ( i = 0; i < 2; i++ ) text_artistAZX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_artistAZX[i] = text_artistAZX[i-2] + width;
    
    text_byBPM = text_load(en_songs_by_bpm, freeSans, white);
    width = text_scaleWidth(en_songs_by_bpm, freeSans, SORT_TEXT_HT);
    for ( i = 0; i < 2; i++ ) text_byBPMX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_byBPMX[i] = text_byBPMX[i-2] + width;
  }
  else {
    fprintf(stderr, "instruments.c: screenInstrumentsBuffer(): Could not open font %s: %s\n", path_regular_freeSans, TTF_GetError());
    return false;
  }
  if (freeSans)
    TTF_CloseFont(freeSans);
  
  if (!screenMenuFooter_buffer()) {
    fprintf(stderr, "Unable to buffer screenMenuFooter.\n");
    return false;
  }
  
  return true;
}

GLvoid screenSongs() {
  glPushMatrix(); {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture( GL_TEXTURE_2D, bg );
    graphics_positionTexture(fillBGVertexX, fillBGVertexY, defVertexZ);
  } glPopMatrix();
  
  glPushMatrix(); {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, SCREENHEADTEXTOFFSET, 0.0f);
    glBindTexture( GL_TEXTURE_2D, text_songs ); /* Top screen title */
    graphics_positionTexture(text_songsX, text_songsY, defVertexZ);
  } glPopMatrix();

  glPushMatrix(); {
    if (byTier_s) {
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBindTexture( GL_TEXTURE_2D, text_byTier );
      glTranslatef(offset_screenSongs_sortByTier_x, SORT_TEXT_Y_OFFSET, 0.0f);
      graphics_positionTexture(text_byTierX, text_sortY, defVertexZ);
    }
    else if (titleAZ_s) {
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBindTexture( GL_TEXTURE_2D, text_titleAZ );
      glTranslatef(offset_screenSongs_sortAZTitle_x, SORT_TEXT_Y_OFFSET, 0.0f);
      graphics_positionTexture(text_titleAZX, text_sortY, defVertexZ);
    }
    else if (artistAZ_s) {
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBindTexture( GL_TEXTURE_2D, text_artistAZ );
      glTranslatef(offset_screenSongs_sortAZArtist_x, SORT_TEXT_Y_OFFSET, 0.0f);
      graphics_positionTexture(text_artistAZX, text_sortY, defVertexZ);
    }
    else {
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBindTexture( GL_TEXTURE_2D, text_byBPM );
      glTranslatef(offset_screenSongs_sortbyBPM_x, SORT_TEXT_Y_OFFSET, 0.0f);
      graphics_positionTexture(text_byBPMX, text_sortY, defVertexZ);
    }
  } glPopMatrix();
  
  screenMenuFooter();
  
  return;
}
