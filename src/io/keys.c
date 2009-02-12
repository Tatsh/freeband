#include "../freeband.h"
#include "prefs.h"
#include "keys.h"

/* Map string keys in the INI file to SDL equivalents */
int keys_mapKeystringToSDL(char keystring[]) {
  int key;

  if ((strncmp("ESC", keystring, 3)) == 0)  key = SDLK_ESCAPE;
  if ((strncmp("F1", keystring, 2)) == 0)   key = SDLK_F1;
  if ((strncmp("F2", keystring, 2)) == 0)   key = SDLK_F2;
  if ((strncmp("F3", keystring, 2)) == 0)   key = SDLK_F3;
  if ((strncmp("F4", keystring, 2)) == 0)   key = SDLK_F4;
  if ((strncmp("F5", keystring, 2)) == 0)   key = SDLK_F5;
  if ((strncmp("F6", keystring, 2)) == 0)   key = SDLK_F6;
  if ((strncmp("F7", keystring, 2)) == 0)   key = SDLK_F7;
  if ((strncmp("F8", keystring, 2)) == 0)   key = SDLK_F8;
  if ((strncmp("F9", keystring, 2)) == 0)   key = SDLK_F9;
  if ((strncmp("F10", keystring, 3)) == 0)  key = SDLK_F10;
  if ((strncmp("F11", keystring, 3)) == 0)  key = SDLK_F11;
  if ((strncmp("F12", keystring, 3)) == 0)  key = SDLK_F12;
  if ((strncmp("esc", keystring, 3)) == 0)  key = SDLK_ESCAPE;
  if ((strncmp("f1", keystring, 2)) == 0)   key = SDLK_F1;
  if ((strncmp("f2", keystring, 2)) == 0)   key = SDLK_F2;
  if ((strncmp("f3", keystring, 2)) == 0)   key = SDLK_F3;
  if ((strncmp("f4", keystring, 2)) == 0)   key = SDLK_F4;
  if ((strncmp("f5", keystring, 2)) == 0)   key = SDLK_F5;
  if ((strncmp("f6", keystring, 2)) == 0)   key = SDLK_F6;
  if ((strncmp("f7", keystring, 2)) == 0)   key = SDLK_F7;
  if ((strncmp("f8", keystring, 2)) == 0)   key = SDLK_F8;
  if ((strncmp("f9", keystring, 2)) == 0)   key = SDLK_F9;
  if ((strncmp("f10", keystring, 3)) == 0)  key = SDLK_F10;
  if ((strncmp("f11", keystring, 3)) == 0)  key = SDLK_F11;
  if ((strncmp("f12", keystring, 3)) == 0)  key = SDLK_F12;

  if ((strncmp("A", keystring, 1)) == 0)    key = SDLK_a;
  if ((strncmp("B", keystring, 1)) == 0)    key = SDLK_b;
  if ((strncmp("C", keystring, 1)) == 0)    key = SDLK_c;
  if ((strncmp("D", keystring, 1)) == 0)    key = SDLK_d;
  if ((strncmp("E", keystring, 1)) == 0)    key = SDLK_e;
  if ((strncmp("F", keystring, 1)) == 0)    key = SDLK_f;
  if ((strncmp("G", keystring, 1)) == 0)    key = SDLK_g;
  if ((strncmp("H", keystring, 1)) == 0)    key = SDLK_h;
  if ((strncmp("I", keystring, 1)) == 0)    key = SDLK_i;
  if ((strncmp("J", keystring, 1)) == 0)    key = SDLK_j;
  if ((strncmp("K", keystring, 1)) == 0)    key = SDLK_k;
  if ((strncmp("L", keystring, 1)) == 0)    key = SDLK_l;
  if ((strncmp("M", keystring, 1)) == 0)    key = SDLK_m;
  if ((strncmp("N", keystring, 1)) == 0)    key = SDLK_n;
  if ((strncmp("O", keystring, 1)) == 0)    key = SDLK_o;
  if ((strncmp("P", keystring, 1)) == 0)    key = SDLK_p;
  if ((strncmp("Q", keystring, 1)) == 0)    key = SDLK_q;
  if ((strncmp("R", keystring, 1)) == 0)    key = SDLK_r;
  if ((strncmp("S", keystring, 1)) == 0)    key = SDLK_s;
  if ((strncmp("T", keystring, 1)) == 0)    key = SDLK_t;
  if ((strncmp("U", keystring, 1)) == 0)    key = SDLK_u;
  if ((strncmp("V", keystring, 1)) == 0)    key = SDLK_v;
  if ((strncmp("W", keystring, 1)) == 0)    key = SDLK_w;
  if ((strncmp("X", keystring, 1)) == 0)    key = SDLK_x;
  if ((strncmp("Y", keystring, 1)) == 0)    key = SDLK_y;
  if ((strncmp("Z", keystring, 1)) == 0)    key = SDLK_z;
  if ((strncmp("a", keystring, 1)) == 0)    key = SDLK_a;
  if ((strncmp("b", keystring, 1)) == 0)    key = SDLK_b;
  if ((strncmp("c", keystring, 1)) == 0)    key = SDLK_c;
  if ((strncmp("d", keystring, 1)) == 0)    key = SDLK_d;
  if ((strncmp("e", keystring, 1)) == 0)    key = SDLK_e;
  if ((strncmp("f", keystring, 1)) == 0)    key = SDLK_f;
  if ((strncmp("g", keystring, 1)) == 0)    key = SDLK_g;
  if ((strncmp("h", keystring, 1)) == 0)    key = SDLK_h;
  if ((strncmp("i", keystring, 1)) == 0)    key = SDLK_i;
  if ((strncmp("j", keystring, 1)) == 0)    key = SDLK_j;
  if ((strncmp("k", keystring, 1)) == 0)    key = SDLK_k;
  if ((strncmp("l", keystring, 1)) == 0)    key = SDLK_l;
  if ((strncmp("m", keystring, 1)) == 0)    key = SDLK_m;
  if ((strncmp("n", keystring, 1)) == 0)    key = SDLK_n;
  if ((strncmp("o", keystring, 1)) == 0)    key = SDLK_o;
  if ((strncmp("p", keystring, 1)) == 0)    key = SDLK_p;
  if ((strncmp("q", keystring, 1)) == 0)    key = SDLK_q;
  if ((strncmp("r", keystring, 1)) == 0)    key = SDLK_r;
  if ((strncmp("s", keystring, 1)) == 0)    key = SDLK_s;
  if ((strncmp("t", keystring, 1)) == 0)    key = SDLK_t;
  if ((strncmp("u", keystring, 1)) == 0)    key = SDLK_u;
  if ((strncmp("v", keystring, 1)) == 0)    key = SDLK_v;
  if ((strncmp("w", keystring, 1)) == 0)    key = SDLK_w;
  if ((strncmp("x", keystring, 1)) == 0)    key = SDLK_x;
  if ((strncmp("y", keystring, 1)) == 0)    key = SDLK_y;
  if ((strncmp("z", keystring, 1)) == 0)    key = SDLK_z;

  return key;
}
