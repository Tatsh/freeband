#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../graphics/text.h"
#include "../io/languages.h"
#include "instruments.h"
#include "main.h"

bool nonGame;
bool online;
bool options;

texture_p bgTexture[] = "GameData/themes/default/global/bg.png";
texture_p logoTexture[] = "GameData/themes/default/screenMain/banner.png";
texture_p mainSelector[] = "GameData/themes/default/screenMain/selector.png";

/* Note:
   Negative is to the left, positive is to the right when horizontal (x)
   Negative is to the top, positive is to the bottom when vertical (y)
   Negative is to the outside, positive is going inside (z)
   Order of corners: top-left, bottom-left, bottom-right, top-right */
GLcoordsX screenMain_logoX[] = { -1.25f, -1.25f, 1.26f, 1.26f }; /* Logo position */
GLcoordsY screenMain_logoY[] = {  -1.0f,   0.0f,  0.0f, -1.0f };
GLalpha screenMain_selectionAlpha = 0.3f;
GLcoordsX screenMain_selectionX[4]; /* Main menu selector's default position */
GLcoordsY screenMain_selectionY[] = {  0.18f, 0.0f, 0.0f, 0.18f };

GLcoordsX text_SinglePlayerX[4]; /* SINGLE PLAYER */
GLcoordsY text_SinglePlayerY[4];
GLcoordsX text_MultiplayerX[4]; /* MULTIPLAYER */
GLcoordsX text_OnlineX[4]; /* ONLINE */
GLcoordsX text_OptionsX[4]; /* OPTIONS */
GLcoordsX text_QuitX[4]; /* QUIT */

GLcoordsY text_SinglePlayer_hl[4];
GLcoordsY text_Multiplayer_hl[4];
GLcoordsY text_Online_hl[4];
GLcoordsY text_Options_hl[4];
GLcoordsY text_Quit_hl[4];

texture_i bg, logo, selectG; /* Textures; must be called selectG thanks to Gentoo defining select randomly elsewhere this links to */
text_i single, multiplayer, onlineM, optionsM, quit; /* Menu options */

/* screenMenuBottom */
text_i select_G, back_R, upDown_strum;
GLcoordsX text_select_GX[4];
GLcoordsY text_select_GY[] =  { 0.0f, BOTTOM_TEXT_HT, BOTTOM_TEXT_HT, 0.0f };
GLcoordsX text_back_RX[4];
GLcoordsY text_back_RY[4];
GLcoordsX text_upDown_strumX[4];
GLcoordsY text_upDown_strumY[4];

texture_i button_green, button_red, strummer, button_bg;
texture_p button_green_p[] = "GameData/themes/default/global/button_green.png";
texture_p button_red_p[] = "GameData/themes/default/global/button_red.png";
texture_p strummer_p[] = "GameData/themes/default/global/strummer.png";
texture_p button_bg_p[] = "GameData/themes/default/global/screenbottom_bg.png";

#define FOOTERBG_HT 0.145f

GLcoordsX button_green_X[4];
GLcoordsY button_green_Y[] = { 0.0f, BOTTOM_TEXT_HT, BOTTOM_TEXT_HT, 0.0f };
GLcoordsX button_red_X[4];
GLcoordsY button_red_Y[4];
GLcoordsX strummer_X[4];
GLcoordsY strummer_Y[4] = { 0.0f, 0.035f, 0.035f, 0.0f };
GLcoordsX button_bg_X[4];
GLcoordsY button_bg_Y[] = { 0.0f, FOOTERBG_HT, FOOTERBG_HT, 0.0f };
GLcoordsX button_bg_X_upDown[4];
/* End screenMenuBottom */

GLuint screenMain_nSelection = 0;

mainMenu_s screenMain_selection;

GLvoid screenMain_accept() {
  switch (screenMain_nSelection) {
    case 0:
#ifdef __DEBUG__
      fprintf(stdout, "Starting single player mode.\n");
#endif
      fb_nPlayers = 1;
      menuQuit = true; /* We are leaving the menu */
      graphics_loading = true; /* We are currently loading textures */
      graphics_clear(); /* Clean up screen */
#ifdef __DEBUG__
      fprintf(stdout, "Deleted all screen mainMenu elements.\nLoading single player screenInstruments elements...\n");
#endif
      fb_screen.mainMenu = graphics_loading = menuQuit = false;
      nonGame = false; /* We are not going to online mode, options menu, or going to quit */
      fb_screen.instruments = instrument[0].guitar = true; /* We set guitar to default selection, does not affect highlight */
      break;

    case 1:
#ifdef __DEBUG__
      fprintf(stdout, "Starting multiplayer mode.\n");
#endif
      nonGame = true; /* Until multiplayer is implemented */
      break;

    case 2:
      fprintf(stdout, "Starting online mode.\n");
      nonGame = true;
      online = true;
      break;

    case 3:
      fprintf(stdout, "Going to options menu.\n");
      nonGame = true;
      options = true;
      break;

    case 4:
      fb_quit(0);
      break;

    default:
      break;
  }

  return;
}

