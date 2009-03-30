#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../screens/difficulty.h"
#include "../screens/instruments.h"
#include "fileio.h"
#include "joypad.h"
#include "keys.h"
#include "languages.h"
#include "prefs.h"

#ifdef __WIN32__
#include "unix2dos.h"
#endif

dictionary *prefs;

prefs_path prefs_root[ARRAY_BUFFER * 2];
prefs_path prefs_languages[ARRAY_BUFFER * 2];
prefs_path prefs_songs[ARRAY_BUFFER * 2];
prefs_path prefs_themes[ARRAY_BUFFER * 2];
prefs_path prefs_ini[ARRAY_BUFFER * 2];

prefs_bool_s prefs_bools[] = {
  { "Freeband:enable_demo", true, true },
  { "Freeband:theming_mode", false, false },
  
  { "Graphics:display_band", true, true },
  { "Graphics:display_venue", true, true },
  { "Graphics:fullscreen", false, false },
  
  { "Online:time_limit", false, false },
  { "Online:use_proxy", false, false },
  
  { "Songs:use_last_song", true, true },
  { "Songs:save_song_speed", true, true },
  { "Songs:time_limit", false, false },
  { "Songs:fail_to_end", true, true }
};

bool prefs_getBools(dictionary *prefs) {
  ushort i;
  
  for (i = 0; i < structln(prefs_bools); i++)
    prefs_bools[i].bUser_value = iniparser_getboolean(prefs, prefs_bools[i].ini_item, -1);
  
  return true;
}

prefs_char_s prefs_chars[] = {
  { "Freeband:language", "en_GB", "en_GB", 0x00 },
  { "Freeband:theme", "default", "default", 0 }, /* No numbers here */
  { "Freeband:default_instrument", "guitar", "guitar", INSTRUMENT_GUITAR },
  { "Freeband:default_difficulty", "easy", "easy", DIFFICULTY_EASY },
  
  { "Audio:output_device", "none", "none", 0 },
  { "Audio:mic_device", "none", "none", 0 },
  
  { "Online:proxy_url", "none", "none", 0 },
  
  { "Songs:default_sort", "by Tier", "by Tier", SORT_BY_TIER },
  { "Songs:last_song", "", "", 0 },
  { "Songs:additional_folders", "", "", 0 }
};

bool prefs_getChars(dictionary *prefs) {
  ushort i;
  
  for (i = 0; i < structln(prefs_chars); i++) 
    prefs_chars[i].cUser_value = iniparser_getstring(prefs, prefs_chars[i].ini_item, INIERROR);
  
  return true;
}

prefs_ints_s prefs_ints[] = {
  { "Graphics:width", 800, 800 },
  { "Graphics:height", 600, 600 }
};

prefs_short_s prefs_shorts[] = {
  { "Freeband:difficulty_judge", 5, 5 },
  
  { "Graphics:bpp", 32, 32 },
};

bool prefs_getInts(dictionary *prefs) {
  ushort i;
  
  for (i = 0; i < structln(prefs_ints); i++) /* Handle ints and shorts here */
    prefs_ints[i].iUser_value = iniparser_getint(prefs, prefs_ints[i].ini_item, -1);
  
  for (i = 0; i < structln(prefs_shorts); i++)
    prefs_shorts[i].sUser_value = iniparser_getint(prefs, prefs_shorts[i].ini_item, -1);
  
  return true;
}

bool getHomePath() {
#ifdef __WIN32__
  /* We get the My Documents/Documents (Windows) directory here */
  /* In this case, the 5th argument can take a char instead of LPTSTR or TCHAR; these are all the same here */
  SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, root);
#else /* POSIX */
  strcat(prefs_root, getenv("HOME"));
#endif /* __WIN32__ */
 
  if (prefs_root == NULL) {
    fprintf(stderr, "Could not find home directory. Check your settings.\n");
    return false;
  }
  
  return true;
}

