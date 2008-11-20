#include "../freeband.h"
#include "../graphics/graphics.h"
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
GLfloat logoVertexX[] = { -1.25f, -1.25f, 1.26f, 1.26f }; /* Logo position */
GLfloat logoVertexY[] = {  -1.0f,   0.0f,  0.0f, -1.0f };
GLfloat mSelectorVertexX[] = { 0.0f, 0.0f, 1.3f, 1.3f }; /* Main menu selector's default position */
GLfloat mSelectorVertexY[] = {  0.18f, 0.0f, 0.0f, 0.18f };
GLfloat mSelectorAlpha[] = { 1.0, 1.0, 1.0, SELECTSRC_ALPHA };

/* Text positions, all are false italic. These take FOREVER!
   There is NO way to calculate these for now, all depends on mechanics of the font, specific to EVERY font */
GLfloat text_SinglePlayerX[] = { 0.09f, 0.07f, 1.22f, 1.24f }; /* SINGLE PLAYER */
GLfloat text_MultiplayerX[]  = { 0.11f, 0.09f, 1.18f, 1.2f }; /* MULTIPLAYER */
GLfloat text_OnlineX[] = { 0.36f, 0.34f, 0.94f, 0.96f }; /* ONLINE */
GLfloat text_OptionsX[] = { 0.28f, 0.26f, 0.98f, 1.0f };
GLfloat text_QuitX[] = { 0.40f, 0.38f, 0.8f, 0.82f };

GLfloat text_SinglePlayerX_hl[4];
GLfloat text_SinglePlayerY_hl[4];
GLfloat text_MultiplayerX_hl[4];
GLfloat text_MultiplayerY_hl[4];
GLfloat text_OnlineX_hl[4];
GLfloat text_OnlineY_hl[4];
GLfloat text_OptionsX_hl[4];
GLfloat text_OptionsY_hl[4];
GLfloat text_QuitX_hl[4];
GLfloat text_QuitY_hl[4];

GLuint menuSelection = 0;

tMenuState menuState;

GLvoid handleMainMenu() {
  if (menuSelection < 1) {
#ifdef __DEBUG__
    fprintf(stdout, "Starting single player mode.\n");
#endif
    nPlayers = 1;
    menuQuit = true; /* We are leaving the menu */
    loading = true; /* We are currently loading textures */

    clearScreen(); /* Clean up screen */
#ifdef __DEBUG__
    fprintf(stdout, "Deleted all screen mainMenu elements.\nLoading single player screenInstruments elements...\n");
#endif
    currentScreen.mainMenu = loading = menuQuit = false;
    nonGame = false; /* We are not going to online mode, options menu, or going to quit */
    currentScreen.instruments = instrument.guitar = true; /* We set guitar to default selection, does not affect highlight */
  }
  else if (menuSelection < 2)
    fprintf(stdout, "Starting multiplayer mode.\n");
  else if (menuSelection < 3) {
    fprintf(stdout, "Starting online mode.\n");
    nonGame = true;
    online = true;
  }
  else if (menuSelection < 4) {
    fprintf(stdout, "Going to options menu.\n");
    nonGame = true;
    options = true;
  }
  else
    quitGame(0);

  return;
}

GLvoid setMainMenuState(GLuint selectID) {
  GLuint i;
  GLfloat tempX[4], tempY[4];

  if (selectID < 1) { /* Single player */
    menuState.single = true;
    menuState.multiplayer = false;
    menuState.online = false;
    menuState.options = false;
    menuState.quit = false;
    for ( i = 0; i < 4; i++ ) { /* Highlight */
      text_QuitX_hl[i] = offscreenVertexXY[i]; /* From down arrow */
      text_MultiplayerX_hl[i] = offscreenVertexXY[i]; /* From up arrow */
      tempX[i] = text_SinglePlayerX[i];
      tempY[i] = text_SinglePlayerY[i];
      text_SinglePlayerX_hl[i] = tempX[i];
      text_SinglePlayerY_hl[i] = tempY[i];
    }
#ifdef __DEBUG__
    fprintf(stdout, "Selected single player mode.\n");
#endif
  }
  else if (selectID < 2) { /* Multiplayer */
    menuState.single = false;
    menuState.multiplayer = true;
    for ( i = 0; i < 4; i++ ) {
      text_SinglePlayerX_hl[i] = offscreenVertexXY[i];
      text_OnlineX_hl[i] = offscreenVertexXY[i];
      tempX[i] = text_MultiplayerX[i];
      tempY[i] = text_MultiplayerY[i];
      text_MultiplayerX_hl[i] = tempX[i];
      text_MultiplayerY_hl[i] = tempY[i];
    }
#ifdef __DEBUG__
    fprintf(stdout, "Selected multiplayer player mode.\n");
#endif
  }
  else if (selectID < 3) { /* Online */
    menuState.single = false;
    menuState.multiplayer = false;
    menuState.online = true;
    for ( i = 0; i < 4; i++ ) {
      text_MultiplayerX_hl[i] = offscreenVertexXY[i];
      text_OptionsX_hl[i] = offscreenVertexXY[i];
      tempX[i] = text_OnlineX[i];
      tempY[i] = text_OnlineY[i];
      text_OnlineX_hl[i] = tempX[i];
      text_OnlineY_hl[i] = tempY[i];
    }
#ifdef __DEBUG__
    fprintf(stdout, "Selected online mode.\n");
#endif
  }
  else if (selectID < 4) { /* Options */
    menuState.online = false;
    menuState.options = true;
    for ( i = 0; i < 4; i++ ) {
      text_OnlineX_hl[i] = offscreenVertexXY[i];
      text_QuitX_hl[i] = offscreenVertexXY[i];
      tempX[i] = text_OptionsX[i];
      tempY[i] = text_OptionsY[i];
      text_OptionsX_hl[i] = tempX[i];
      text_OptionsY_hl[i] = tempY[i];
    }
#ifdef __DEBUG__
    fprintf(stdout, "Selected options menu.\n");
#endif
  }
  else { /* Quit */
    menuState.options = false;
    menuState.quit = true;
    for ( i = 0; i < 4; i++ ) {
      text_OptionsX_hl[i] = offscreenVertexXY[i];
      text_SinglePlayerX_hl[i] = offscreenVertexXY[i];
      tempX[i] = text_QuitX[i];
      tempY[i] = text_QuitY[i];
      text_QuitX_hl[i] = tempX[i];
      text_QuitY_hl[i] = tempY[i];
    }
#ifdef __DEBUG__
    fprintf(stdout, "Selected to quit.\n");
#endif
  }

  return;
}

