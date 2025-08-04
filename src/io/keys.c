#include "keys.h"
#include "freeband.h"
#include "nonstd.h"
#include "prefs.h"

static keymap_s specialkeys[] = {{"ESCAPE", SDLK_ESCAPE}, /* No shift keys are accepted */
                                 {"ESC", SDLK_ESCAPE},
                                 {"F1", SDLK_F1},
                                 {"F2", SDLK_F2},
                                 {"F3", SDLK_F3},
                                 {"F4", SDLK_F4},
                                 {"F5", SDLK_F5},
                                 {"F6", SDLK_F6},
                                 {"F7", SDLK_F7},
                                 {"F8", SDLK_F8},
                                 {"F9", SDLK_F9},
                                 {"F10", SDLK_F10},
                                 {"F11", SDLK_F11},
                                 {"F12", SDLK_F12},
                                 {"BACKSPACE", SDLK_BACKSPACE},
                                 {"TAB", SDLK_TAB},
                                 {"RETURN", SDLK_RETURN},
                                 {"ENTER", SDLK_RETURN},
                                 {"PAUSE", SDLK_PAUSE},
                                 {"SPACE", SDLK_SPACE},
                                 {"DELETE", SDLK_DELETE},
                                 {"LSHIFT", SDLK_LSHIFT},
                                 {"RSHIFT", SDLK_RSHIFT},
                                 {"LCTRL", SDLK_LCTRL},
                                 {"RCTRL", SDLK_RCTRL},
                                 {"PRINTSCREEN", SDLK_PRINT},
                                 {"UP", SDLK_UP},
                                 {"DOWN", SDLK_DOWN},
                                 {"LEFT", SDLK_LEFT},
                                 {"RIGHT", SDLK_RIGHT},
                                 {"INSERT", SDLK_INSERT},
                                 {"HOME", SDLK_HOME},
                                 {"END", SDLK_END},
                                 {"PAGEUP", SDLK_PAGEUP},
                                 {"PAGEDOWN", SDLK_PAGEDOWN},
                                 {"NP_0", SDLK_KP0}, /* Number pad keys */
                                 {"NP_1", SDLK_KP1},
                                 {"NP_2", SDLK_KP2},
                                 {"NP_3", SDLK_KP3},
                                 {"NP_4", SDLK_KP4},
                                 {"NP_5", SDLK_KP5},
                                 {"NP_6", SDLK_KP6},
                                 {"NP_7", SDLK_KP7},
                                 {"NP_8", SDLK_KP8},
                                 {"NP_9", SDLK_KP9},
                                 {"NP_.", SDLK_KP_PERIOD},
                                 {"NP_/", SDLK_KP_DIVIDE},
                                 {"NP_*", SDLK_KP_MULTIPLY},
                                 {"NP_-", SDLK_KP_MINUS},
                                 {"NP_=", SDLK_KP_EQUALS},
                                 {"NP_ENTER", SDLK_KP_ENTER}};

keyPrefs_s keyPrefs[] =
  {/* To the right are the default values to use in case of a botched preferences file */
   {"operator", SDLK_F12, SDLK_F12}, /* Keyboard 1 only */
   {"enabled", false, false},        /* Keyboards 2 and 3 only */
   {"disable_pick", true, true},
   {"button_green", SDLK_F1, SDLK_F1},
   {"button_red", SDLK_F2, SDLK_F2},
   {"button_yellow", SDLK_F3, SDLK_F3},
   {"button_blue", SDLK_F4, SDLK_F4},
   {"button_orange", SDLK_F5, SDLK_F5},
   {"button_pick_up", SDLK_UP, SDLK_UP},
   {"button_pick_down", SDLK_DOWN, SDLK_DOWN},
   {"button_start", SDLK_RETURN, SDLK_RETURN},
   {"button_select", SDLK_BACKQUOTE, SDLK_BACKQUOTE},
   {"button_direction_left", SDLK_LEFT, SDLK_LEFT},
   {"button_direction_right", SDLK_RIGHT, SDLK_RIGHT},
   {"button_direction_up", SDLK_UP, SDLK_UP},
   {"button_direction_down", SDLK_DOWN, SDLK_DOWN},
   {"whammy_down", SDLK_2, SDLK_2},
   {"whammy_up", SDLK_3, SDLK_3},
   {"star_power", SDLK_5, SDLK_5},
   {"screenshot", SDLK_PRINT, SDLK_PRINT}};

