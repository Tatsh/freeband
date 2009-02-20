#ifndef JOYPAD_H
#define JOYPAD_H

typedef struct { /* Input_Joystick */
  bool enabled;
  short button_green;
  short button_red;
  short button_yellow;
  short button_blue;
  short button_orange;
  short button_pick_up;
  short button_pick_down;
  short button_start;
  short button_select;
  short button_direction_left;
  short button_direction_right;
  short button_direction_up;
  short button_direction_down;
  short whammy_up;
  short whammy_down;
  short star_power;
  short screenshot;
} prefs_Input_Joystick_s;

extern prefs_Input_Joystick_s prefs_Input_Joystick[];

#endif /* JOYPAD_H */
