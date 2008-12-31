#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../graphics/text.h"
#include "instruments.h"
#include "main.h"

bool nonGame;
bool online;
bool options;

char bgTexture[] = "GameData/themes/default/global/bg.png";
char logoTexture[] = "GameData/themes/default/screenStart/banner.png";
char mainSelector[] = "GameData/themes/default/screenStart/selector.png";

/* Note:
   Negative is to the left, positive is to the right when horizontal (x)
   Negative is to the top, positive is to the bottom when vertical (y)
   Negative is to the outside, positive is going inside (z)
   Order of corners: top-left, bottom-left, bottom-right, top-right */
GLfloat screenMain_logoX[] = { -1.25f, -1.25f, 1.26f, 1.26f }; /* Logo position */
GLfloat screenMain_logoY[] = {  -1.0f,   0.0f,  0.0f, -1.0f };
GLfloat screenMain_selectionAlpha = 0.3f;
GLfloat screenMain_selectionX[4]; /* Main menu selector's default position */
GLfloat screenMain_selectionY[] = {  0.18f, 0.0f, 0.0f, 0.18f };

GLfloat text_SinglePlayerX[4]; /* SINGLE PLAYER */
GLfloat text_SinglePlayerY[4];
GLfloat text_MultiplayerX[4]; /* MULTIPLAYER */
GLfloat text_OnlineX[4]; /* ONLINE */
GLfloat text_OptionsX[4]; /* OPTIONS */
GLfloat text_QuitX[4]; /* QUIT */

GLfloat text_SinglePlayer_hl[4];
GLfloat text_Multiplayer_hl[4];
GLfloat text_Online_hl[4];
GLfloat text_Options_hl[4];
GLfloat text_Quit_hl[4];

GLuint bg, logo, selectG; /* Textures; must be called selectG thanks to Gentoo defining select randomly elsewhere this links to */
GLuint single, multiplayer, onlineM, optionsM, quit; /* Menu options */
GLuint screenMain_nSelection = 0;

tMenuState screenMain_selection;

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
      fb_screen.instruments = instrument_P1.guitar = true; /* We set guitar to default selection, does not affect highlight */
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

GLvoid screenMain_buffer() {
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
  
  if ((bg = graphics_loadTexture(bgTexture, 0)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", bgTexture);

  if ((logo = graphics_loadTexture(logoTexture, 1)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", logoTexture);
  
  if ((selectG = graphics_loadTexture(mainSelector, 2)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", mainSelector);
  for ( i = 0; i < 2; i++ ) screenMain_selectionX[i] = graphics_centreAtX(0.6f, graphics_scaleTextureWidth(400, 52, 0.18f));
  for ( i = 2; i < 4; i++ ) screenMain_selectionX[i] = screenMain_selectionX[i-2] + graphics_scaleTextureWidth(400, 52, 0.18f);
  
  /* Text */
  if ((crillee = TTF_OpenFont(path_italic_crillee, DEFAULT_TEXT_PT))) {
    single = text_load("SINGLE PLAYER", crillee, white, 0); /* Always load text as white; change using glColor4f */
    width = graphics_scaleTextureWidth(545, 96, MENUITEMSHT); /* Get these values from stdout */
    for ( i = 0; i < 2; i++ ) text_SinglePlayerX[i] = graphics_centreAtX(0.6f, width);
    for ( i = 2; i < 4; i++ ) text_SinglePlayerX[i] = text_SinglePlayerX[i-2] + width;
  
    multiplayer = text_load("MULTIPLAYER", crillee, white, 1);
    for ( i = 0; i < 2; i++ ) text_MultiplayerX[i] = graphics_centreAtX(0.6f, graphics_scaleTextureWidth(489, 96, MENUITEMSHT));
    for ( i = 2; i < 4; i++ ) text_MultiplayerX[i] = text_MultiplayerX[i-2] + graphics_scaleTextureWidth(489, 96, MENUITEMSHT);
  
    onlineM = text_load("ONLINE", crillee, white, 2);
    for ( i = 0; i < 2; i++ ) text_OnlineX[i] = graphics_centreAtX(0.6f, graphics_scaleTextureWidth(266, 96, MENUITEMSHT));
    for ( i = 2; i < 4; i++ ) text_OnlineX[i] = text_OnlineX[i-2] + graphics_scaleTextureWidth(266, 96, MENUITEMSHT);
  
    optionsM = text_load("OPTIONS", crillee, white, 3);
    for ( i = 0; i < 2; i++ ) text_OptionsX[i] = graphics_centreAtX(0.6f, graphics_scaleTextureWidth(311, 96, MENUITEMSHT));
    for ( i = 2; i < 4; i++ ) text_OptionsX[i] = text_OptionsX[i-2] + graphics_scaleTextureWidth(311, 96, MENUITEMSHT);
  
    quit = text_load("QUIT", crillee, white, 4);
    for ( i = 0; i < 2; i++ ) text_QuitX[i] = graphics_centreAtX(0.6f, graphics_scaleTextureWidth(168, 96, MENUITEMSHT));
    for ( i = 2; i < 4; i++ ) text_QuitX[i] = text_QuitX[i-2] + graphics_scaleTextureWidth(168, 96, MENUITEMSHT);
  }
  else
    fprintf(stderr, "Error opening font for screenMain: %s\n", TTF_GetError());

  if (crillee)
    TTF_CloseFont(crillee);

  return;
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