/* Map string keys in the INI file to SDL equivalents */
int keys_mapKeystringToSDL(char *key) {
  int ckey = *(char *)key;
  int retkey = -1; /* Key we return */
  ushort i;

  if (strlen(key) == 1) {
    switch (ckey) {
      case 'a': /* INI parser does not ever return an upper-case value */
        retkey = SDLK_a;
        break;

      case 'b':
        retkey = SDLK_b;
        break;

      case 'c':
        retkey = SDLK_c;
        break;

      case 'd':
        retkey = SDLK_d;
        break;

      case 'e':
        retkey = SDLK_e;
        break;

      case 'f':
        retkey = SDLK_f;
        break;

      case 'g':
        retkey = SDLK_g;
        break;

      case 'h':
        retkey = SDLK_h;
        break;

      case 'i':
        retkey = SDLK_i;
        break;

      case 'j':
        retkey = SDLK_j;
        break;

      case 'k':
        retkey = SDLK_k;
        break;

      case 'l':
        retkey = SDLK_l;
        break;

      case 'm':
        retkey = SDLK_m;
        break;

      case 'n':
        retkey = SDLK_n;
        break;

      case 'o':
        retkey = SDLK_o;
        break;

      case 'p':
        retkey = SDLK_p;
        break;

      case 'q':
        retkey = SDLK_q;
        break;

      case 'r':
        retkey = SDLK_r;
        break;

      case 's':
        retkey = SDLK_s;
        break;

      case 't':
        retkey = SDLK_t;
        break;

      case 'u':
        retkey = SDLK_u;
        break;

      case 'v':
        retkey = SDLK_v;
        break;

      case 'w':
        retkey = SDLK_w;
        break;

      case 'x':
        retkey = SDLK_x;
        break;

      case 'y':
        retkey = SDLK_y;
        break;

      case 'z':
        retkey = SDLK_z;
        break;

      case '1':
        retkey = SDLK_1;
        break;

      case '2':
        retkey = SDLK_2;
        break;

      case '3':
        retkey = SDLK_3;
        break;

      case '4':
        retkey = SDLK_4;
        break;

      case '5':
        retkey = SDLK_5;
        break;

      case '6':
        retkey = SDLK_6;
        break;

      case '7':
        retkey = SDLK_7;
        break;

      case '8':
        retkey = SDLK_8;
        break;

      case '9':
        retkey = SDLK_9;
        break;

      case '0':
        retkey = SDLK_0;
        break;

      case '\'':
        retkey = SDLK_QUOTE;
        break;

      case '.':
        retkey = SDLK_PERIOD;
        break;

      case '/':
        retkey = SDLK_SLASH;
        break;

      case ';':
        retkey = SDLK_SEMICOLON;
        break;

      case '=':
        retkey = SDLK_EQUALS;
        break;

      case '[':
        retkey = SDLK_LEFTBRACKET;
        break;

      case ']':
        retkey = SDLK_RIGHTBRACKET;
        break;

      case '\\':
        retkey = SDLK_BACKSLASH;
        break;

      case '`':
        retkey = SDLK_BACKQUOTE;
        break;

      case -1:
        retkey = KEYS_NOKEY; /* Key is disabled */

      default: /* Go to the for loop below */
        break;
    }
  } else {
    for (i = 0; i < structln(specialkeys); i++) {
      if (!strcasecmp(key, specialkeys[i].key)) {
        retkey = specialkeys[i].map;
      }
    }
  }

#ifndef NDEBUG
  if (retkey != KEYS_NOKEY)
    fprintf(stdout,
            "keys_mapKeystringToSDL(): Mapped key string \"%s\" to SDL key %d (%#x).\n",
            key,
            retkey,
            retkey);
  else
    fprintf(stdout, "keys_mapKeystringToSDL(): Mapped key string \"%s\" to no key.", key);
#endif

  return retkey;
}

void prefs_getKeys(dictionary *prefs) {
  const int buf_size = 1024;
  char *iniItem = calloc(buf_size, 1);
  ushort i;

  /* Get data for keyboard 1; it is always enabled */
  for (i = 0; i < structln(keyPrefs); i++) {
    strcat(iniItem, "Input_Keyboard1:");
    strcat(iniItem, keyPrefs[i].iniItem);
    iniparser_getint(prefs, iniItem, keyPrefs[i].default_value);
  }

  /* Keyboards 2 and 3 only if enabled */
  memset(iniItem, 0, buf_size);
  for (i = 0; i < structln(keyPrefs); i++) {
    strcat(iniItem, "Input_Keyboard2:");
    strcat(iniItem, keyPrefs[i].iniItem);
    iniparser_getint(prefs, iniItem, keyPrefs[i].default_value);
  }

  memset(iniItem, 0, buf_size);
  for (i = 0; i < structln(keyPrefs); i++) {
    strcat(iniItem, "Input_Keyboard3:");
    strcat(iniItem, keyPrefs[i].iniItem);
    iniparser_getint(prefs, iniItem, keyPrefs[i].default_value);
  }

  free(iniItem);
}
