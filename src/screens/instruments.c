#include "../freeband.h"
#include "../graphics/graphics.h"
#include "instruments.h"
#include "main.h"

GLfloat text_GuitarX[] = { 0.0f, 0.0f, 1.3f, 1.3f }; /* Main menu selector's default position */
GLfloat text_GuitarY[] = { -0.18f, 0.0f, 0.0f, -0.18f }; /* Use this as basis to calculate the other Y coordinates */
GLfloat text_BassX[] = { 0.0f, 0.0f, 1.3f, 1.3f };
GLfloat text_BassY[4];
GLfloat text_DrumsX[] = { 0.0f, 0.0f, 1.3f, 1.3f };
GLfloat text_DrumsY[4];
GLfloat text_VocalsX[] = { 0.0f, 0.0f, 1.3f, 1.3f };
GLfloat text_VocalsY[4];

GLfloat text_GuitarX_hl[4];
GLfloat text_GuitarY_hl[4];
GLfloat text_BassX_hl[4];
GLfloat text_BassY_hl[4];
GLfloat text_DrumsX_hl[4];
GLfloat text_DrumsY_hl[4];
GLfloat text_VocalsX_hl[4];
GLfloat text_VocalsY_hl[4];

GLuint instSelection = 0; /* Guitar */

tInstrument instrument;

GLvoid handleInstrumentsMenu() {
  
  return;
}

GLvoid setInstrumentsMenuState_1P(GLuint instSelection) {
  GLuint i;
  GLfloat tempX[4], tempY[4];
  
  if (instSelection < 1) { /* Guitar */
    instrument.guitar = true;
    instrument.bass = false;
    instrument.drums = false;
    instrument.vocals = false;
    for ( i = 0; i < 4; i++ ) { /* Highlight */
      text_VocalsX_hl[i] = offscreenVertexXY[i]; /* From down arrow */
      text_BassX_hl[i] = offscreenVertexXY[i]; /* From up arrow */
      tempX[i] = text_GuitarX[i];
      tempY[i] = text_GuitarY[i];
      text_GuitarX_hl[i] = tempX[i];
      text_GuitarY_hl[i] = tempY[i];
    }
#ifdef __DEBUG__
    fprintf(stdout, "Selected Guitar gameplay.\n");
#endif
  }
  else if (instSelection < 2) { /* Bass */
    instrument.guitar = false;
    instrument.bass = true;
    instrument.drums = false;
    instrument.vocals = false;
    for ( i = 0; i < 4; i++ ) {
      text_GuitarX_hl[i] = offscreenVertexXY[i];
      text_DrumsX_hl[i] = offscreenVertexXY[i];
      tempX[i] = text_BassX[i];
      tempY[i] = text_BassY[i];
      text_BassX_hl[i] = tempX[i];
      text_BassY_hl[i] = tempY[i];
    }
#ifdef __DEBUG__
    fprintf(stdout, "Selected Bass gameplay.\n");
#endif
  }
  else if (instSelection < 3) { /* Drums */
    instrument.guitar = false;
    instrument.bass = false;
    instrument.drums = true;
    instrument.vocals = false;
    for ( i = 0; i < 4; i++ ) {
      text_BassX_hl[i] = offscreenVertexXY[i];
      text_VocalsX_hl[i] = offscreenVertexXY[i];
      tempX[i] = text_DrumsX[i];
      tempY[i] = text_DrumsY[i];
      text_DrumsX_hl[i] = tempX[i];
      text_DrumsY_hl[i] = tempY[i];
    }
#ifdef __DEBUG__
    fprintf(stdout, "Selected Drums gameplay.\n");
#endif
  }
  else { /* Vocals */
    instrument.guitar = false;
    instrument.bass = false;
    instrument.drums = false;
    instrument.vocals = true;
    for ( i = 0; i < 4; i++ ) {
      text_DrumsX_hl[i] = offscreenVertexXY[i];
      text_GuitarX_hl[i] = offscreenVertexXY[i];
      tempX[i] = text_VocalsX[i];
      tempY[i] = text_VocalsY[i];
      text_VocalsX_hl[i] = tempX[i];
      text_VocalsY_hl[i] = tempY[i];
    }
#ifdef __DEBUG__
    fprintf(stdout, "Selected Vocals gameplay.\n");
#endif
  }

  return;
}

