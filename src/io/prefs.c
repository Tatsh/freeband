#include "../freeband.h"
#include "defaults.h"
#include "languages.h"
#include "prefs.h"
#include "keys.h"

#ifdef __WIN32__
#include <shlobj.h>
#endif

prefs_path prefs_root[255];
prefs_path prefs_songs[255];
prefs_path prefs_themes[255];
prefs_path prefs_ini[255];

/* [Freeband] */
prefs_string *freeband_language;
prefs_ushort freeband_language_s;
prefs_bool freeband_enable_demo;
prefs_string *freeband_theme;
prefs_string *freeband_default_instrument;
prefs_ushort freeband_default_instrument_s;
prefs_string *freeband_default_difficulty;
prefs_ushort freeband_default_difficulty_s;
prefs_ushort freeband_difficulty_judge;
prefs_bool freeband_theming_mode;

/* [Graphics] */
prefs_uint graphics_width;
prefs_uint graphics_height;

bool prefs_verify() { /* This function only checks and fixes preferences; it does NOT read them */
  short ret;
  
  /* We get the $HOME or %%HOME (Windows) environment variable */
#ifdef __WIN32__
  char myDocuments[255]; /* TCHAR is char */
  if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, myDocuments)))
    strcat(prefs_root, myDocuments);
  
  if (prefs_root == NULL) {
    fprintf(stderr, "Could not find My Documents folder. Check to make sure you have one assigned in your Windows settings.\n");
    return false;
  }
#else /* POSIX; this is preferred :) */
  strcat(prefs_root, getenv("HOME"));
  
  if (prefs_root == NULL) {
    fprintf(stderr, "Could not find home directory.\nTry setting $HOME to a path.");
    return false;
  }
#endif

  strcat(prefs_root, "/Freeband"); /* Create paths to search for or make */
  strcat(prefs_songs, prefs_root);
  strcat(prefs_songs, "/songs");
  strcat(prefs_themes, prefs_root);
  strcat(prefs_themes, "/themes");
  strcat(prefs_ini, prefs_root);
  strcat(prefs_ini, "/preferences.ini");
  
#ifdef __WIN32__
  struct _stat buffer;
  
  if ((ret = _stat(prefs_root, &buffer)) != 0) {
    fprintf(stderr, "Unable to locate Freeband directory in your home directory. Creating one now...\n");
    
    if ((ret = _mkdir(prefs_root)) != 0) {
      fprintf(stderr, "Unable to create %s directory. Check if you have permission.\n", prefs_root);
      return false;
    }
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "Found preferences root: %s.\n", prefs_root);
#endif

  if ((ret = _stat(prefs_songs, &buffer)) != 0) { /* No? Create songs folder */
    fprintf(stderr, "Unable to locate a Freeband songs directory. Creating one now...\n");
    
    if ((ret = _mkdir(prefs_songs)) != 0) {
      fprintf(stderr, "Unable to create %s directory. Check if you have permission.\n", prefs_songs);
      return false; /* Error! Do we have permission? */
    }
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "Found songs directory: %s.\n", prefs_songs);
#endif

  if ((ret = _stat(prefs_themes, &buffer)) != 0) { /* No? Create themes folder and copy default theme to it */
    fprintf(stderr, "Unable to locate a Freeband themes directory. Creating one now...\n");
    
    if ((ret = _mkdir(prefs_themes)) != 0) {
      fprintf(stderr, "Unable to create %s directory. Check if you have permission.\n", prefs_themes);
      return false; /* Error! Do we have permission? */
    }
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "Found themes directory: %s.\n", prefs_themes);
#endif

  /* Do we already have a preferences.ini file in $HOME/Freeband? */
  if ((ret = _stat(prefs_ini, &buffer)) != 0) { /* No? Copy a default one then */
    fprintf(stderr, "Unable to find %s file. Copying a default one now...\n", prefs_ini);
    defaults_copyFile("GameData/preferences.ini", prefs_ini);
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "Found preferences.ini file: %s.\nGetting preferences...\n", prefs_ini);
#endif
  
