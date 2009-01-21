#ifndef GAME_H
#define GAME_H

#define en_player_1 "PLAYER 1"
#define en_player_2 "PLAYER_2"
#define en_player_3 "PLAYER 3"
#define en_player_4 "PLAYER 4"

#define TRACKWIDTH       0.4f
#define STRINGOFFSET     0.51f
#define STRINGLENGTH    -5.0f
#define STRINGSPACE      0.16f
#define STRINGWIDTH      0.024f
#define STRINGSTRANS     0.58f
#define NOTEDIFF         0.111f
#define GREENNOTE       -0.277f
#define GREENSTRCOORD   -0.332f /* This influences all the other strings' positions! */

typedef struct {
  bool g;
  bool r;
  bool y;
  bool b;
  bool o;
} tButton;

extern bool gamePaused;
extern GLfloat bringDownAngle;

extern GLfloat NE_coord_neg;
extern GLfloat NE_coord_pos;

extern tButton screenGame_button;

GLvoid screenGame_buffer();
GLvoid screenGame();

#endif
