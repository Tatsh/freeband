#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../graphics/text.h"
#include "instruments.h"
#include "main.h"
#include "songs.h"

GLcoordsX text_GuitarX[4];
GLcoordsY text_GuitarY[] = { 0.0f, MENUITEMSHT, MENUITEMSHT, 0.0f };
GLcoordsX text_BassX[4];
GLcoordsY text_BassY[4];
GLcoordsX text_DrumsX[4];
GLcoordsY text_DrumsY[4];
GLcoordsX text_VocalsX[4];
GLcoordsY text_VocalsY[4];

GLcoordsX text_Guitar_hl[4];
GLcoordsX text_Bass_hl[4];
GLcoordsX text_Drums_hl[4];
GLcoordsX text_Vocals_hl[4];

GLcoordsX text_SelectInstrumentX[4]; /* Crillee is italic on its own, this makes it appear not italic */
GLcoordsY text_SelectInstrumentY[] = { 0.0f, SCREENHEADTEXTHT, SCREENHEADTEXTHT, 0.0f };

GLfloat degree = 0.0f;

texture_i bg;
texture_i text_guitar, text_bass, text_drums, text_vocals;
texture_i text_selectInstrument;

GLuint screenInstruments_nSelection = 0; /* Guitar */

tInstrument instrument_P1;

GLvoid screenInstruments_accept() {
  switch(screenInstruments_nSelection) {
    case 0:
#ifdef __DEBUG__
      fprintf(stdout, "Starting %d player guitar game.\n", fb_nPlayers);
#endif
      break;
      
    case 1:
#ifdef __DEBUG__
      fprintf(stdout, "Starting %d player bass game.\n", fb_nPlayers);
#endif      
      break;
      
    case 2:
#ifdef __DEBUG__
      fprintf(stdout, "Starting %d player drums game.\n", fb_nPlayers);
#endif
      break;
      
    case 3:
#ifdef __DEBUG__
      fprintf(stdout, "Starting %d player vocals game.\n", fb_nPlayers);
#endif
      break;
      
    default:
      break;
  }

  menuQuit = true;
  graphics_loading = true;
  graphics_clear();
#ifdef __DEBUG__
  fprintf(stdout, "Deleted all screenInstruments elements.\nLoading screenSongs elements...\n");
#endif
  fb_screen.instruments = graphics_loading = menuQuit = false;
  fb_screen.songs = true;

  return;
}

GLvoid screenInstruments_highlighted(GLuint instSelection) {
  GLuint i;
  
  switch(instSelection) {
    case 0:  /* Guitar */
      instrument_P1.guitar = true;
      instrument_P1.bass = false;
      instrument_P1.drums = false;
      instrument_P1.vocals = false;
      for ( i = 0; i < 4; i++ ) { /* Highlight */
        text_Vocals_hl[i] = 1.0f; /* From down arrow */
        text_Bass_hl[i] = 1.0f; /* From up arrow */
        text_Guitar_hl[i] = colour_yellow_F0FF07[i];
      }
#ifdef __DEBUG__
      fprintf(stdout, "Selected Guitar gameplay.\n");
#endif
      break;

    case 1: /* Bass */
      instrument_P1.guitar = false;
      instrument_P1.bass = true;
      instrument_P1.drums = false;
      instrument_P1.vocals = false;
      for ( i = 0; i < 4; i++ ) {
        text_Guitar_hl[i] = 1.0f;
        text_Drums_hl[i] = 1.0f;
        text_Bass_hl[i] = colour_yellow_F0FF07[i];
      }
#ifdef __DEBUG__
      fprintf(stdout, "Selected Bass gameplay.\n");
#endif
      break;

    case 2: /* Drums */
      instrument_P1.guitar = false;
      instrument_P1.bass = false;
      instrument_P1.drums = true;
      instrument_P1.vocals = false;
      for ( i = 0; i < 4; i++ ) {
        text_Bass_hl[i] = 1.0f;
        text_Vocals_hl[i] = 1.0f;
        text_Drums_hl[i] = colour_yellow_F0FF07[i];
      }
#ifdef __DEBUG__
      fprintf(stdout, "Selected Drums gameplay.\n");
#endif
      break;

    case 3: /* Vocals */
      instrument_P1.guitar = false;
      instrument_P1.bass = false;
      instrument_P1.drums = false;
      instrument_P1.vocals = true;
      for ( i = 0; i < 4; i++ ) {
        text_Drums_hl[i] = 1.0f;
        text_Guitar_hl[i] = 1.0f;
        text_Vocals_hl[i] = colour_yellow_F0FF07[i];
      }
#ifdef __DEBUG__
      fprintf(stdout, "Selected Vocals gameplay.\n");
#endif
      break;
    
      default:
        break;

  }

  return;
}

