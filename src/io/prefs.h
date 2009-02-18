#ifndef PREFS_H
#define PREFS_H

#define INIERROR "iniparser error string"

#define four_three    "4x3"
#define sixteen_nine  "16x9"
#define sixteen_ten   "16x10"

#ifdef __WIN32__
typedef unsigned int uint;
#endif

typedef char prefs_path; /* Preferences directories and paths to files */

typedef bool prefs_bool;
typedef char prefs_string;
typedef double prefs_double;
typedef int prefs_int;
typedef uint prefs_uint;
typedef short prefs_short;
typedef ushort prefs_ushort;

typedef struct { /* Freeband */
  char *language;
  ushort language_u;
  bool enable_demo;
  char *theme;
  char *default_instrument;
  ushort default_instrument_u;
  char *default_difficulty;
  ushort default_difficulty_u;
  ushort difficulty_judge;
  bool theming_mode;
} prefs_Freeband_s;

typedef struct { /* Audio */
  char *output_device;
  ushort output_device_u;
  char *input_device;
  ushort input_device_u;
  float global_offset;
} prefs_Audio_s;

typedef struct { /* Graphics */
  uint width;
  uint height;
  ushort bpp;
  char *aspect_ratio;
  ushort aspect_ratio_u;
  bool ar4x3;
  bool ar16x9;
  bool ar16x10;
  bool fullscreen;
  bool display_band;
  bool display_venue;
  bool display_audience;
} prefs_Graphics_s;

typedef struct { /* Input_Keyboard1 */
  bool enabled;
  char *button_green;
  char *button_red;
  char *button_yellow;
  char *button_blue;
  char *button_orange;
  char *button_pick_up;
  char *button_pick_down;
  char *button_start;
  char *button_select;
  char *button_direction_left;
  char *button_direction_right;
  char *button_direction_up;
  char *button_direction_down;
  char *whammy_up;
  char *whammy_down;
  char *star_power;
  char *screenshot;
} prefs_Input_Keyboard_s;

typedef struct { /* Input_Joystick1 */
  bool enabled;
  ushort button_green;
  ushort button_red;
  ushort button_yellow;
  ushort button_blue;
  ushort button_orange;
  ushort button_pick_up;
  ushort button_pick_down;
  ushort button_start;
  ushort button_select;
  ushort button_direction_left;
  ushort button_direction_right;
  ushort button_direction_up;
  ushort button_direction_down;
  ushort whammy_up;
  ushort whammy_down;
  ushort star_power;
  ushort screenshot;
} prefs_Input_Joystick_s;

extern dictionary *prefs;

extern prefs_path prefs_root[255];
extern prefs_path prefs_languages[255];
extern prefs_path prefs_songs[255];
extern prefs_path prefs_themes[255];

extern prefs_Freeband_s prefs_Freeband;
extern prefs_Audio_s prefs_Audio;
extern prefs_Graphics_s prefs_Graphics;
extern prefs_Input_Keyboard_s prefs_Input_Keyboard1;
extern prefs_Input_Keyboard_s prefs_Input_Keyboard2;
extern prefs_Input_Keyboard_s prefs_Input_Keyboard3;
extern prefs_Input_Joystick_s prefs_Input_Joystick1;
extern prefs_Input_Joystick_s prefs_Input_Joystick2;
extern prefs_Input_Joystick_s prefs_Input_Joystick3;

bool prefs_verify();
bool prefs_load();

#endif
