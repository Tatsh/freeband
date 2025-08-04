#include "languages.h"
#include "fileio.h"
#include "freeband.h"
#include "prefs.h"

prefs_path languageIni[255];

languageStrings_screenMain_s languageStrings_screenMain;
languageStrings_screenFooter_s languageStrings_screenFooter;
languageStrings_screenInstruments_s languageStrings_screenInstruments;
languageStrings_screenSongs_s languageStrings_screenSongs;
languageStrings_screenDifficulty_s languageStrings_screenDifficulty;
languageStrings_screenPause_s languageStrings_screenPause;

dictionary *lang_d;

bool languages_loadLanguage(ushort lang) {
  strcat(languageIni, prefs_languages);

  switch (lang) {
    case en_GB:
      strcat(languageIni, "/en_GB.ini");
      if ((lang_d = iniparser_load(languageIni)) == NULL) {
        fprintf(stderr, "Error loading %s dictionary using iniparser.\n", languageIni);
        return false;
      }
#ifndef NDEBUG
      else
        fprintf(
          stdout, "Successfully opened English-Commonwealth language file: %s.\n", languageIni);
#endif
      break;

#ifdef __LANG_PL_PL__
    case pl_PL:
      strcat(languageIni, "/pl_PL.ini");
      if ((lang_d = iniparser_load(languageIni)) == NULL) {
        fprintf(stderr, "Error loading %s dictionary using iniparser.\n", languageIni);
        return false;
      }
#ifndef NDEBUG
      else
        fprintf(stdout, "Successfully opened Polish language file: %s.\n", languageIni);
#endif
      break;
#endif /* __LANG_PL_PL__ */

    default:
      break;
  }

  /* screenMain */
  languageStrings_screenMain.single_player =
    iniparser_getstring(lang_d, "screenMain:single_player", INIERROR);
  languageStrings_screenMain.multiplayer =
    iniparser_getstring(lang_d, "screenMain:multiplayer", INIERROR);
  languageStrings_screenMain.online = iniparser_getstring(lang_d, "screenMain:online", INIERROR);
  languageStrings_screenMain.options = iniparser_getstring(lang_d, "screenMain:options", INIERROR);
  languageStrings_screenMain.quit = iniparser_getstring(lang_d, "screenMain:quit", INIERROR);

  /* screenFooter */
  languageStrings_screenFooter.select =
    iniparser_getstring(lang_d, "screenFooter:select", INIERROR);
  languageStrings_screenFooter.back = iniparser_getstring(lang_d, "screenFooter:back", INIERROR);
  languageStrings_screenFooter.up_down =
    iniparser_getstring(lang_d, "screenFooter:up_down", INIERROR);

  /* screenInstruments */
  languageStrings_screenInstruments.header =
    iniparser_getstring(lang_d, "screenInstruments:header", INIERROR);
  languageStrings_screenInstruments.header_multiplayer =
    iniparser_getstring(lang_d, "screenInstruments:header_multiplayer", INIERROR);
  languageStrings_screenInstruments.guitar =
    iniparser_getstring(lang_d, "screenInstruments:guitar", INIERROR);
  languageStrings_screenInstruments.bass =
    iniparser_getstring(lang_d, "screenInstruments:bass", INIERROR);
  languageStrings_screenInstruments.drums =
    iniparser_getstring(lang_d, "screenInstruments:drums", INIERROR);
  languageStrings_screenInstruments.vocals =
    iniparser_getstring(lang_d, "screenInstruments:vocals", INIERROR);

  /* screenCharacters */

  /* screenSongs */
  languageStrings_screenSongs.header = iniparser_getstring(lang_d, "screenSongs:header", INIERROR);
  languageStrings_screenSongs.sort_by_tier =
    iniparser_getstring(lang_d, "screenSongs:sort_by_tier", INIERROR);
  languageStrings_screenSongs.sort_title_AZ =
    iniparser_getstring(lang_d, "screenSongs:sort_title_AZ", INIERROR);
  languageStrings_screenSongs.sort_artist_AZ =
    iniparser_getstring(lang_d, "screenSongs:sort_artist_AZ", INIERROR);
  /*if (strcmp(INIERROR, languageStrings_screenSongs.sort_bpm = iniparser_getstring(lang_d, "screenSongs:sort_bpm", INIERROR)) != 0)
    fprintf(stderr, "Error"); One way to check for errors */
  languageStrings_screenSongs.sort_bpm =
    iniparser_getstring(lang_d, "screenSongs:sort_bpm", INIERROR);

  /* screenDifficulty */
  languageStrings_screenDifficulty.header =
    iniparser_getstring(lang_d, "screenDifficulty:header", INIERROR);
  languageStrings_screenDifficulty.header_multiplayer =
    iniparser_getstring(lang_d, "screenDifficulty:header_multiplayer", INIERROR);
  languageStrings_screenDifficulty.easy =
    iniparser_getstring(lang_d, "screenDifficulty:easy", INIERROR);
  languageStrings_screenDifficulty.medium =
    iniparser_getstring(lang_d, "screenDifficulty:medium", INIERROR);
  languageStrings_screenDifficulty.hard =
    iniparser_getstring(lang_d, "screenDifficulty:hard", INIERROR);
  languageStrings_screenDifficulty.expert =
    iniparser_getstring(lang_d, "screenDifficulty:expert", INIERROR);

  /* screenPause */
  languageStrings_screenPause.header = iniparser_getstring(lang_d, "screenPause:header", INIERROR);
  languageStrings_screenPause.player_1 =
    iniparser_getstring(lang_d, "screenPause:player_1", INIERROR);
  languageStrings_screenPause.player_2 =
    iniparser_getstring(lang_d, "screenPause:player_2", INIERROR);
  languageStrings_screenPause.player_3 =
    iniparser_getstring(lang_d, "screenPause:player_3", INIERROR);
  languageStrings_screenPause.player_4 =
    iniparser_getstring(lang_d, "screenPause:player_4", INIERROR);
  languageStrings_screenPause.resume = iniparser_getstring(lang_d, "screenPause:resume", INIERROR);
  languageStrings_screenPause.resume_timer =
    iniparser_getstring(lang_d, "screenPause:resume_timer", INIERROR);
  languageStrings_screenPause.restart =
    iniparser_getstring(lang_d, "screenPause:restart", INIERROR);
  languageStrings_screenPause.lefty_mode =
    iniparser_getstring(lang_d, "screenPause:lefty_mode", INIERROR);
  languageStrings_screenPause.change_difficulty =
    iniparser_getstring(lang_d, "screenPause:change_difficulty", INIERROR);
  languageStrings_screenPause.adjust_microphone_volume =
    iniparser_getstring(lang_d, "screenPause:adjust_microphone_volume", INIERROR);
  languageStrings_screenPause.quit = iniparser_getstring(lang_d, "screenPause:quit", INIERROR);
  languageStrings_screenPause.new_song =
    iniparser_getstring(lang_d, "screenPause:new_song", INIERROR);
  languageStrings_screenPause.main_menu =
    iniparser_getstring(lang_d, "screenPause:main_menu", INIERROR);

  return true;
}

