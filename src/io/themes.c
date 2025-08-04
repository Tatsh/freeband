#include "themes.h"
#include "freeband.h"
#include "prefs.h"

bool themes_default;
prefs_path theme_directory[255];

bool themes_loadDefaultTheme() {
  themes_path fonts[255];
  themes_path global[255];
  themes_path screenCharacters[255];
  themes_path screenDifficulty[255];
  themes_path screenInstruments[255];
  themes_path screenMain[255];
  themes_path screenGame[255];
  themes_path screenPause[255];
  themes_path screenSongs[255];

  strcat(theme_directory, prefs_themes);
  strcat("/default", theme_directory);

#ifdef _WIN32
#else
  /* Does the directory exist? */
  /* Does it have a metrics.ini file? If not, copy the file and report */
  /* If yes but certain settings are missing, copy default metrics.ini and report */
  /* Verify all fonts listed exist, and are valid to open; if not, exit and report error to user with specific font corrupted */
  /* If it is from the default theme, try copying the font first */
  /* Are all the required files present? If not, fallback to default theme's file */
  /* Verify all image files are valid to open; if not, exit and report error with specific file corrupted */
  /* If it is from the default theme, try copying the file first */
#endif

  return true;
}

bool themes_loadTheme(char *theme) {
  themes_path fonts[255];
  themes_path global[255];
  themes_path screenCharacters[255];
  themes_path screenDifficulty[255];
  themes_path screenInstruments[255];
  themes_path screenMain[255];
  themes_path screenGame[255];
  themes_path screenPause[255];
  themes_path screenSongs[255];

  if (strncmp("default", theme, 7) == 0) {
    if (themes_loadDefaultTheme())
      return true;
    else
      fprintf(stderr, "Error loading default theme.\n");
  }

  strcat(theme_directory, prefs_themes);
  strcat("/", theme_directory);
  strcat(theme, theme_directory);

#ifdef _WIN32
  /* Here we use functions like _stat() instead of stat() etc */
#else
  /* Does the directory exist? */
  /* Does it have a metrics.ini file? If not, use default theme and report error to user */
  /* If yes but certain settings are missing, use default theme and report error to user */
  /* Verify all fonts listed exist, and are valid to open; if not, exit and report error to user with specific font corrupted */
  /* If it is from the default theme, try copying the font first */
  /* Are all the required files present? If not, fallback to default theme's file */
  /* Verify all image files are valid to open; if not, exit and report error with specific file corrupted */
  /* If it is from the default theme, try copying the file first */
#endif

  return true;
}
