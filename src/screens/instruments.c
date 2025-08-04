#include "instruments.h"
#include "freeband.h"
#include "graphics/graphics.h"
#include "graphics/text.h"
#include "io/languages.h"
#include "io/prefs.h"
#include "main.h"
#include "songs.h"

GLcoordsX text_GuitarX[4];
GLcoordsY text_GuitarY[] = {0.0f, MENUITEMSHT, MENUITEMSHT, 0.0f};
GLcoordsX text_BassX[4];
GLcoordsY text_BassY[4];
GLcoordsX text_DrumsX[4];
GLcoordsY text_DrumsY[4];
GLcoordsX text_VocalsX[4];
GLcoordsY text_VocalsY[4];

GLcoordsX
  text_SelectInstrumentX[4]; /* Crillee is italic on its own, this makes it appear not italic */
GLcoordsY text_SelectInstrumentY[] = {0.0f, SCREENHEADTEXTHT, SCREENHEADTEXTHT, 0.0f};

GLfloat degree = 0.0f;

extern texture_i bg;
texture_i text_guitar, text_bass, text_drums, text_vocals;
texture_i text_selectInstrument;

instrument_s instrument[4];

ushort current_instrument;

GLvoid screenInstruments_accept() {
  switch (current_instrument) {
    case INSTRUMENT_GUITAR:
#ifndef NDEBUG
      fprintf(stdout, "Starting %d player guitar game.\n", fb_nPlayers);
#endif
      break;

    case INSTRUMENT_BASS:
#ifndef NDEBUG
      fprintf(stdout, "Starting %d player bass game.\n", fb_nPlayers);
#endif
      break;

    case INSTRUMENT_DRUMS:
#ifndef NDEBUG
      fprintf(stdout, "Starting %d player drums game.\n", fb_nPlayers);
#endif
      break;

    case INSTRUMENT_VOCALS:
#ifndef NDEBUG
      fprintf(stdout, "Starting %d player vocals game.\n", fb_nPlayers);
#endif
      break;

    default:
      break;
  }

  menuQuit = true;
  graphics_loading = true;
  graphics_clear();
#ifndef NDEBUG
  fprintf(stdout, "Deleted all screenInstruments elements.\nLoading screenSongs elements...\n");
#endif
  fb_screen.instruments = graphics_loading = menuQuit = false;
  fb_screen.songs = true;
}

bool screenInstruments_buffer() {
  GLfloat width;
  ushort i;
  TTF_Font *freeSans, *crillee;

  if (fb_nPlayers == 1) {
    /* Generate Y coordinates for text */
    for (i = 0; i < 4; i++)
      text_BassY[i] = text_GuitarY[i] + 0.2;
    for (i = 0; i < 4; i++)
      text_DrumsY[i] = text_BassY[i] + 0.2;
    for (i = 0; i < 4; i++)
      text_VocalsY[i] = text_DrumsY[i] + 0.2;

    if ((bg = graphics_loadTexture(bgTexture, 0)) == -1)
      fprintf(stderr, "Unable to load texture: %s.\n", bgTexture);

    if ((freeSans = TTF_OpenFont(path_bold_freeSans, DEFAULT_TEXT_PT))) {
      text_guitar = text_load(languageStrings_screenInstruments.guitar, freeSans, white);
      /* GLint text_scaleWidth(const char text[], TTF_Font *font, GLuint ptsize, GLfloat textureHeight); */
      width = text_scaleWidth(languageStrings_screenInstruments.guitar, freeSans, MENUITEMSHT);
      for (i = 0; i < 2; i++)
        text_GuitarX[i] = graphics_centreAtX(0.6f, width);
      for (i = 2; i < 4; i++)
        text_GuitarX[i] = text_GuitarX[i - 2] + width;

      text_bass = text_load(languageStrings_screenInstruments.bass, freeSans, white);
      width = text_scaleWidth(languageStrings_screenInstruments.bass, freeSans, MENUITEMSHT);
      for (i = 0; i < 2; i++)
        text_BassX[i] = graphics_centreAtX(0.6f, width);
      for (i = 2; i < 4; i++)
        text_BassX[i] = text_BassX[i - 2] + width;

      text_drums = text_load(languageStrings_screenInstruments.drums, freeSans, white);
      width = text_scaleWidth(languageStrings_screenInstruments.drums, freeSans, MENUITEMSHT);
      for (i = 0; i < 2; i++)
        text_DrumsX[i] = graphics_centreAtX(0.6f, width);
      for (i = 2; i < 4; i++)
        text_DrumsX[i] = text_DrumsX[i - 2] + width;

      text_vocals = text_load(languageStrings_screenInstruments.vocals, freeSans, white);
      width = text_scaleWidth(languageStrings_screenInstruments.vocals, freeSans, MENUITEMSHT);
      for (i = 0; i < 2; i++)
        text_VocalsX[i] = graphics_centreAtX(0.6f, width);
      for (i = 2; i < 4; i++)
        text_VocalsX[i] = text_VocalsX[i - 2] + width;
    } else {
      fprintf(stderr,
              "instruments.c: screenInstrumentsBuffer(): Could not open font %s: %s\n",
              path_bold_bitstreamVeraSans,
              TTF_GetError());
      return false;
    }
    if (freeSans)
      TTF_CloseFont(freeSans);

    if ((crillee = TTF_OpenFont(path_italic_crillee, DEFAULT_TEXT_PT))) {
      text_selectInstrument = text_load(languageStrings_screenInstruments.header, crillee, white);
      width = text_scaleWidth(languageStrings_screenInstruments.header, crillee, MENUITEMSHT);
      for (i = 0; i < 2; i++)
        text_SelectInstrumentX[i] = graphics_centreAtX(0.0f, width);
      for (i = 2; i < 4; i++)
        text_SelectInstrumentX[i] = text_SelectInstrumentX[i - 2] + width;
    } else {
      fprintf(stderr,
              "instruments.c: screenInstrumentsBuffer(): Could not open font %s: %s\n",
              path_italic_crillee,
              TTF_GetError());
      return false;
    }
    if (crillee)
      TTF_CloseFont(crillee);
  } else
    fprintf(stdout, "Multiplayer not implemented yet.\n");

  if (!screenMenuFooter_buffer()) {
    fprintf(stderr, "Unable to buffer screenMenuFooter.\n");
    return false;
  }

  return true;
}