GLvoid setMainImages() {
  GLuint i = 0;

  /* Set 'SINGLE PLAYER' to be highlighted */
  for ( i = 0; i < 4; i++ ) {
    text_SinglePlayerX_hl[i] = text_SinglePlayerX[i];
    text_SinglePlayerY_hl[i] = text_SinglePlayerY[i]; 
  }
  
  for ( i = 0; i < 4; i++ ) { /* Set all highlighted versions of text except for 'SINGLE PLAYER' to offscreen */
    text_MultiplayerX_hl[i] = offscreenVertexXY[i];
    text_MultiplayerY_hl[i] = offscreenVertexXY[i];
    text_OnlineX_hl[i] = offscreenVertexXY[i];
    text_OnlineY_hl[i] = offscreenVertexXY[i];
    text_OptionsX_hl[i] = offscreenVertexXY[i];
    text_OptionsY_hl[i] = offscreenVertexXY[i];
    text_QuitX_hl[i] = offscreenVertexXY[i];
    text_QuitY_hl[i] = offscreenVertexXY[i];
  }
  
  if ((texture[0] = loadTexture(bgTexture, 0)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", bgTexture);

  if ((texture[1] = loadTexture(logoTexture, 1)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", logoTexture);
  
  if ((texture[2] = loadTexture(mainSelector, 2)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", mainSelector);
  
  return;
}

GLvoid setMainText() {
  TTF_Font *font;
  font = TTF_OpenFont(defaultFont, 72); /* 72 seems to be the best size for this font */
  if (!font)
    fprintf(stderr, "SDL_ttf: TTF_OpenFont() response: %s\n", TTF_GetError());
  else {
    GLuint single, multiplayer, online, options, quit;
    GLuint singleS, multiplayerS, onlineS, optionsS, quitS; /* Selected equivalents */
    
    single = loadText("SINGLE PLAYER", font, blue_7CA4F6, 0);
    multiplayer = loadText("MULTIPLAYER", font, blue_7CA4F6, 1);
    online = loadText("ONLINE", font, blue_7CA4F6, 2);
    options = loadText("OPTIONS", font, blue_7CA4F6, 3);
    quit = loadText("QUIT", font, blue_7CA4F6, 4); /* Currently a nasty artifact to the right */
    
    /* Remember difference between selected equivalent and original texture is 5 in this case */
    singleS = loadText("SINGLE PLAYER", font, white, 5);
    multiplayerS = loadText("MULTIPLAYER", font, white, 6);
    onlineS = loadText("ONLINE", font, white, 7);
    optionsS = loadText("OPTIONS", font, white, 8);
    quitS = loadText("QUIT", font, white, 9);
  }

  if (font)
    TTF_CloseFont(font); /* Clean up */

  return;
}

GLvoid screenMain() {
  glBindTexture( GL_TEXTURE_2D, texture[0] );
  positionTexture(fillBGVertexX, fillBGVertexY, defVertexZ, defaultAlpha);

  glBindTexture( GL_TEXTURE_2D, texture[1] );
  positionTexture(logoVertexX, logoVertexY, defVertexZ, mSelectorAlpha); /* Remember last argument is the next texture's alpha value */

  glBindTexture( GL_TEXTURE_2D, texture[2] ); /* Use selector's default position */
  positionTexture(mSelectorVertexX, mSelectorVertexY, defVertexZ, defaultAlpha);
  
  /* Text positions */
  glBindTexture( GL_TEXTURE_2D, text[0] );
  positionTexture(text_SinglePlayerX, text_SinglePlayerY, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[1] );
  positionTexture(text_MultiplayerX, text_MultiplayerY, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[2] );
  positionTexture(text_OnlineX, text_OnlineY, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[3] );
  positionTexture(text_OptionsX, text_OptionsY, defVertexZ, defaultAlpha);

  glBindTexture( GL_TEXTURE_2D, text[4] );
  positionTexture(text_QuitX, text_QuitY, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[5] );
  positionTexture(text_SinglePlayerX_hl, text_SinglePlayerY_hl, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[6] );
  positionTexture(text_MultiplayerX_hl, text_MultiplayerY_hl, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[7] );
  positionTexture(text_OnlineX_hl, text_OnlineY_hl, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[8] );
  positionTexture(text_OptionsX_hl, text_OptionsY_hl, defVertexZ, defaultAlpha);
  
  glBindTexture( GL_TEXTURE_2D, text[9] );
  positionTexture(text_QuitX_hl, text_QuitY_hl, defVertexZ, defaultAlpha);

  return;
}