GLvoid screenMain_highlighted(GLuint selectID) {
  GLuint i;

  switch(selectID) {
    case 0: /* Single player */
      screenMain_selection.quit = false;
      screenMain_selection.single = true;
      screenMain_selection.multiplayer = false;
      for ( i = 0; i < 4; i++ ) { /* Highlight */
        text_Quit_hl[i] = colour_blue_7CA4F6[i]; /* From down arrow */
        text_Multiplayer_hl[i] = colour_blue_7CA4F6[i]; /* From up arrow */
        text_SinglePlayer_hl[i] = 1.0f;
    }
#ifdef __DEBUG__
    fprintf(stdout, "Selected single player mode.\n");
#endif
    break;

    case 1:  /* Multiplayer */
      screenMain_selection.single = false;
      screenMain_selection.multiplayer = true;
      screenMain_selection.online = false;
      for ( i = 0; i < 4; i++ ) {
        text_SinglePlayer_hl[i] = colour_blue_7CA4F6[i];
        text_Online_hl[i] = colour_blue_7CA4F6[i];
        text_Multiplayer_hl[i] = 1.0f;
      }
#ifdef __DEBUG__
      fprintf(stdout, "Selected multiplayer player mode.\n");
#endif
      break;

    case 2: /* Online */
      screenMain_selection.multiplayer = false;
      screenMain_selection.online = true;
      screenMain_selection.options = false;
      for ( i = 0; i < 4; i++ ) {
        text_Multiplayer_hl[i] = colour_blue_7CA4F6[i];
        text_Options_hl[i] = colour_blue_7CA4F6[i];
        text_Online_hl[i] = 1.0f;
      }
#ifdef __DEBUG__
      fprintf(stdout, "Selected online mode.\n");
#endif
      break;

    case 3: /* Options */
      screenMain_selection.online = false;
      screenMain_selection.options = true;
      screenMain_selection.quit = false;
      for ( i = 0; i < 4; i++ ) {
        text_Online_hl[i] = colour_blue_7CA4F6[i];
        text_Quit_hl[i] = colour_blue_7CA4F6[i];
        text_Options_hl[i] = 1.0f;
      }
#ifdef __DEBUG__
      fprintf(stdout, "Selected options menu.\n");
#endif
      break;

    case 4: /* Quit */
      screenMain_selection.options = false;
      screenMain_selection.quit = true;
      screenMain_selection.single = false;
      for ( i = 0; i < 4; i++ ) {
        text_Options_hl[i] = colour_blue_7CA4F6[i];
        text_SinglePlayer_hl[i] = colour_blue_7CA4F6[i];
        text_Quit_hl[i] = 1.0f;
      }
#ifdef __DEBUG__
      fprintf(stdout, "Selected to quit.\n");
#endif
      break;

      default:
        break;
  }

  return;
}

