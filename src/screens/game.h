typedef struct {
  bool g;
  bool r;
  bool y;
  bool b;
  bool o;
} tButton;

extern tButton button;

extern bool bar;
extern bool beat;
extern bool beat2;
extern bool beat3;
extern bool gamePaused;
extern GLfloat bringDownAngle;

GLvoid screenGameBuffer();
GLvoid screenGame();
