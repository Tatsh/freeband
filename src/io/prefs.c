#include "../freeband.h"
#include "../graphics/graphics.h"
#include "../screens/difficulty.h"
#include "../screens/instruments.h"
#include "fileio.h"
#include "languages.h"
#include "prefs.h"
#include "keys.h"

dictionary *prefs;

prefs_path prefs_root[255];
prefs_path prefs_languages[255];
prefs_path prefs_songs[255];
prefs_path prefs_themes[255];
prefs_path prefs_ini[255];

prefs_Freeband_s prefs_Freeband;
prefs_Audio_s prefs_Audio;
prefs_Graphics_s prefs_Graphics;
prefs_Input_Keyboard_s prefs_Input_Keyboard1;
prefs_Input_Keyboard_s prefs_Input_Keyboard2;
prefs_Input_Keyboard_s prefs_Input_Keyboard3;
prefs_Input_Joystick_s prefs_Input_Joystick1;
prefs_Input_Joystick_s prefs_Input_Joystick2;
prefs_Input_Joystick_s prefs_Input_Joystick3;

bool prefs_verify() { /* This function only checks and fixes preferences; it does NOT read them */
  short ret;
  
#ifdef __WIN32__
  /* We get the $HOME or %%HOME (Windows) environment variable */
  /* In this case, the 5th argument can take a char instead of LPTSTR or TCHAR; these are all the same here */
  SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, prefs_root);
  
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
  strcat(prefs_languages, prefs_root);
  strcat(prefs_languages, "/languages");
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
  prefs_Graphics.ar4x3 = prefs_Graphics.ar16x9 = prefs_Graphics.ar16x10 = false;
  
  if ((prefs = iniparser_load(prefs_ini)) == NULL) {
    fprintf(stderr, "Error loading %s dictionary using iniparser.\n", prefs_ini);
    return false;
  }

  /* [Freeband] */
  prefs_Freeband.language = iniparser_getstring(prefs, "Freeband:language", INIERROR);
  if (strcmp(INIERROR, prefs_Freeband.language) == 0) { /* Verify language file exists later */
    prefs_Freeband.language = "en_GB"; /* Force to default if there is no language in the file */
    prefs_Freeband.language_u = en_GB;
  }
  else if (strncmp("en_GB", prefs_Freeband.language, 4) == 0)
    prefs_Freeband.language_u = en_GB;
  else if (strncmp("pl_PL", prefs_Freeband.language, 4) == 0)
    prefs_Freeband.language_u = pl_PL;
  else /* If language is not recognised, force to default */
    prefs_Freeband.language_u = en_GB;
  languages_loadLanguage(prefs_Freeband.language_u);
  
  if ((prefs_Freeband.enable_demo = iniparser_getboolean(prefs, "Freeband:enable_demo", -1)) != 1)
    prefs_Freeband.enable_demo = false;
  else
    prefs_Freeband.enable_demo = true;

  prefs_Freeband.theme = iniparser_getstring(prefs, "Freeband:theme", INIERROR);
  if (strcmp(INIERROR, prefs_Freeband.theme) == 0) /* We will verify the folder exists later */
    prefs_Freeband.theme = "default";
  /*themes_loadTheme(prefs_Freeband.theme);*/
  
  prefs_Freeband.default_instrument = iniparser_getstring(prefs, "Freeband:default_instrument", INIERROR);
  if (strcmp(INIERROR, prefs_Freeband.default_instrument) == 0)
    prefs_Freeband.default_instrument = "guitar";
  if (strncmp("guitar", prefs_Freeband.default_instrument, 6) == 0) /* This is for if default_instrument="fioejaiofej" for example */
    prefs_Freeband.default_instrument_u = INSTRUMENT_GUITAR;
  else if (strncmp("bass", prefs_Freeband.default_instrument, 4) == 0)
    prefs_Freeband.default_instrument_u = INSTRUMENT_BASS;
  else if (strncmp("drums", prefs_Freeband.default_instrument, 5) == 0)
    prefs_Freeband.default_instrument_u = INSTRUMENT_DRUMS;
  else if (strncmp("vocals", prefs_Freeband.default_instrument, 6) == 0)
    prefs_Freeband.default_instrument_u = INSTRUMENT_VOCALS;
  else
    prefs_Freeband.default_instrument_u = INSTRUMENT_GUITAR;
  current_instrument = prefs_Freeband.default_instrument_u;
  
  prefs_Freeband.default_difficulty = iniparser_getstring(prefs, "Freeband:default_difficulty", INIERROR);
  if (strcmp(INIERROR, prefs_Freeband.default_difficulty) == 0)
    prefs_Freeband.default_difficulty = "easy";
  if (strcmp("easy", prefs_Freeband.default_difficulty) == 0)
    prefs_Freeband.default_difficulty_u = DIFFICULTY_EASY;
  else if (strcmp("medium", prefs_Freeband.default_difficulty) == 0)
    prefs_Freeband.default_difficulty_u = DIFFICULTY_MEDIUM;
  else if (strcmp("hard", prefs_Freeband.default_difficulty) == 0)
    prefs_Freeband.default_difficulty_u = DIFFICULTY_HARD;
  else if (strcmp("expert", prefs_Freeband.default_difficulty) == 0)
    prefs_Freeband.default_difficulty_u = DIFFICULTY_EXPERT;
  else
    prefs_Freeband.default_difficulty_u = DIFFICULTY_EASY;
  current_difficulty = prefs_Freeband.default_difficulty_u;
  
  prefs_Freeband.difficulty_judge = iniparser_getint(prefs, "Freeband:difficulty_judge", 11);
  if (prefs_Freeband.difficulty_judge < 1 || prefs_Freeband.difficulty_judge > 10) {
    /* iniparser_set(prefs, "Freeband:difficulty_judge", "5"); Requires patched iniparser.h */
    fprintf(stderr, "Invalid judge setting. Using default: 5\n");
    prefs_Freeband.difficulty_judge = 5;
  }
  
  if ((prefs_Freeband.theming_mode = iniparser_getboolean(prefs, "Freeband:theming_mode", -1)) != 1)
    prefs_Freeband.theming_mode = false;
  else
    prefs_Freeband.theming_mode = true;

  /* [Graphics] */
  prefs_Graphics.width = iniparser_getint(prefs, "Graphics:width", -1);
  prefs_Graphics.height = iniparser_getint(prefs, "Graphics:height", -1);
  prefs_Graphics.bpp = iniparser_getint(prefs, "Graphics:bpp", -1);
  prefs_Graphics.aspect_ratio = iniparser_getstring(prefs, "Graphics:aspect_ratio", INIERROR);
  if (strncmp(four_three, prefs_Graphics.aspect_ratio, 3) == 0)
    prefs_Graphics.ar4x3 = true;
  else if (strncmp(sixteen_nine, prefs_Graphics.aspect_ratio, 3) == 0)
    prefs_Graphics.ar16x9 = true;
  else if (strncmp(sixteen_ten, prefs_Graphics.aspect_ratio, 4) == 0)
    prefs_Graphics.ar16x10 = true;
  else
    prefs_Graphics.ar4x3 = true;
  if ((prefs_Graphics.display_band = iniparser_getboolean(prefs, "Graphics:display_band", -1)) != 1)
    prefs_Graphics.display_band = false;
  else
    prefs_Graphics.display_band = true;
  if ((prefs_Graphics.display_venue = iniparser_getboolean(prefs, "Graphics:display_venue", -1)) != 1)
    prefs_Graphics.display_venue = false;
  else
    prefs_Graphics.display_venue = true;
  if ((prefs_Graphics.fullscreen = iniparser_getboolean(prefs, "Graphics:fullscreen", -1)) != 1)
    prefs_Graphics.fullscreen = false;
  else
    prefs_Graphics.fullscreen = true;

