#ifndef MAIN_H
#define MAIN_H

#define MENUITEMSHT 0.21f

#define SELECTSRC_ALPHA 0.3f
#define SELECTDST_ALPHA 0.6f

#define EN_SELECT "SELECT" /* These are used for spacing purposes only! */
#define EN_BACK "BACK"
#define EN_UPDOWN "UP/DOWN"

typedef struct {
  bool single; /* This does NOT affect the initial position of the selector */
  bool multiplayer;
  bool online;
  bool options;
  bool quit;
} mainMenu_s;

extern bool nonGame;
extern bool online;
extern bool options;
extern char bgTexture[];
extern char logoTexture[];
extern char mainSelector[];
extern GLfloat screenMain_logoX[];
extern GLfloat screenMain_logoY[];
extern GLfloat screenMain_selectionX[]; /* Main menu selector's default position */
extern GLfloat screenMain_selectionY[];
extern GLfloat text_MultiplayerY[], text_OnlineY[], text_OptionsY[], text_QuitY[];
extern GLuint screenMain_nSelection;
extern mainMenu_s screenMain_selection;

bool screenMain_buffer();
GLvoid screenMain_highlighted(GLuint nSelection);
GLvoid screenMain_accept();
GLvoid screenMain();

bool screenMenuFooter_buffer();
GLvoid screenMenuFooter();

#endif
