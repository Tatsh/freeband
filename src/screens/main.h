#ifndef MAIN_H
#define MAIN_H

#define MENUITEMSHT 0.21f

#define EN_SINGLE_PLAYER  "SINGLE PLAYER"
#define EN_MULTIPLAYER    "MULTIPLAYER"
#define en_online         "ONLINE"
#define en_options        "OPTIONS"
#define en_quit           "QUIT"

/* For later; I have no plans on building separate language builds
   Non-translated are commented out */
#define ES_SINGLE_PLAYER  "UN JUGADOR"
#define ES_MULTIPLAYER    "MULTIJUGADOR"
#define ES_ONLINE         "EN LÍNEA"
#define ES_OPTIONS        "OPCIÓN"
#define ES_QUIT           "DEJAR"

#define FR_SINGLE_PLAYER  "UN JOUER"
#define FR_MULTIPLAYER    "MULTIJOUER"
#define FR_ONLINE         "EN LIGNE"
#define FR_OPTIONS        "OPTIONS"
#define FR_QUIT           "QUITTER"

#define IT_SINGLE_PLAYER  "UN GIOCATORE"
#define IT_MULTIPLAYER    "MULTIGIOCATORE"
#define IT_ONLINE         "ON-LINE"
#define IT_OPTIONS        "OPZIONES"
#define IT_QUIT           "SMÉTTERE"

#define JA_SINGLE_PLAYER  "SINGLE_PLAYER" /* MOST Japanese games keep menus in English */
#define JA_MULTIPLAYER    "MULTIPLAYER"
#define JA_ONLINE         "ONLINE"
#define JA_OPTIONS        "OPTIONS"
#define JA_QUIT           "QUIT"

/*
#define AR_SINGLE_PLAYER  ""
#define AR_MULTIPLAYER    ""
#define AR_ONLINE         ""
#define AR_OPTIONS        ""
#define AR_QUIT           ""

#define ZHS_SINGLE_PLAYER   ""
#define ZHS_MULTIPLAYER     ""
#define ZHS_ONLINE          ""
#define ZHS_OPTIONS         ""
#define ZHS_QUIT            ""

#define ZHT_SINGLE_PLAYER   ""
#define ZHT_MULTIPLAYER     ""
#define ZHT_ONLINE          ""
#define ZHT_OPTIONS         ""
#define ZHT_QUIT            ""*/

#define SELECTSRC_ALPHA 0.3f
#define SELECTDST_ALPHA 0.6f

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

#endif