#ifdef __DEBUG__
  fprintf(stdout, "\n[Freeband]\n");
  fprintf(stdout, "language=%s (%#x)\n", prefs_Freeband.language, prefs_Freeband.language_u);
  fprintf(stdout, "enable_demo=%s\n", prefs_Freeband.enable_demo ? "true" : "false");
  fprintf(stdout, "theme=%s\n", prefs_Freeband.theme);
  fprintf(stdout, "default_instrument=%s (%#x)\n", prefs_Freeband.default_instrument, prefs_Freeband.default_instrument_u);
  fprintf(stdout, "default_difficulty=%s (%#x)\n", prefs_Freeband.default_difficulty, prefs_Freeband.default_difficulty_u);
  fprintf(stdout, "difficulty_judge=%d\n", prefs_Freeband.difficulty_judge);
  fprintf(stdout, "theming_mode=%s\n\n", prefs_Freeband.theming_mode ? "true" : "false");
  
  fprintf(stdout, "[Graphics]\n");
  fprintf(stdout, "width=%d\n", prefs_Graphics.width);
  fprintf(stdout, "height=%d\n", prefs_Graphics.height);
  fprintf(stdout, "bpp=%d (%d-bit)\n", prefs_Graphics.bpp, prefs_Graphics.bpp);
  fprintf(stdout, "aspect_ratio=%s\n", prefs_Graphics.aspect_ratio);
  fprintf(stdout, "display_band=%s\n", prefs_Graphics.display_band ? "true" : "false");
  fprintf(stdout, "display_venue=%s\n", prefs_Graphics.display_venue ? "true" : "false");
  fprintf(stdout, "fullscreen=%s\n", prefs_Graphics.fullscreen ? "true" : "false");
  
  fprintf(stdout, "\n");
#endif
  
  return true;
}