GLvoid screenInstruments() {
  glPushMatrix();
  {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, bg);
    graphics_positionTexture(fillBGVertexX, fillBGVertexY, defVertexZ);
  }
  glPopMatrix();

  /* Text elements */
  glPushMatrix();
  {
    glTranslatef(0.0f, -0.35f, 0.0f);
    if (current_instrument != INSTRUMENT_GUITAR)
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else
      glColor4f(colour_yellow_F0FF07[0],
                colour_yellow_F0FF07[1],
                colour_yellow_F0FF07[2],
                colour_yellow_F0FF07[3]);
    glBindTexture(GL_TEXTURE_2D, text_guitar);
    graphics_positionTexture(text_GuitarX, text_GuitarY, defVertexZ);

    if (current_instrument != INSTRUMENT_BASS)
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else
      glColor4f(colour_yellow_F0FF07[0],
                colour_yellow_F0FF07[1],
                colour_yellow_F0FF07[2],
                colour_yellow_F0FF07[3]);
    glBindTexture(GL_TEXTURE_2D, text_bass);
    graphics_positionTexture(text_BassX, text_BassY, defVertexZ);

    if (current_instrument != INSTRUMENT_DRUMS)
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else
      glColor4f(colour_yellow_F0FF07[0],
                colour_yellow_F0FF07[1],
                colour_yellow_F0FF07[2],
                colour_yellow_F0FF07[3]);
    glBindTexture(GL_TEXTURE_2D, text_drums);
    graphics_positionTexture(text_DrumsX, text_DrumsY, defVertexZ);

    if (current_instrument != INSTRUMENT_VOCALS)
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else
      glColor4f(colour_yellow_F0FF07[0],
                colour_yellow_F0FF07[1],
                colour_yellow_F0FF07[2],
                colour_yellow_F0FF07[3]);
    glBindTexture(GL_TEXTURE_2D, text_vocals);
    graphics_positionTexture(text_VocalsX, text_VocalsY, defVertexZ);
  }
  glPopMatrix();

  glPushMatrix();
  {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, SCREENHEADTEXTOFFSET, 0.0f);
    glBindTexture(GL_TEXTURE_2D, text_selectInstrument); /* Top screen title */
    graphics_positionTexture(text_SelectInstrumentX, text_SelectInstrumentY, defVertexZ);
  }
  glPopMatrix();

  glPushMatrix();
  {
    switch (current_instrument) {
      case INSTRUMENT_GUITAR:
        glTranslatef(-0.15f, -0.05f, 2.0f);
        glRotatef(110.0f, -0.05f, 0.0f, 0.0f);
        glRotatef(degree, 0.0f, 0.0f, 0.05f);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, bg);
        glColor4f(-1.0f, 1.0f, 1.0f, 1.0f);
        gluCylinder(quadratic, 0.05f, 0.05f, 0.1f, 32, 32);
        glPopMatrix();
        break;

      case INSTRUMENT_BASS:
        glTranslatef(-0.15f, -0.05f, 2.0f);
        glRotatef(110.0f, -0.05f, 0.0f, 0.0f);
        glRotatef(degree, 0.0f, 0.0f, 0.05f);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, bg);
        glColor4f(1.0f, -1.0f, 1.0f, 1.0f);
        gluCylinder(quadratic, 0.05f, 0.0f, 0.1f, 32, 32);
        glPopMatrix();
        break;

      case INSTRUMENT_DRUMS:
        glTranslatef(-0.15f, 0.0f, 2.0f);
        glRotatef(180.0f, 0.05f, 0.0f, 0.0f);
        glRotatef(degree, 0.0f, -0.05f, 0.0f);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, bg);
        glColor4f(1.0f, 1.0f, -1.0f, 1.0f);
        glutSolidTeapot(0.05f);
        glPopMatrix();
        break;

      case INSTRUMENT_VOCALS:
        glTranslatef(-0.15f, 0.0f, 2.0f);
        glRotatef(180.0f, 0.05f, 0.0f, 0.0f);
        glRotatef(degree, 0.0f, -0.05f, 0.0f);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, bg);
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
  glPopMatrix();

  screenMenuFooter();
}