GLvoid setInstrumentsImages_1P() {
  
  return;
}

GLvoid setInstrumentsText_1P() {
  TTF_Font *font, *status;
  font = TTF_OpenFont(defaultFont, DEFAULT_TEXT_PT); /* 72 seems to be the best size for this font */
  status = TTF_OpenFont(statusFont, DEFAULT_TEXT_PT);
  if (!font)
    fprintf(stderr, "SDL_ttf: TTF_OpenFont() response: %s\n", TTF_GetError());
  else if (!status)
    fprintf(stderr, "SDL_ttf: TTF_OpenFont() response: %s\n", TTF_GetError());
  else {
    GLuint guitar, bass, drums, vocals;
    GLuint guitarS, bassS, drumsS, vocalsS; /* Selected versions */
    GLuint statusGuitar, statusBass, statusDrums, statusVocals;
    
    guitar = loadText("GUITAR", font, white, 0);
    bass = loadText("BASS", font, white, 1);
    drums = loadText("DRUMS", font, white, 2);
    vocals = loadText("VOCALS", font, white, 3);
    
    guitarS = loadText("GUITAR", font, yellow, 4); /* Prepare selected versions */
    bassS = loadText("BASS", font, yellow, 5);
    drumsS = loadText("DRUMS", font, yellow, 6);
    vocalsS = loadText("VOCALS", font, yellow, 7);
    
    statusGuitar = loadText("Ultimate maximum guitar fun!", status, white, 8);
    statusBass = loadText("Maximum bass fun!", status, white, 9);
    statusDrums = loadText("Drum fun!", status, white, 10);
    statusVocals = loadText("Singing fun!", status, white, 11);
  }
    
  if (font)
    TTF_CloseFont(font); /* Clean up */
  
  return;
}

GLvoid screenInstrumentsBuffer(GLuint nPlayers) {
  GLuint i;
  
  if (nPlayers < 2) {
    
    /* Generate Y coordinates for text */
    for ( i = 0; i < 4; i++ ) text_BassY[i] = text_GuitarY[i] + 0.2;
    for ( i = 0; i < 4; i++ ) text_DrumsY[i] = text_BassY[i] + 0.2;
    for ( i = 0; i < 4; i++ ) text_VocalsY[i] = text_DrumsY[i] + 0.2;
  
    /* Set guitar to be highlighted by default */
    for ( i = 0; i < 4; i++ ) {
      text_GuitarX_hl[i] = text_GuitarX[i];
      text_GuitarY_hl[i] = text_GuitarY[i];
    }
    
    /* Set all highlight versions off screen, except for first option since that is highlighted by default */
    for ( i = 0; i < 4; i++ ) {
      text_BassX_hl[i] = offscreenVertexXY[i];
      text_BassY_hl[i] = offscreenVertexXY[i];
      text_DrumsX_hl[i] = offscreenVertexXY[i];
      text_DrumsY_hl[i] = offscreenVertexXY[i];
      text_VocalsX_hl[i] = offscreenVertexXY[i];
      text_VocalsY_hl[i] = offscreenVertexXY[i];
    }

    setInstrumentsImages_1P();
    setInstrumentsText_1P();
 
  }
  else
    fprintf(stdout, "Multiplayer not implemented yet.\n");
#ifdef __DEBUG__
  fprintf(stdout, "Loading textures of screenInstruments complete.\n");
#endif
  
  return;
}

GLvoid screenInstruments(GLuint nPlayers) {
  /* Text elements */
  glBindTexture( GL_TEXTURE_2D, text[0] );
  positionTexture(text_GuitarX, text_GuitarY, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[1] );
  positionTexture(text_BassX, text_BassY, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[2] );
  positionTexture(text_DrumsX, text_DrumsY, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[3] );
  positionTexture(text_VocalsX, text_VocalsY, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[4] );
  positionTexture(text_GuitarX_hl, text_GuitarY_hl, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[5] );
  positionTexture(text_BassX_hl, text_BassY_hl, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[6] );
  positionTexture(text_DrumsX_hl, text_DrumsY_hl, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[7] );
  positionTexture(text_VocalsX_hl, text_VocalsY_hl, defVertexZ, defaultAlpha);
  
}