bool screenMenuFooter_buffer() {
  ushort i;
  GLfloat width;
  TTF_Font *freeSans;
  
  if ((button_bg = graphics_loadTexture(button_bg_p, 0)) == -1)
    fprintf(stderr, "Error loading %s texture.\n", button_bg_p);
  for ( i = 0; i < 2; i++ ) button_bg_X[i] = graphics_centreAtX(0.0f,
        graphics_scaleTextureWidth(graphics_getTextureWidth(button_bg_p), graphics_getTextureHeight(button_bg_p), FOOTERBG_HT));
  for ( i = 2; i < 4; i++ ) button_bg_X[i] = button_bg_X[i-2] +
        graphics_scaleTextureWidth(graphics_getTextureWidth(button_bg_p), graphics_getTextureHeight(button_bg_p), FOOTERBG_HT);
  for ( i = 0; i < 2; i++ ) button_bg_X_upDown[i] = graphics_centreAtX(0.0f,
        graphics_scaleTextureWidth(graphics_getTextureWidth(button_bg_p), graphics_getTextureHeight(button_bg_p), FOOTERBG_HT + 0.03));
  for ( i = 2; i < 4; i++ ) button_bg_X_upDown[i] = button_bg_X_upDown[i-2] +
        graphics_scaleTextureWidth(graphics_getTextureWidth(button_bg_p), graphics_getTextureHeight(button_bg_p), FOOTERBG_HT + 0.03);
  
  if ((button_green = graphics_loadTexture(button_green_p, 0)) == -1)
    fprintf(stderr, "Error loading %s texture.\n", button_green_p);
  for ( i = 0; i < 2; i++ ) button_green_X[i] = graphics_centreAtX(0.0f,
        graphics_scaleTextureWidth(graphics_getTextureWidth(button_green_p), graphics_getTextureHeight(button_green_p), BOTTOM_TEXT_HT));
  for ( i = 2; i < 4; i++ ) button_green_X[i] = button_green_X[i-2] +
        graphics_scaleTextureWidth(graphics_getTextureWidth(button_green_p), graphics_getTextureHeight(button_green_p), BOTTOM_TEXT_HT);
  
  if ((button_red = graphics_loadTexture(button_red_p, 1)) == -1)
    fprintf(stderr, "Error loading %s texture.\n", button_red_p);
  for ( i = 0; i < 2; i++ ) button_red_X[i] = graphics_centreAtX(0.0f,
        graphics_scaleTextureWidth(graphics_getTextureWidth(button_red_p), graphics_getTextureHeight(button_red_p), BOTTOM_TEXT_HT));
  for ( i = 2; i < 4; i++ ) button_red_X[i] = button_red_X[i-2] +
        graphics_scaleTextureWidth(graphics_getTextureWidth(button_red_p), graphics_getTextureHeight(button_red_p), BOTTOM_TEXT_HT);
  for ( i = 0; i < 4; i++ ) button_red_Y[i] = button_green_Y[i];
  
  if ((strummer = graphics_loadTexture(strummer_p, 2)) == -1)
    fprintf(stderr, "Error loading %s texture.\n", strummer_p);
  for ( i = 0; i < 2; i++ ) strummer_X[i] = graphics_centreAtX(0.0f,
        graphics_scaleTextureWidth(graphics_getTextureWidth(strummer_p), graphics_getTextureHeight(strummer_p), 0.05f));
  for ( i = 2; i < 4; i++ ) strummer_X[i] = strummer_X[i-2] +
        graphics_scaleTextureWidth(graphics_getTextureWidth(strummer_p), graphics_getTextureHeight(strummer_p), 0.05f);
  
  /* Text */
  if ((freeSans = TTF_OpenFont(path_bold_freeSans, DEFAULT_TEXT_PT))) {
    select_G = text_load(languageStrings_screenFooter.select, freeSans, white); /* Force the scale of English to fit the text */
    width = text_scaleWidth(EN_SELECT, freeSans, BOTTOM_TEXT_HT);
    for ( i = 0; i < 2; i++ ) text_select_GX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_select_GX[i] = text_select_GX[i-2] + width;
    
    back_R = text_load(languageStrings_screenFooter.back, freeSans, white);
    width = text_scaleWidth(EN_BACK, freeSans, BOTTOM_TEXT_HT);
    for ( i = 0; i < 2; i++ ) text_back_RX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_back_RX[i] = text_back_RX[i-2] + width;
    for ( i = 0; i < 4; i++ ) text_back_RY[i] = text_select_GY[i];
    
    upDown_strum = text_load(languageStrings_screenFooter.up_down, freeSans, white);
    width = text_scaleWidth(EN_UPDOWN, freeSans, BOTTOM_TEXT_HT);
    for ( i = 0; i < 2; i++ ) text_upDown_strumX[i] = graphics_centreAtX(0.0f, width);
    for ( i = 2; i < 4; i++ ) text_upDown_strumX[i] = text_back_RX[i-2] + width;
    for ( i = 0; i < 4; i++ ) text_upDown_strumY[i] = text_select_GY[i];
  }
  else {
#ifdef __WIN32__
#else
    fprintf(stderr, "Error opening %s font for screenMenuBottom: %s\n", path_bold_freeSans, TTF_GetError());
#endif
    return false;
  }
  
  if (freeSans)
    TTF_CloseFont(freeSans);
  
  return true;
}

