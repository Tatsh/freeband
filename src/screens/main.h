typedef struct {
  bool single; /* This does NOT affect the initial position of the selector */
  bool multiplayer;
  bool online;
  bool options;
  bool quit;
} tMenuState;

extern char defaultFont[];
extern tMenuState menuState;
extern GLfloat logoVertexX[];
extern GLfloat logoVertexY[];
extern GLfloat mSelectorVertexX[]; /* Main menu selector's default position */
extern GLfloat mSelectorVertexY[];
extern GLuint menuSelection;
extern GLfloat text_SinglePlayerY[], text_MultiplayerY[], text_OnlineY[], text_OptionsY[], text_QuitY[];

void setMainMenuState(int selectID);
void setMainText();
void screenMain();
