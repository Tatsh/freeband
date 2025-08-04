#include "pause.h"
#include "freeband.h"
#include "game.h"
#include "graphics/graphics.h"
#include "graphics/text.h"
#include "input/input.h"
#include "io/languages.h"
#include "io/prefs.h"
#include "main.h"

bool gamePaused;

pause_fMenuState_s pause_menuState;

/* Pause header */
GLcoordsX text_pausedX[4];
GLcoordsY text_pausedY[] = {0.0f, SCREENHEADTEXTHT, SCREENHEADTEXTHT, 0.0f};

GLcoordsX text_resumeX[4];
GLcoordsY text_resumeY[] = {0.0f, PAUSE_MENU_ITEMS_HT, PAUSE_MENU_ITEMS_HT, 0.0f};

GLcoordsX text_restartX[4];
GLcoordsY text_restartY[] = {0.0f, PAUSE_MENU_ITEMS_HT, PAUSE_MENU_ITEMS_HT, 0.0f};

GLcoordsX text_changeDifficultyX[4];
GLcoordsY text_changeDifficultyY[] = {0.0f, PAUSE_MENU_ITEMS_HT, PAUSE_MENU_ITEMS_HT, 0.0f};

GLcoordsX text_adjustMicVolumeX[4];
GLcoordsY text_adjustMicVolumeY[] = {0.0f, PAUSE_MENU_ITEMS_HT, PAUSE_MENU_ITEMS_HT, 0.0f};

GLcoordsX text_leftyModeX[4];
GLcoordsY text_leftyModeY[] = {0.0f, PAUSE_MENU_ITEMS_HT, PAUSE_MENU_ITEMS_HT, 0.0f};

GLcoordsX text_quitX[4];
GLcoordsY text_quitY[] = {0.0f, PAUSE_MENU_ITEMS_HT, PAUSE_MENU_ITEMS_HT, 0.0f};

text_i text_paused, text_resume, text_restart, text_changeDifficulty, text_adjustMicVolume,
  text_leftyMode, text_quit;

bool screenPause_buffer() {
  ushort i;
  GLfloat width;
  TTF_Font *crillee, *freeSans;

  pause_menuState.resume = true;

  if ((crillee = TTF_OpenFont(path_italic_crillee, DEFAULT_TEXT_PT))) {
    text_paused = text_load(languageStrings_screenPause.header, crillee, white);
    width = text_scaleWidth(languageStrings_screenPause.header, crillee, SCREENHEADTEXTHT);
    for (i = 0; i < 2; i++)
      text_pausedX[i] = graphics_centreAtX(0.0f, width);
    for (i = 2; i < 4; i++)
      text_pausedX[i] = text_pausedX[i - 2] + width;
  }
  if (crillee)
    TTF_CloseFont(crillee);

  if ((freeSans = TTF_OpenFont(path_bold_freeSans, DEFAULT_TEXT_PT))) {
    text_resume = text_load(languageStrings_screenPause.resume, freeSans, white);
    width = text_scaleWidth(languageStrings_screenPause.resume, freeSans, PAUSE_MENU_ITEMS_HT);
    for (i = 0; i < 2; i++)
      text_resumeX[i] = graphics_centreAtX(0.0f, width);
    for (i = 2; i < 4; i++)
      text_resumeX[i] = text_resumeX[i - 2] + width;

    text_restart = text_load(languageStrings_screenPause.restart, freeSans, white);
    width = text_scaleWidth(languageStrings_screenPause.restart, freeSans, PAUSE_MENU_ITEMS_HT);
    for (i = 0; i < 2; i++)
      text_restartX[i] = graphics_centreAtX(0.0f, width);
    for (i = 2; i < 4; i++)
      text_restartX[i] = text_restartX[i - 2] + width;

    text_changeDifficulty =
      text_load(languageStrings_screenPause.change_difficulty, freeSans, white);
    width =
      text_scaleWidth(languageStrings_screenPause.change_difficulty, freeSans, PAUSE_MENU_ITEMS_HT);
    for (i = 0; i < 2; i++)
      text_changeDifficultyX[i] = graphics_centreAtX(0.0f, width);
    for (i = 2; i < 4; i++)
      text_changeDifficultyX[i] = text_changeDifficultyX[i - 2] + width;

    text_adjustMicVolume =
      text_load(languageStrings_screenPause.adjust_microphone_volume, freeSans, white);
    width = text_scaleWidth(
      languageStrings_screenPause.adjust_microphone_volume, freeSans, PAUSE_MENU_ITEMS_HT);
    for (i = 0; i < 2; i++)
      text_adjustMicVolumeX[i] = graphics_centreAtX(0.0f, width);
    for (i = 2; i < 4; i++)
      text_adjustMicVolumeX[i] = text_adjustMicVolumeX[i - 2] + width;

    text_leftyMode = text_load(languageStrings_screenPause.lefty_mode, freeSans, white);
    width = text_scaleWidth(languageStrings_screenPause.lefty_mode, freeSans, PAUSE_MENU_ITEMS_HT);
    for (i = 0; i < 2; i++)
      text_leftyModeX[i] = graphics_centreAtX(0.0f, width);
    for (i = 2; i < 4; i++)
      text_leftyModeX[i] = text_leftyModeX[i - 2] + width;

    text_quit = text_load(languageStrings_screenPause.quit, freeSans, white);
    width = text_scaleWidth(languageStrings_screenPause.quit, freeSans, PAUSE_MENU_ITEMS_HT);
    for (i = 0; i < 2; i++)
      text_quitX[i] = graphics_centreAtX(0.0f, width);
    for (i = 2; i < 4; i++)
      text_quitX[i] = text_quitX[i - 2] + width;
  }
  if (freeSans)
    TTF_CloseFont(freeSans);

  return true;
}