bool screenInstruments_buffer() {
  GLfloat width;
  GLuint i;
  TTF_Font *bitstream;
  
  if (fb_nPlayers == 1) {
    /* Generate Y coordinates for text */
    for ( i = 0; i < 4; i++ ) text_BassY[i] = text_GuitarY[i] + 0.2;
    for ( i = 0; i < 4; i++ ) text_DrumsY[i] = text_BassY[i] + 0.2;
    for ( i = 0; i < 4; i++ ) text_VocalsY[i] = text_DrumsY[i] + 0.2;
  
    /* Set guitar to be highlighted by default */
    for ( i = 0; i < 4; i++ ) {
      text_Guitar_hl[i] = colour_yellow_F0FF07[i];
      text_Bass_hl[i] = 1.0f;
      text_Drums_hl[i] = 1.0f;
      text_Vocals_hl[i] = 1.0f;
    }
    
    if ((bg = graphics_loadTexture(bgTexture, 0)) == -1)
      fprintf(stderr, "Unable to load texture: %s.\n", bgTexture);
    
    if ((bitstream = TTF_OpenFont(path_bold_bitstreamVeraSans, DEFAULT_TEXT_PT))) {
      text_guitar = text_load(en_guitar, bitstream, white, 0);
      /* GLint text_scaleWidth(const char text[], TTF_Font *font, GLuint ptsize, GLfloat textureHeight); */
      width = text_scaleWidth(en_guitar, bitstream, DEFAULT_TEXT_PT, MENUITEMSHT);
      for ( i = 0; i < 2; i++ ) text_GuitarX[i] = graphics_centreAtX(0.6f, width);
      for ( i = 2; i < 4; i++ ) text_GuitarX[i] = text_GuitarX[i-2] + width;

      text_bass = text_load(en_bass, bitstream, white, 1);
      width = text_scaleWidth(en_bass, bitstream, DEFAULT_TEXT_PT, MENUITEMSHT);
      for ( i = 0; i < 2; i++ ) text_BassX[i] = graphics_centreAtX(0.6f, width);
      for ( i = 2; i < 4; i++ ) text_BassX[i] = text_BassX[i-2] + width;

      text_drums = text_load(en_drums, bitstream, white, 2);
      width = text_scaleWidth(en_drums, bitstream, DEFAULT_TEXT_PT, MENUITEMSHT);
      for ( i = 0; i < 2; i++ ) text_DrumsX[i] = graphics_centreAtX(0.6f, width);
      for ( i = 2; i < 4; i++ ) text_DrumsX[i] = text_DrumsX[i-2] + width;

      text_vocals = text_load(en_vocals, bitstream, white, 3);
      width = text_scaleWidth(en_vocals, bitstream, DEFAULT_TEXT_PT, MENUITEMSHT);
      for ( i = 0; i < 2; i++ ) text_VocalsX[i] = graphics_centreAtX(0.6f, width);
      for ( i = 2; i < 4; i++ ) text_VocalsX[i] = text_VocalsX[i-2] + width;
    }
    else {
      fprintf(stderr, "instruments.c: screenInstrumentsBuffer(): Could not open font %s: %s\n", path_bold_bitstreamVeraSans, TTF_GetError());
      return false;
    }
    if (bitstream)
      TTF_CloseFont(bitstream);

    TTF_Font *crillee;
    if ((crillee = TTF_OpenFont(path_italic_crillee, DEFAULT_TEXT_PT))) {
      text_selectInstrument = text_load(en_select_instrument, crillee, white, 4);
      width = text_scaleWidth(en_select_instrument, crillee, DEFAULT_TEXT_PT, MENUITEMSHT);
      for ( i = 0; i < 2; i++ ) text_SelectInstrumentX[i] = graphics_centreAtX(0.0f, width);
      for ( i = 2; i < 4; i++ ) text_SelectInstrumentX[i] = text_SelectInstrumentX[i-2] + width;
    }
    else {
      fprintf(stderr, "instruments.c: screenInstrumentsBuffer(): Could not open font %s: %s\n", path_italic_crillee, TTF_GetError());
      return false;
    }
    if (crillee)
      TTF_CloseFont(crillee);
  }
  else
    fprintf(stdout, "Multiplayer not implemented yet.\n");
  
  return true;
}

