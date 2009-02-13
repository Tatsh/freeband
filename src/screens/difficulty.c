#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../graphics/text.h"
#include "difficulty.h"
#include "main.h"

bool diffEasy = true; /* Read from user's last setting in preferences file later */
bool diffMedium, diffHard, diffExpert;

texture_p pSelection[] = "GameData/themes/default/screenDifficulty/selection.png";

GLcoordsX screenDifficulty_selectionX[4];
GLcoordsY screenDifficulty_selectionY[4] = { 0.0f, DIFFHT, DIFFHT, 0.0f };

GLcoordsX text_selectDifficultyX[4];
GLcoordsX text_selectDifficultyY[4] = { 0.0f, SCREENHEADTEXTHT, SCREENHEADTEXTHT, 0.0f };

GLcoordsX text_easyX[4];
GLcoordsY text_easyY[] = { 0.0f, DIFFHT, DIFFHT, 0.0f };
GLcoordsX text_mediumX[4];
GLcoordsY text_mediumY[4];
GLcoordsX text_hardX[4];
GLcoordsY text_hardY[4];
GLcoordsX text_expertX[4];
GLcoordsY text_expertY[4];

texture_i bg, selection;
text_i text_selectDifficulty, text_easy, text_medium, text_hard, text_expert;

bool screenDifficulty_buffer() {
  GLfloat width;
  ushort i;
  TTF_Font *freeSans, *crillee;
  
  if ((bg = graphics_loadTexture(bgTexture, 0)) < 0)
    fprintf(stderr, "Unable to load texture: %s.\n", bgTexture);
  
  if ((selection = graphics_loadTexture(pSelection, 1)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", pSelection);
  width = graphics_scaleTextureWidth(505, 85, 0.1);
  for ( i = 0; i < 2; i++ ) screenDifficulty_selectionX[i] = graphics_centreAtX(0.0f, width);
  for ( i = 2; i < 4; i++ ) screenDifficulty_selectionX[i] = screenDifficulty_selectionX[i-2] + width;
  
  if ((crillee = TTF_OpenFont(path_italic_crillee, DEFAULT_TEXT_PT))) {
    text_selectDifficulty = text_load(en_select_difficulty, crillee, white);
    width = text_scaleWidth(en_select_difficulty, crillee, MENUITEMSHT);
    for ( i = 0; i < 2; i++ ) text_selectDifficultyX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_selectDifficultyX[i] = text_selectDifficultyX[i-2] + width;
  }
  else {
    fprintf(stderr, "instruments.c: screenInstrumentsBuffer(): Could not open font %s: %s\n", path_italic_crillee, TTF_GetError());
    return false;
  }
  if (crillee)
    TTF_CloseFont(crillee);
  
  if ((freeSans = TTF_OpenFont(path_bold_freeSans, DEFAULT_TEXT_PT))) {
    text_easy = text_load(en_easy, freeSans, white);
    width = text_scaleWidth(en_easy, freeSans, DIFFHT);
    for ( i = 0; i < 2; i++ ) text_easyX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_easyX[i] = text_easyX[i-2] + width;
    
    text_medium = text_load(en_medium, freeSans, white);
    width = text_scaleWidth(en_medium, freeSans, DIFFHT);
    for ( i = 0; i < 2; i++ ) text_mediumX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_mediumX[i] = text_mediumX[i-2] + width;
    for ( i = 0; i < 4; i++ ) text_mediumY[i] = text_easyY[i] + DIFFHT;

    text_hard = text_load(en_hard, freeSans, white);
    width = text_scaleWidth(en_hard, freeSans, DIFFHT);
    for ( i = 0; i < 2; i++ ) text_hardX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_hardX[i] = text_hardX[i-2] + width;
    for ( i = 0; i < 4; i++ ) text_hardY[i] = text_mediumY[i] + DIFFHT;
    
    text_expert = text_load(en_expert, freeSans, white);
    width = text_scaleWidth(en_expert, freeSans, DIFFHT);
    for ( i = 0; i < 2; i++ ) text_expertX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_expertX[i] = text_expertX[i-2] + width;
    for ( i = 0; i < 4; i++ ) text_expertY[i] = text_hardY[i] + DIFFHT;
  }
  else {
    fprintf(stderr, "difficulty.c: screenDifficulty_buffer(): Could not open font %s: %s\n", path_bold_bitstreamVeraSans, TTF_GetError());
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

GLvoid screenDifficulty() {
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, bg );
  graphics_positionTexture(fillBGVertexX, fillBGVertexY, defVertexZ);
  
  glPushMatrix(); {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, SCREENHEADTEXTOFFSET, 0.0f);
    glBindTexture( GL_TEXTURE_2D, text_selectDifficulty ); /* Top screen title */
    graphics_positionTexture(text_selectDifficultyX, text_selectDifficultyY, defVertexZ);
  } glPopMatrix();
  
  if (diffEasy)
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  else
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, text_easy );
  graphics_positionTexture(text_easyX, text_easyY, defVertexZ);
  
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  if (diffMedium)
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  else
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, text_medium );
  graphics_positionTexture(text_mediumX, text_mediumY, defVertexZ);
  
  if (diffHard)
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  else
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, text_hard );
  graphics_positionTexture(text_hardX, text_hardY, defVertexZ);

  if (diffExpert)
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  else
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, text_expert );
  graphics_positionTexture(text_expertX, text_expertY, defVertexZ);
  
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, selection );
  graphics_positionTexture(screenDifficulty_selectionX, screenDifficulty_selectionY, defVertexZ);
  
  screenMenuFooter();

  return;
}
