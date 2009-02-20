#ifndef KEYS_H
#define KEYS_H

#define KEYS_NOKEY -1

typedef struct { /* Input_Keyboard */
  bool enabled;
  bool disable_pick;
  uint button_green;
  uint button_red;
  uint button_yellow;
  uint button_blue;
  uint button_orange;
  uint button_pick_up;
  uint button_pick_down;
  uint button_start;
  uint button_select;
  uint button_direction_left;
  uint button_direction_right;
  uint button_direction_up;
  uint button_direction_down;
  uint whammy_up;
  uint whammy_down;
  uint star_power;
  uint screenshot;
} prefs_Input_Keyboard_s;

extern prefs_Input_Keyboard_s prefs_Input_Keyboard[];

int keys_mapKeystringToSDL(char *key);
void prefs_keys_get();

#endif