#else /* POSIX */
  struct stat buffer;
  
  /* We check to see if $HOME has a directory 'Freeband' */
  if ((ret = stat(prefs_root, &buffer)) != 0) { /* No? Create one */
    fprintf(stderr, "Unable to locate a Freeband directory in your home directory. Creating one now...\n");
    
    if ((ret = mkdir(prefs_root, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0) {
      fprintf(stderr, "Unable to create %s directory. Check if you have permission.\n", prefs_root);
      return false; /* Error! Do we have permission? */
    }
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "Found preferences root: %s.\n", prefs_root);
#endif
  
  /* Do we have a songs folder? */
  if ((ret = stat(prefs_songs, &buffer)) != 0) { /* No? Create songs folder */
    fprintf(stderr, "Unable to locate a Freeband songs directory. Creating one now...\n");
    
    if ((ret = mkdir(prefs_songs, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0) {
      fprintf(stderr, "Unable to create %s directory. Check if you have permission.\n", prefs_songs);
      return false; /* Error! Do we have permission? */
    }
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "Found songs directory: %s.\n", prefs_songs);
#endif
  
  /* Do we have a themes folder? */
  if ((ret = stat(prefs_themes, &buffer)) != 0) { /* No? Create themes folder and copy default theme to it */
    fprintf(stderr, "Unable to locate a Freeband themes directory. Creating one now...\n");
    
    if ((ret = mkdir(prefs_themes, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0) {
      fprintf(stderr, "Unable to create %s directory. Check if you have permission.\n", prefs_themes);
      return false; /* Error! Do we have permission? */
    }
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "Found themes directory: %s.\n", prefs_themes);
#endif

  /* Do we already have a preferences.ini file in $HOME/Freeband? */
  if ((ret = stat(prefs_ini, &buffer)) != 0) { /* No? Copy a default one then */
    fprintf(stderr, "Unable to find %s file. Copying a default one now...\n", prefs_ini);
    defaults_copyFile("GameData/preferences.ini", prefs_ini);
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "Found preferences.ini file: %s.\nGetting preferences...\n", prefs_ini);
#endif
  
#endif

  return true; /* Checking for default preferences, songs and themes is handled in defaults.c */
}

bool prefs_load() {
  dictionary *prefs;

  if ((prefs = iniparser_load(prefs_ini)) == NULL) {
    fprintf(stderr, "Error loading %s dictionary using iniparser.\n", prefs_ini);
    return false;
  }

  /* [Freeband] */
  freeband_language = iniparser_getstring(prefs, "Freeband:language", INIERROR);
  if (strcmp(INIERROR, freeband_language) == 0) /* Verify language file exists later */
    freeband_language = "en_GB";
  if (strcmp("en_US", freeband_language) == 0)
    freeband_language_s = en_US;
  else if (strcmp("zh_CN", freeband_language) == 0)
    freeband_language_s = zh_CN;
  else
    freeband_language_s = en_GB;
  
  if ((freeband_enable_demo = iniparser_getboolean(prefs, "Freeband:enable_demo", -1)) != 1)
    freeband_enable_demo = false;
  else
    freeband_enable_demo = true;

  freeband_theme = iniparser_getstring(prefs, "Freeband:theme", INIERROR);
  if (strcmp(INIERROR, freeband_theme) == 0) /* We will verify the folder exists later */
    freeband_theme = "default";
  
  freeband_default_instrument = iniparser_getstring(prefs, "Freeband:default_instrument", INIERROR);
  if (strcmp(INIERROR, freeband_default_instrument) == 0)
    freeband_default_instrument = "guitar";
  if (strcmp("guitar", freeband_default_instrument) == 0) /* This is for if default_instrument="fioejaiofej" for example */
    freeband_default_instrument_s = PREFS_GUITAR;
  else if (strcmp("bass", freeband_default_instrument) == 0)
    freeband_default_instrument_s = PREFS_BASS;
  else if (strcmp("drums", freeband_default_instrument) == 0)
    freeband_default_instrument_s = PREFS_DRUMS;
  else if (strcmp("vocals", freeband_default_instrument) == 0)
    freeband_default_instrument_s = PREFS_VOCALS;
  else
    freeband_default_instrument_s = PREFS_GUITAR;
  
  freeband_default_difficulty = iniparser_getstring(prefs, "Freeband:default_difficulty", INIERROR);
  if (strcmp(INIERROR, freeband_default_instrument) == 0)
    freeband_default_difficulty = "easy";
  if (strcmp("easy", freeband_default_difficulty) == 0)
    freeband_default_difficulty_s = PREFS_EASY;
  else if (strcmp("medium", freeband_default_difficulty) == 0)
    freeband_default_difficulty_s = PREFS_MEDIUM;
  else if (strcmp("hard", freeband_default_difficulty) == 0)
    freeband_default_difficulty_s = PREFS_HARD;
  else if (strcmp("expert", freeband_default_difficulty) == 0)
    freeband_default_instrument_s = PREFS_EXPERT;
  else
    freeband_default_instrument_s = PREFS_EASY;
  
  freeband_difficulty_judge = iniparser_getint(prefs, "Freeband:difficulty_judge", 11);
  if (freeband_difficulty_judge < 1 || freeband_difficulty_judge > 10) {
    /* iniparser_set(prefs, "Freeband:difficulty_judge", "5"); Requires patched iniparser.h */
    fprintf(stderr, "Invalid judge setting. Using default: 5\n");
    
    freeband_difficulty_judge = 5;
  }
  
  if ((freeband_theming_mode = iniparser_getboolean(prefs, "Freeband:theming_mode", -1)) != 1)
    freeband_theming_mode = false;
  else
    freeband_theming_mode = true;

  /* [Graphics] */
  graphics_width = iniparser_getint(prefs, "Graphics:width", -1);
  graphics_height = iniparser_getint(prefs, "Graphics:height", -1);
  
  /* [InputKeyboard1] */

#ifdef __DEBUG__
  fprintf(stdout, "\n[Freeband]\n");
  fprintf(stdout, "language=%s (%#x)\n", freeband_language, freeband_language_s);
  fprintf(stdout, "enable_demo=%s\n", freeband_enable_demo ? "true" : "false");
  fprintf(stdout, "theme=%s\n", freeband_theme);
  fprintf(stdout, "default_instrument=%s (%d)\n", freeband_default_instrument, freeband_default_instrument_s);
  fprintf(stdout, "default_difficulty=%s (%d)\n", freeband_default_difficulty, freeband_default_instrument_s);
  fprintf(stdout, "difficulty_judge=%d\n", freeband_difficulty_judge);
  fprintf(stdout, "theming_mode=%s\n\n", freeband_theming_mode ? "true" : "false");
  
  fprintf(stdout, "[Graphics]\n");
  fprintf(stdout, "width=%d\n", graphics_width);
  fprintf(stdout, "height=%d\n", graphics_height);
#endif
  
  iniparser_freedict(prefs);
#ifdef __DEBUG__
  fprintf(stdout, "\nFreed %s dictionary.\n", prefs_ini);
#endif
  
  return true;
}
