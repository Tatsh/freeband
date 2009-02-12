#ifndef PREFS_H
#define PREFS_H

#include <iniparser.h>

#define INIERROR "INI Error string"

#define PREFS_GUITAR 0
#define PREFS_BASS 1
#define PREFS_DRUMS 2
#define PREFS_VOCALS 3

#define PREFS_EASY 0
#define PREFS_MEDIUM 1
#define PREFS_HARD 2
#define PREFS_EXPERT 3

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

/* [Freeband] */
extern prefs_bool freeband_enable_demo;
extern prefs_string *freeband_theme;
extern prefs_ushort freeband_default_instrument_s;
extern prefs_ushort freeband_default_difficulty_s;
extern prefs_ushort freeband_difficulty_judge;
extern prefs_bool freeband_theming_mode;

/* [Graphics] */
extern prefs_uint graphics_width;
extern prefs_uint graphics_height;

bool prefs_verify();
bool prefs_load();

#endif
