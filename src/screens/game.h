typedef struct {
  bool g;
  bool r;
  bool y;
  bool b;
  bool o;
} tButton;

extern tButton button;

extern bool gamePaused;
extern GLfloat bringDownAngle;

GLvoid screenGameBuffer();
GLvoid screenGame();