bool screenMain_buffer() {
  GLuint i;
  GLfloat width;
  TTF_Font *crillee;

  /* Graphics */
  for ( i = 0; i < 4; i++ ) { /* Set 'SINGLE PLAYER' to be highlighted */
    text_SinglePlayer_hl[i] = 1.0f;
    text_Multiplayer_hl[i] = colour_blue_7CA4F6[i];
    text_Online_hl[i] = colour_blue_7CA4F6[i];
    text_Options_hl[i] = colour_blue_7CA4F6[i];
    text_Quit_hl[i] = colour_blue_7CA4F6[i];
  }
  
  if ((bg = graphics_loadTexture(bgTexture, 0)) == -1) {
    fprintf(stderr, "Unable to load texture: %s.\n", bgTexture);
    return false;
  }

  if ((logo = graphics_loadTexture(logoTexture, 1)) == -1) {
    fprintf(stderr, "Unable to load texture: %s.\n", logoTexture);
    return false;
  }
  
  if ((selectG = graphics_loadTexture(mainSelector, 2)) == -1) {
    fprintf(stderr, "Unable to load texture: %s.\n", mainSelector);
    return false;
  }
  for ( i = 0; i < 2; i++ ) screenMain_selectionX[i] = graphics_centreAtX(0.6f,
        graphics_scaleTextureWidth(graphics_getTextureWidth(mainSelector), graphics_getTextureHeight(mainSelector), 0.18f));
  for ( i = 2; i < 4; i++ ) screenMain_selectionX[i] = screenMain_selectionX[i-2] +
        graphics_scaleTextureWidth(graphics_getTextureWidth(mainSelector), graphics_getTextureHeight(mainSelector), 0.18f);
  
  /* Text */
  if ((crillee = TTF_OpenFont(path_italic_crillee, DEFAULT_TEXT_PT))) {
    single = text_load(languageStrings_screenMain.single_player, crillee, white); /* Always load text as white; change using glColor4f */
    width = text_scaleWidth(languageStrings_screenMain.single_player, crillee, MENUITEMSHT);
    for ( i = 0; i < 2; i++ ) text_SinglePlayerX[i] = graphics_centreAtX(0.6f, width);
    for ( i = 2; i < 4; i++ ) text_SinglePlayerX[i] = text_SinglePlayerX[i-2] + width;

    multiplayer = text_load(languageStrings_screenMain.multiplayer, crillee, white);
    width = text_scaleWidth(languageStrings_screenMain.multiplayer, crillee, MENUITEMSHT);
    for ( i = 0; i < 2; i++ ) text_MultiplayerX[i] = graphics_centreAtX(0.6f, width);
    for ( i = 2; i < 4; i++ ) text_MultiplayerX[i] = text_MultiplayerX[i-2] + width;
  
    onlineM = text_load(languageStrings_screenMain.online, crillee, white);
    width = text_scaleWidth(languageStrings_screenMain.online, crillee, MENUITEMSHT);
    for ( i = 0; i < 2; i++ ) text_OnlineX[i] = graphics_centreAtX(0.6f, width);
    for ( i = 2; i < 4; i++ ) text_OnlineX[i] = text_OnlineX[i-2] + width;
  
    optionsM = text_load(languageStrings_screenMain.options, crillee, white);
    width = text_scaleWidth(languageStrings_screenMain.options, crillee, MENUITEMSHT);
    for ( i = 0; i < 2; i++ ) text_OptionsX[i] = graphics_centreAtX(0.6f, width);
    for ( i = 2; i < 4; i++ ) text_OptionsX[i] = text_OptionsX[i-2] + width;
  
    quit = text_load(languageStrings_screenMain.quit, crillee, white);
    width = text_scaleWidth(languageStrings_screenMain.quit, crillee, MENUITEMSHT);
    for ( i = 0; i < 2; i++ ) text_QuitX[i] = graphics_centreAtX(0.6f, width);
    for ( i = 2; i < 4; i++ ) text_QuitX[i] = text_QuitX[i-2] + width;
  }
  else {
#ifdef __WIN32__
#else
    fprintf(stderr, "Error opening %s font for screenMain: %s\n", path_italic_crillee, TTF_GetError());
#endif
    return false;
  }

  if (crillee)
    TTF_CloseFont(crillee);

  return true;
}

