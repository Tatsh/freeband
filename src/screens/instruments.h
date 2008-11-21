typedef struct {
  bool guitar;
  bool bass;
  bool drums;
  bool vocals;
} tInstrument;

extern GLfloat selectedGradientY[], selectedGradientY_reset[];
extern GLuint instSelection;
extern tInstrument instrument;

GLvoid handleInstrumentsMenu();
GLvoid setInstrumentsImages_1P();
GLvoid setInstrumentsMenuState_1P(GLuint instSelection);
GLvoid setInstrumentsText_1P();
GLvoid screenInstrumentsBuffer(GLuint nPlayers);
GLvoid screenInstruments(GLuint nPlayers);
