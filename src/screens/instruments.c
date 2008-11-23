#include "../freeband.h"
#include "../graphics/graphics.h"
#include "instruments.h"
#include "main.h"

char instCanvas[] = "GameData/themes/default/screenInstruments/canvas.png";
char selectedGradient[] = "GameData/themes/default/screenInstruments/selectedgrad.png";

/* Negative is to the left, positive is to the right when horizontal (x)
   Negative is to the top, positive is to the bottom when vertical (y)
   Negative is to the outside, positive is going inside (z)
   Order of corners: top-left, bottom-left, bottom-right, top-right */
GLfloat instCanvasX[] = { 0.1f, 0.1f, 1.2f, 1.2f };
GLfloat instCanvasY[] = { -0.4f, 0.6f, 0.6f, -0.4 };
GLfloat selectedGradientX[] = { 0.12f, 0.12f, 1.18f, 1.18f }; /* This places it underneath 'GUITAR' */
GLfloat selectedGradientY[] = { -0.35f, -0.15f, -0.15f, -0.35f };
GLfloat selectedGradientY_reset[] = { -0.35f, -0.15f, -0.15f, -0.35f };

GLfloat text_GuitarX[] = { 0.3f, 0.3f, 1.0f, 1.0f }; /* Guitar selector's default position */
GLfloat text_GuitarY[] = { -0.35f, -0.15f, -0.15f, -0.35f }; /* Use this as basis to calculate the other Y coordinates */
GLfloat text_BassX[] = { 0.4f, 0.4f, 0.9f, 0.9f };
GLfloat text_BassY[4];
GLfloat text_DrumsX[] = { 0.35f, 0.35f, 0.97f, 0.97f };
GLfloat text_DrumsY[4];
GLfloat text_VocalsX[] = { 0.29f, 0.29f, 1.03f, 1.03f };
GLfloat text_VocalsY[4];

GLfloat text_Guitar_hl[4];
GLfloat text_Bass_hl[4];
GLfloat text_Drums_hl[4];
GLfloat text_Vocals_hl[4];

GLfloat text_SelectInstrumentX[] = { -0.9f, -0.85f, 0.85f, 0.8f }; /* Crillee is italic on its own, this makes it appear not italic */
GLfloat text_SelectInstrumentY[] = { -1.1f, -0.7f, -0.7f, -1.1f };

GLfloat degree = 0.0f;

GLuint instSelection = 0; /* Guitar */

tInstrument instrument;

GLvoid setInstrument(GLuint instSelection) {
  GLuint i;
  
  switch(instSelection) {
    case 0:  /* Guitar */
      instrument.guitar = true;
      instrument.bass = false;
      instrument.drums = false;
      instrument.vocals = false;
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
      instrument.guitar = false;
      instrument.bass = true;
      instrument.drums = false;
      instrument.vocals = false;
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
      instrument.guitar = false;
      instrument.bass = false;
      instrument.drums = true;
      instrument.vocals = false;
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
      instrument.guitar = false;
      instrument.bass = false;
      instrument.drums = false;
      instrument.vocals = true;
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

GLvoid setInstrumentsImages_1P() {
  if ((texture[0] = loadTexture(bgTexture, 0)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", bgTexture);
  
  if ((texture[1] = loadTexture(instCanvas, 1)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", instCanvas);
  
  if ((texture[2] = loadTexture(selectedGradient, 2)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", selectedGradient);
  
  return;
}

GLvoid setInstrumentsText_1P() {
  TTF_Font *font, *instFont;
  font = TTF_OpenFont(defaultFont, DEFAULT_TEXT_PT); /* 72 seems to be the best size for this font */
  instFont = TTF_OpenFont(bitstreamFont, DEFAULT_TEXT_PT);
  if (!font)
    fprintf(stderr, "SDL_ttf: TTF_OpenFont() response: %s\n", TTF_GetError());
  else if (!instFont)
    fprintf(stderr, "SDL_ttf: TTF_OpenFont() response: %s\n", TTF_GetError());
  else {
    GLuint guitar, bass, drums, vocals;
    GLuint selectInstrument;
    
    guitar = loadText("GUITAR", instFont, white, 0);
    bass = loadText("BASS", instFont, white, 1);
    drums = loadText("DRUMS", instFont, white, 2);
    vocals = loadText("VOCALS", instFont, white, 3);
    
    selectInstrument = loadText("SELECT INSTRUMENT", font, white, 4);
  }
    
  if (font)
    TTF_CloseFont(font); /* Clean up */
  
  return;
}

GLvoid screenInstrumentsBuffer(GLuint nPlayers) {
  GLuint i;
  
  if (nPlayers < 2) {
    
    /* Generate Y coordinates for text */
    for ( i = 0; i < 4; i++ ) text_BassY[i] = text_GuitarY[i] + 0.23;
    for ( i = 0; i < 4; i++ ) text_DrumsY[i] = text_BassY[i] + 0.23;
    for ( i = 0; i < 4; i++ ) text_VocalsY[i] = text_DrumsY[i] + 0.23;
  
    /* Set guitar to be highlighted by default */
    for ( i = 0; i < 4; i++ ) {
      text_Guitar_hl[i] = colour_yellow_F0FF07[i];
      text_Bass_hl[i] = 1.0f;
      text_Drums_hl[i] = 1.0f;
      text_Vocals_hl[i] = 1.0f;
    }

    
    /* Set all highlight versions off screen, except for first option since that is highlighted by default */
    for ( i = 0; i < 4; i++ ) {

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
  
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, texture[0] );
  positionTexture(fillBGVertexX, fillBGVertexY, defVertexZ);

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, texture[1] );
  positionTexture(instCanvasX, instCanvasY, defVertexZ);
  
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, texture[2] );
  positionTexture(selectedGradientX, selectedGradientY, defVertexZ);

  /* Text elements */
  glColor4f(text_Guitar_hl[0], text_Guitar_hl[1], text_Guitar_hl[2], text_Guitar_hl[3]);
  glBindTexture( GL_TEXTURE_2D, text[0] );
  positionTexture(text_GuitarX, text_GuitarY, defVertexZ);

  glColor4f(text_Bass_hl[0], text_Bass_hl[1], text_Bass_hl[2], text_Bass_hl[3]);
  glBindTexture( GL_TEXTURE_2D, text[1] );
  positionTexture(text_BassX, text_BassY, defVertexZ);

  glColor4f(text_Drums_hl[0], text_Drums_hl[1], text_Drums_hl[2], text_Drums_hl[3]);
  glBindTexture( GL_TEXTURE_2D, text[2] );
  positionTexture(text_DrumsX, text_DrumsY, defVertexZ);

  glColor4f(text_Vocals_hl[0], text_Vocals_hl[1], text_Vocals_hl[2], text_Vocals_hl[3]);
  glBindTexture( GL_TEXTURE_2D, text[3] );
  positionTexture(text_VocalsX, text_VocalsY, defVertexZ);

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, text[4] ); /* Top screen title */
  positionTexture(text_SelectInstrumentX, text_SelectInstrumentY, defVertexZ);


  switch (instSelection) {
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