GLvoid screenMain() {
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, bg );
  graphics_positionTexture(fillBGVertexX, fillBGVertexY, defVertexZ);

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBindTexture( GL_TEXTURE_2D, logo );
  graphics_positionTexture(screenMain_logoX, screenMain_logoY, defVertexZ);

  glColor4f(1.0, 1.0f, 1.0f, screenMain_selectionAlpha);
  glBindTexture( GL_TEXTURE_2D, selectG ); /* Use selector's default position */
  graphics_positionTexture(screenMain_selectionX, screenMain_selectionY, defVertexZ);
  
  /* Text positions */
  glPushMatrix(); {
    glTranslatef(0.0f, -0.017f, 0.0f);
  
    glColor4f(text_SinglePlayer_hl[0], text_SinglePlayer_hl[1], text_SinglePlayer_hl[2], text_SinglePlayer_hl[3]);
    glBindTexture( GL_TEXTURE_2D, single );
    graphics_positionTexture(text_SinglePlayerX, text_SinglePlayerY, defVertexZ);
    
    glColor4f(text_Multiplayer_hl[0], text_Multiplayer_hl[1], text_Multiplayer_hl[2], text_Multiplayer_hl[3]);
    glBindTexture( GL_TEXTURE_2D, multiplayer );
    graphics_positionTexture(text_MultiplayerX, text_MultiplayerY, defVertexZ);

    glColor4f(text_Online_hl[0], text_Online_hl[1], text_Online_hl[2], text_Online_hl[3]); 
    glBindTexture( GL_TEXTURE_2D, onlineM );
    graphics_positionTexture(text_OnlineX, text_OnlineY, defVertexZ);

    glColor4f(text_Options_hl[0], text_Options_hl[1], text_Options_hl[2], text_Options_hl[3]);
    glBindTexture( GL_TEXTURE_2D, optionsM );
    graphics_positionTexture(text_OptionsX, text_OptionsY, defVertexZ);
  
    glColor4f(text_Quit_hl[0], text_Quit_hl[1], text_Quit_hl[2], text_Quit_hl[3]);
    glBindTexture( GL_TEXTURE_2D, quit );
    graphics_positionTexture(text_QuitX, text_QuitY, defVertexZ);
  }
  glPopMatrix();

  return;
}

GLvoid screenMenuFooter() {
  if (fb_screen.songs);
  else {
    glPushMatrix(); {
      glTranslatef(-0.8f, 0.85f, 0.0f);
      glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
      glBindTexture( GL_TEXTURE_2D, button_bg );
      graphics_positionTexture(button_bg_X, button_bg_Y, defVertexZ);
      glTranslatef(-0.18f, 0.025f, 0.0f);
      glBindTexture( GL_TEXTURE_2D, button_green );
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      graphics_positionTexture(button_green_X, button_green_Y, defVertexZ);
      glTranslatef(0.25f, 0.0f, 0.0f);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBindTexture( GL_TEXTURE_2D, select_G );
      graphics_positionTexture(text_select_GX, text_select_GY, defVertexZ);
    
      glTranslatef(0.6f, -0.025f, 0.0f);
      glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
      glBindTexture( GL_TEXTURE_2D, button_bg );
      graphics_positionTexture(button_bg_X, button_bg_Y, defVertexZ);
      glTranslatef(-0.12f, 0.025f, 0.0f);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBindTexture( GL_TEXTURE_2D, button_red );
      graphics_positionTexture(button_red_X, button_red_Y, defVertexZ);
      glTranslatef(0.2f, 0.0f, 0.0f);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBindTexture( GL_TEXTURE_2D, back_R );
      graphics_positionTexture(text_back_RX, text_back_RY, defVertexZ);
    
      glTranslatef(0.6f, -0.025f, 0.0f);
      glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
      glBindTexture( GL_TEXTURE_2D, button_bg );
      graphics_positionTexture(button_bg_X_upDown, button_bg_Y, defVertexZ);
      glTranslatef(-0.23f, 0.05f, 0.0f);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBindTexture( GL_TEXTURE_2D, strummer );
      graphics_positionTexture(strummer_X, strummer_Y, defVertexZ);
      glTranslatef(0.28f, -0.03f, 0.0f);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBindTexture( GL_TEXTURE_2D, upDown_strum );
      graphics_positionTexture(text_upDown_strumX, text_upDown_strumY, defVertexZ);
    } glPopMatrix();
  }
  
  return;
}
