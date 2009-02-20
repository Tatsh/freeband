#ifndef PREFS_H
#define PREFS_H

#include "iniparser.h"

#define INIERROR "iniparser error string"

#define four_three    "4x3"
#define sixteen_nine  "16x9"
#define sixteen_ten   "16x10"

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
  bool fullscreen;
  bool display_band;
  bool display_venue;
  bool display_audience;
} prefs_Graphics_s;

typedef struct { /* Online */
  bool use_proxy;
  char *proxy_url;
  bool time_limit;
  ushort time_limit_sec;
} prefs_Online_s;

typedef struct { /* Songs */
  char *default_sort;
  char *last_song;
  bool use_last_song;
  bool save_song_speed; /* For keeping song speeds specific to songs */
  ushort default_speed_mod; /* From 1-4 */
  char *additional_folders; /* Comma separated list of paths with groups in them */
  bool time_limit;
  ushort time_limit_sec;
} prefs_Songs_s;

extern dictionary *prefs;

extern prefs_path prefs_root[255];
extern prefs_path prefs_languages[255];
extern prefs_path prefs_songs[255];
extern prefs_path prefs_themes[255];

extern prefs_Freeband_s prefs_Freeband;
extern prefs_Audio_s prefs_Audio;
extern prefs_Graphics_s prefs_Graphics;
extern prefs_Online_s prefs_Online;
extern prefs_Songs_s prefs_Songs;

bool prefs_verify();
bool prefs_load();

#endif