GLvoid screenInstruments() {
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, bg );
  graphics_positionTexture(fillBGVertexX, fillBGVertexY, defVertexZ);

/*  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, texture[1] );
  graphics_positionTexture(instCanvasX, instCanvasY, defVertexZ);*/
  
/*  glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
  glBindTexture( GL_TEXTURE_2D, texture[2] );
  graphics_positionTexture(selectedGradientX, selectedGradientY, defVertexZ);*/

  /* Text elements */
  glPushMatrix(); {
    glTranslatef(0.0f, -0.35f, 0.0f);
    glColor4f(text_Guitar_hl[0], text_Guitar_hl[1], text_Guitar_hl[2], text_Guitar_hl[3]);
    glBindTexture( GL_TEXTURE_2D, text_guitar );
    graphics_positionTexture(text_GuitarX, text_GuitarY, defVertexZ);

    glColor4f(text_Bass_hl[0], text_Bass_hl[1], text_Bass_hl[2], text_Bass_hl[3]);
    glBindTexture( GL_TEXTURE_2D, text_bass );
    graphics_positionTexture(text_BassX, text_BassY, defVertexZ);

    glColor4f(text_Drums_hl[0], text_Drums_hl[1], text_Drums_hl[2], text_Drums_hl[3]);
    glBindTexture( GL_TEXTURE_2D, text_drums );
    graphics_positionTexture(text_DrumsX, text_DrumsY, defVertexZ);

    glColor4f(text_Vocals_hl[0], text_Vocals_hl[1], text_Vocals_hl[2], text_Vocals_hl[3]);
    glBindTexture( GL_TEXTURE_2D, text_vocals );
    graphics_positionTexture(text_VocalsX, text_VocalsY, defVertexZ);
  } glPopMatrix();

  glPushMatrix(); {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, SCREENHEADTEXTOFFSET, 0.0f);
    glBindTexture( GL_TEXTURE_2D, text[4] ); /* Top screen title */
    graphics_positionTexture(text_SelectInstrumentX, text_SelectInstrumentY, defVertexZ);
  } glPopMatrix();


  switch (screenInstruments_nSelection) {
    case 0:
      glTranslatef(-0.15f, -0.05f, 2.0f);
      glRotatef( 110.0f, -0.05f, 0.0f, 0.0f );
      glRotatef( degree, 0.0f, 0.0f, 0.05f );
      glPushMatrix();
      glBindTexture( GL_TEXTURE_2D, texture[0] );
      glColor4f(-1.0f, 1.0f, 1.0f, 1.0f);
      gluCylinder( quadratic, 0.05f, 0.05f, 0.1f, 32, 32 );
      glPopMatrix();
      break;
      
    case 1:
      glTranslatef(-0.15f, -0.05f, 2.0f);
      glRotatef( 110.0f, -0.05f, 0.0f, 0.0f );
      glRotatef( degree, 0.0f, 0.0f, 0.05f );
      glPushMatrix();
      glBindTexture( GL_TEXTURE_2D, texture[0] );
      glColor4f(1.0f, -1.0f, 1.0f, 1.0f);
      gluCylinder( quadratic, 0.05f, 0.0f, 0.1f, 32, 32 );
      glPopMatrix();
      break;
      
    case 2:
      glTranslatef(-0.15f, 0.0f, 2.0f);
      glRotatef( 180.0f, 0.05f, 0.0f, 0.0f );
      glRotatef( degree, 0.0f, -0.05f, 0.0f );
      glPushMatrix();
      glBindTexture( GL_TEXTURE_2D, texture[0] );
      glColor4f(1.0f, 1.0f, -1.0f, 1.0f);
      glutSolidTeapot(0.05f);
      glPopMatrix();
      break;
      
    case 3:
      glTranslatef(-0.15f, 0.0f, 2.0f);
      glRotatef( 180.0f, 0.05f, 0.0f, 0.0f );
      glRotatef( degree, 0.0f, -0.05f, 0.0f );
      glPushMatrix();
      glBindTexture( GL_TEXTURE_2D, texture[0] );
      glColor4f(-1.0f, 1.0f, -1.0f, 1.0f);
      glutWireTeapot(0.05f);
      glPopMatrix();
      break;
      
    default:
      break;
  }

  if (degree == 360.0f)
    degree = 0.0f;
  else
    degree += 0.5f;
}