void languages_checkForINIs() {
  langINI_path checkINI[255];
  ushort ret;

  checkINI[0] = '\0'; /* Windows prefers it this way */

  strcat(checkINI, prefs_languages);
  strcat(checkINI, "/en_GB.ini");

#ifdef _WIN32
  struct _stat buffer;

  if ((ret = _stat(checkINI, &buffer)) != 0) {
    fprintf(stderr, "Unable to locate %s language file. Copying now...\n", checkINI);
    fileIO_copyFile("languages/en_GB.ini", checkINI);
  }
#ifndef NDEBUG
  else
    fprintf(stdout, "Found %s language file.\n", checkINI);
#endif

#ifdef __WIN32_LANG_PL_PL__
  checkINI[0] = '\0'; /* Reset */
  strcat(checkINI, prefs_languages);
  strcat(checkINI, "/pl_PL.ini");

  if ((ret = _stat(checkINI, &buffer)) != 0) {
    fprintf(stderr, "Unable to locate %s language file. Copying now...\n", checkINI);
    fileIO_copyFile("languges/pl_PL.ini", checkINI);
  }
#ifndef NDEBUG
  else
    fprintf(stdout, "Found %s language file.\n", checkINI);
#endif

#endif /* __WIN32_LANG_PL_PL__ */

#else /* POSIX */
  struct stat buffer;

  if ((ret = stat(checkINI, &buffer)) != 0) {
    fprintf(stderr, "Unable to locate %s language file. Copying now...\n", checkINI);
    fileIO_copyFile("languages/en_GB.ini", checkINI);
  }
#ifndef NDEBUG
  else
    fprintf(stdout, "Found %s language file.\n", checkINI);
#endif

#ifdef __LANG_PL_PL__ /* May seem redundant but this is easier for now */
  checkINI[0] = '\0'; /* Reset */
  strcat(checkINI, prefs_languages);
  strcat(checkINI, "/pl_PL.ini");

  if ((ret = stat(checkINI, &buffer)) != 0) {
    fprintf(stderr, "Unable to locate %s language file. Copying now...\n", checkINI);
    fileIO_copyFile("languages/pl_PL.ini", checkINI);
  }
#endif                /* __LANG_PL_PL__ */

#endif /* POSIX */
}
