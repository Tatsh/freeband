#ifndef GAME_H
#define GAME_H

#include "freeband.h"

#define en_player_1 "PLAYER 1"
#define en_player_2 "PLAYER_2"
#define en_player_3 "PLAYER 3"
#define en_player_4 "PLAYER 4"

#define TRACKWIDTH 0.4f
#define STRINGOFFSET 0.51f
#define STRINGLENGTH -5.0f
#define STRINGSPACE 0.16f
#define STRINGWIDTH 0.024f
#define STRINGSTRANS 0.58f
#define NOTEDIFF 0.111f
#define GREENNOTE -0.277f
#define GREENSTRCOORD -0.332f /* This influences all the other strings' positions! */

#define NOTE_HIT 0x00
#define NOTE_HIT_WITH_EXTRA 0x01
#define ALL_NOTES_HIT 0x02
#define COMPLETE_MISS 0x03
#define FREEZE_BARELY_OFF 0x04
#define FREEZE_HIT_AND_RELEASED 0x05

#define DEAD_NOTE 0x00
#define SONG_END 0xFF

#define SCORE_ADD 250 /* Might change later */
#define SCORE_ADD_FAILED 10
#define LIFE_ADD 0.1

#define NOTE_BUFFER 100

typedef struct {
  bool g;
  bool r;
  bool y;
  bool b;
  bool o;
} button_s;

typedef struct {
  ushort note;
  ushort speed;
  ushort hit;
} timing_window_s;

extern GLfloat bringDownAngle;

extern GLfloat NE_coord_neg;
extern GLfloat NE_coord_pos;

extern button_s screenGame_button;
extern timing_window_s timing_window[];

GLvoid screenGame_buffer();
GLvoid screenGame();

#endif