GLvoid screenPause() {
  glPushMatrix();
  {
    glTranslatef(0.0f, -0.55f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, text_paused);
    text_position(text_pausedX, text_pausedY, defVertexZ);
  }
  glPopMatrix();

  glPushMatrix();
  {
    glTranslatef(0.0f, PAUSE_MENU_ITEMS_OFFSET, 0.0f);
    if (pause_menuState.resume)
      glColor4f(buttonColour_yellow[0],
                buttonColour_yellow[1],
                buttonColour_yellow[2],
                buttonColour_yellow[3]);
    else
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, text_resume);
    text_position(text_resumeX, text_resumeY, defVertexZ);
  }
  glPopMatrix();
  glPushMatrix();
  { /* Add a drop shadow */
    glTranslatef(0.01f, PAUSE_MENU_ITEMS_OFFSET + 0.01f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.25f);
    glBindTexture(GL_TEXTURE_2D, text_resume);
    text_position(text_resumeX, text_resumeY, defVertexZ);
  }
  glPopMatrix();

  glPushMatrix();
  {
    glTranslatef(0.0f, PAUSE_MENU_ITEMS_OFFSET + PAUSE_MENU_ITEMS_DIFF, 0.0f);
    if (pause_menuState.restart)
      glColor4f(buttonColour_yellow[0],
                buttonColour_yellow[1],
                buttonColour_yellow[2],
                buttonColour_yellow[3]);
    else
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, text_restart);
    text_position(text_restartX, text_restartY, defVertexZ);
  }
  glPopMatrix();
  glPushMatrix();
  { /* Add a drop shadow */
    glTranslatef(0.01f, PAUSE_MENU_ITEMS_OFFSET + PAUSE_MENU_ITEMS_DIFF + 0.01f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.25f);
    glBindTexture(GL_TEXTURE_2D, text_restart);
    text_position(text_restartX, text_restartY, defVertexZ);
  }
  glPopMatrix();

  glPushMatrix();
  {
    glTranslatef(0.0f, PAUSE_MENU_ITEMS_OFFSET + (PAUSE_MENU_ITEMS_DIFF * 2.0f), 0.0f);
    if (pause_menuState.change_difficulty)
      glColor4f(buttonColour_yellow[0],
                buttonColour_yellow[1],
                buttonColour_yellow[2],
                buttonColour_yellow[3]);
    else
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, text_changeDifficulty);
    text_position(text_changeDifficultyX, text_changeDifficultyY, defVertexZ);
  }
  glPopMatrix();
  glPushMatrix();
  { /* Add a drop shadow */
    glTranslatef(0.01f, PAUSE_MENU_ITEMS_OFFSET + (PAUSE_MENU_ITEMS_DIFF * 2.0f) + 0.01f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.25f);
    glBindTexture(GL_TEXTURE_2D, text_changeDifficulty);
    text_position(text_changeDifficultyX, text_changeDifficultyY, defVertexZ);
  }
  glPopMatrix();

  glPushMatrix();
  {
    glTranslatef(0.0f, PAUSE_MENU_ITEMS_OFFSET + (PAUSE_MENU_ITEMS_DIFF * 3.0f), 0.0f);
    if (pause_menuState.change_mic_volume)
      glColor4f(buttonColour_yellow[0],
                buttonColour_yellow[1],
                buttonColour_yellow[2],
                buttonColour_yellow[3]);
    else
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, text_adjustMicVolume);
    text_position(text_adjustMicVolumeX, text_adjustMicVolumeY, defVertexZ);
  }
  glPopMatrix();
  glPushMatrix();
  { /* Add a drop shadow */
    glTranslatef(0.01f, PAUSE_MENU_ITEMS_OFFSET + (PAUSE_MENU_ITEMS_DIFF * 3.0f) + 0.01f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.25f);
    glBindTexture(GL_TEXTURE_2D, text_adjustMicVolume);
    text_position(text_adjustMicVolumeX, text_adjustMicVolumeY, defVertexZ);
  }
  glPopMatrix();

  glPushMatrix();
  {
    glTranslatef(0.0f, PAUSE_MENU_ITEMS_OFFSET + (PAUSE_MENU_ITEMS_DIFF * 4.0f), 0.0f);
    if (pause_menuState.lefty_mode)
      glColor4f(buttonColour_yellow[0],
                buttonColour_yellow[1],
                buttonColour_yellow[2],
                buttonColour_yellow[3]);
    else
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, text_leftyMode);
    text_position(text_leftyModeX, text_leftyModeY, defVertexZ);
  }
  glPopMatrix();
  glPushMatrix();
  { /* Add a drop shadow */
    glTranslatef(0.01f, PAUSE_MENU_ITEMS_OFFSET + (PAUSE_MENU_ITEMS_DIFF * 4.0f) + 0.01f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.25f);
    glBindTexture(GL_TEXTURE_2D, text_leftyMode);
    text_position(text_leftyModeX, text_leftyModeY, defVertexZ);
  }
  glPopMatrix();

  glPushMatrix();
  {
    glTranslatef(0.0f, PAUSE_MENU_ITEMS_OFFSET + (PAUSE_MENU_ITEMS_DIFF * 5.0f), 0.0f);
    if (pause_menuState.quit)
      glColor4f(buttonColour_yellow[0],
                buttonColour_yellow[1],
                buttonColour_yellow[2],
                buttonColour_yellow[3]);
    else
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, text_quit);
    text_position(text_quitX, text_quitY, defVertexZ);
  }
  glPopMatrix();
  glPushMatrix();
  { /* Add a drop shadow */
    glTranslatef(0.01f, PAUSE_MENU_ITEMS_OFFSET + (PAUSE_MENU_ITEMS_DIFF * 5.0f) + 0.01f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.25f);
    glBindTexture(GL_TEXTURE_2D, text_quit);
    text_position(text_quitX, text_quitY, defVertexZ);
  }
  glPopMatrix();
}
