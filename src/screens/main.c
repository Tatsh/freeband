#include "../freeband.h"
#include "../graphics/graphics.h"
#include "main.h"

#define SELECTBLENDSRC  0.30f
#define SELECTBLENDDEST 0.60f

char defaultFont[] = "GameData/themes/default/global/crillee.ttf";

/* Negative is to the left, positive is to the right when horizontal (x)
   Negative is to the top, positive is to the bottom when vertical (y)
   Negative is to the outside, positive is going inside (z)
  Order of corners: top-left, bottom-left, bottom-right, top-right */
GLfloat logoVertexX[] = { -1.25f, -1.25f, 1.26f, 1.26f }; /* Logo position */
GLfloat logoVertexY[] = {  -1.0f,   0.0f,  0.0f, -1.0f };

GLfloat mSelectorVertexX[] = { 0.0f, 0.0f, 1.3f, 1.3f }; /* Main menu selector's default position */
GLfloat mSelectorVertexY[] = {  0.18f,   0.0f,  0.0f, 0.18f };

/* Text positions, all are false italic. These take FOREVER! */
GLfloat text_SinglePlayerX[] = { 0.09f, 0.07f, 1.22f, 1.24f }; /* SINGLE PLAYER */
GLfloat text_MultiplayerX[]  = { 0.11f, 0.09f, 1.18f, 1.2f }; /* MULTIPLAYER */
GLfloat text_OnlineX[] = { 0.24f, 0.22f, 0.98f, 1.0f }; /* ONLINE */
GLfloat text_OptionsX[] = { 0.24f, 0.22f, 0.98f, 1.0f };
GLfloat text_QuitX[] = { 0.24f, 0.22f, 0.98f, 1.0f };

GLuint menuSelection = 0;

tMenuState menuState;

void setMainMenuState(int selectID) {
  if (selectID < 1) { /* Single player */
    menuState.single = true;
    menuState.multiplayer = false;
    menuState.online = false;
    menuState.options = false;
    menuState.quit = false;
#ifdef __DEBUG__
  fprintf(stdout, "Selected single player mode.\n");
#endif
  }
  else if (selectID < 2) {
    menuState.single = false;
    menuState.multiplayer = true;
    menuState.online = false;
    menuState.options = false;
    menuState.quit = false;
#ifdef __DEBUG__
    fprintf(stdout, "Selected multiplayer player mode.\n");
#endif
  }
  else if (selectID < 3) {
    menuState.single = false;
    menuState.multiplayer = false;
    menuState.online = true;
    menuState.options = false;
    menuState.quit = false;
#ifdef __DEBUG__
    fprintf(stdout, "Selected online mode.\n");
#endif
  }
  else if (selectID < 4) {
    menuState.single = false;
    menuState.multiplayer = false;
    menuState.online = false;
    menuState.options = true;
    menuState.quit = false;
#ifdef __DEBUG__
    fprintf(stdout, "Selected options menu.\n");
#endif
  }
  else {
    menuState.single = false;
    menuState.multiplayer = false;
    menuState.online = false;
    menuState.options = false;
    menuState.quit = true;
#ifdef __DEBUG__
    fprintf(stdout, "Selected to quit.\n");
#endif
  }

  return;
}

void setMainText() {
  TTF_Font *font;
  font = TTF_OpenFont(defaultFont, 72); /* 72 seems to be the best size for this font */
  if (!font)
    fprintf(stderr, "SDL_ttf: TTF_OpenFont() response: %s\n", TTF_GetError());
  else {
    GLuint single, multiplayer, online, options, quit;
    SDL_Color white;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    
    single = loadText("SINGLE PLAYER", font, white, 3);
    multiplayer = loadText("MULTIPLAYER", font, white, 4);
    online = loadText("ONLINE", font, white, 5);
    options = loadText("OPTIONS", font, white, 6);
    quit = loadText("QUIT", font, white, 7);
  }

  if (font)
    TTF_CloseFont(font); /* If we do not do this, we run out of RAM quickly! */

  return;
}

void screenMain() {
  menuState.single = true;

  glBindTexture( GL_TEXTURE_2D, texture[0] );
  positionTexture(fillBGVertexX, fillBGVertexY, defVertexZ);

  glBindTexture( GL_TEXTURE_2D, texture[1] );
  positionTexture(logoVertexX, logoVertexY, defVertexZ);

  glBindTexture( GL_TEXTURE_2D, texture[2] ); /* Use selector's default position */
  positionTexture(mSelectorVertexX, mSelectorVertexY, defVertexZ);
  /*glColor4f(1.0f, 1.0f, 1.0f, SELECTBLENDSRC);*/
  
  setMainText();
  glBindTexture( GL_TEXTURE_2D, texture[3] );
  positionTexture(text_SinglePlayerX, text_SinglePlayerY, defVertexZ);
  
  glBindTexture( GL_TEXTURE_2D, texture[4] );
  
  positionTexture(text_MultiplayerX, text_MultiplayerY, defVertexZ);
  
  glBindTexture( GL_TEXTURE_2D, texture[5] );
  positionTexture(text_OnlineX, text_OnlineY, defVertexZ);
  
  glBindTexture( GL_TEXTURE_2D, texture[6] );
  positionTexture(text_OptionsX, text_OptionsY, defVertexZ);

  glBindTexture( GL_TEXTURE_2D, texture[7] );
  positionTexture(text_QuitX, text_QuitY, defVertexZ);

  return;
}
