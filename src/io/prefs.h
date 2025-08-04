#ifndef PREFS_H
#define PREFS_H

#include "freeband.h"
#include "iniparser.h"

#define INIERROR "iniparser error string"
#define FREEBAND_PREFS_ROOT "/Freeband"
#define FREEBAND_PREFS_INI "/preferences.ini"
#define FREEBAND_PREFS_LANGS_ROOT "/languages"
#define FREEBAND_PREFS_SONGS_ROOT "/songs"
#define FREEBAND_PREFS_THEMES_ROOT "/themes"

#define INSTRUMENT_GUITAR 0
#define INSTRUMENT_BASS 1
#define INSTRUMENT_DRUMS 2
#define INSTRUMENT_VOCALS 3

#define SORT_BY_TIER 0
#define SORT_AZ_TITLE 1
#define SORT_AZ_ARTIST 2
#define SORT_BY_BPM 3

typedef char prefs_path; /* Preferences directories and paths to files */

typedef struct {
  char ini_item[ARRAY_BUFFER];
  bool bDefault_value;
  bool bUser_value;
} prefs_bool_s;

typedef struct {
  char ini_item[ARRAY_BUFFER];
  char cDefault_value[ARRAY_BUFFER];
  char *cUser_value;
  int iValue;
} prefs_char_s;

typedef struct {
  char ini_item[ARRAY_BUFFER];
  double dDefault_value;
  double dUser_value;
} prefs_double_s;

typedef struct {
  char ini_item[ARRAY_BUFFER];
  int iDefault_value;
  int iUser_value;
} prefs_ints_s;

typedef struct {
  char ini_item[ARRAY_BUFFER];
  short sDefault_value;
  short sUser_value;
} prefs_short_s;

/* Commented out till we need these
typedef struct {
  char ini_item[ARRAY_BUFFER];
  uint uiDefault_value;
  uint uiUser_value;
} prefs_uints_s;

typedef struct {
  char ini_item[ARRAY_BUFFER];
  ushort usDefault_value;
  ushort usUser_value;
} prefs_ushort_s;*/

extern dictionary *prefs;

extern prefs_path prefs_root[ARRAY_BUFFER * 2];
extern prefs_path prefs_languages[ARRAY_BUFFER * 2];
extern prefs_path prefs_songs[ARRAY_BUFFER * 2];
extern prefs_path prefs_themes[ARRAY_BUFFER * 2];

extern prefs_bool_s prefs_bools[];
extern prefs_char_s prefs_chars[];
extern prefs_ints_s prefs_ints[];
extern prefs_short_s prefs_shorts[];

bool prefs_verify();
bool prefs_load();
void prefs_getKeys(dictionary *prefs);

#endif