#ifdef __WIN32__
bool prefs_verifyPaths_win32(prefs_path search[]) {
  struct _stat buffer;
  /* /languages directory */
  
  /* /songs directory */
  
  /* /themes directory */
  
  return true;
}
#endif

bool prefs_verifyPaths() {
  if (getHomePath()) {
#ifdef __WIN32__
    prefs_verifyPaths_win32(search);
#else
  /* /languages directory */
  
  /* /songs directory */
  
  /* /themes directory */
#endif
  }
  else
    fprintf(stderr, "Fatal error finding home path.\n");
  
  return true;
}

bool prefs_verify() { /* This function only checks and fixes preferences; it does NOT read them */
  short ret;
  getHomePath();
  
  strcat(prefs_root, FREEBAND_PREFS_ROOT); /* Create paths to search for or make */
  strcat(prefs_languages, prefs_root);
  strcat(prefs_languages, "/languages");
  strcat(prefs_songs, prefs_root);
  strcat(prefs_songs, "/songs");
  strcat(prefs_themes, prefs_root);
  strcat(prefs_themes, "/themes");
  strcat(prefs_ini, prefs_root);
  strcat(prefs_ini, "/preferences.ini");
  
  struct stat buffer;
  
#ifdef __WIN32__
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

  /* Do we have a languages folder? */
  if ((ret = _stat(prefs_languages, &buffer)) != 0) { /* No? Create it */
    fprintf(stderr, "Unable to locate a Freeband languages directory. Creating one now...\n");
    
    if ((ret = _mkdir(prefs_languages)) != 0) {
      fprintf(stderr, "Unable to create %s directory. Check if you have permission.\n", prefs_songs);
      return false; /* Error! Do we have permission? */
    }
  }
  else {
#ifdef __DEBUG__
    fprintf(stdout, "Found languages directory: %s.\n", prefs_languages);
#endif
    languages_checkForINIs();
  }

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
    fileIO_copyFile("GameData/preferences.ini", prefs_ini);
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "Found preferences.ini file: %s.\nGetting preferences...\n", prefs_ini);
#endif
  
#else /* POSIX */

  
  /* Do we have a languages folder? */
  if ((ret = stat(prefs_languages, &buffer)) != 0) { /* No? Create it */
    fprintf(stderr, "Unable to locate a Freeband languages directory. Creating one now...\n");
    
    if ((ret = mkdir(prefs_languages, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0) {
      fprintf(stderr, "Unable to create %s directory. Check if you have permission.\n", prefs_songs);
      return false; /* Error! Do we have permission? */
    }
  }
  else {
#ifdef __DEBUG__
    fprintf(stdout, "Found languages directory: %s.\n", prefs_languages);
#endif
    languages_checkForINIs();
  }
  
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
    fileIO_copyFile("GameData/preferences.ini", prefs_ini);
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "Found preferences.ini file: %s.\nGetting preferences...\n", prefs_ini);
#endif
  
  languages_checkForINIs();
  
#endif

  return true; /* Checking for default preferences, songs and themes is handled in defaults.c */
}

bool prefs_load() {
  FILE *inifile;
#ifdef __WIN32__
  CFlag_s *pFlag;
#endif
  
  if ((prefs = iniparser_load(prefs_ini)) == NULL) {
    fprintf(stderr, "Error loading %s dictionary using iniparser.\n", prefs_ini);
    return false;
  }
  
  prefs_getBools(prefs);
  prefs_getChars(prefs);
  prefs_getInts(prefs);
  prefs_getKeys(prefs);
  
/*  inifile = fopen(prefs_ini, "w+");
  iniparser_dump_ini(prefs, inifile); /* Write a new INI, just in case settings are invalid and are being reset */
/*#ifdef __WIN32__
  fileIO_unix2dos(inifile); /* Convert to DOS format for Windows users */
/*#endif /* __WIN32__ */
  /*fclose(inifile);*/
  
  return true;
}
