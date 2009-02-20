#include "../freeband.h"
#include "keys.h"
#include "prefs.h"

prefs_Input_Keyboard_s prefs_Input_Keyboard[3];

/* Thanks to syntropy for this method */
typedef struct {
  char *key;
  int map;
} keymap_s;

static keymap_s specialkeys[] = {
  { "ESCAPE", SDLK_ESCAPE }, /* No shift keys are accepted */
  { "ESC", SDLK_ESCAPE },
  { "F1", SDLK_F1 },
  { "F2", SDLK_F2 },
  { "F3", SDLK_F3 },
  { "F4", SDLK_F4 },
  { "F5", SDLK_F5 },
  { "F6", SDLK_F6 },
  { "F7", SDLK_F7 },
  { "F8", SDLK_F8 },
  { "F9", SDLK_F9 },
  { "F10", SDLK_F10 },
  { "F11", SDLK_F11 },
  { "F12", SDLK_F12 },
  { "BACKSPACE", SDLK_BACKSPACE },
  { "TAB", SDLK_TAB },
  { "RETURN", SDLK_RETURN },
  { "ENTER", SDLK_RETURN },
  { "PAUSE", SDLK_PAUSE },
  { "SPACE", SDLK_SPACE },
  { "DELETE", SDLK_DELETE },
  { "LSHIFT", SDLK_LSHIFT },
  { "RSHIFT", SDLK_RSHIFT },
  { "LCTRL", SDLK_LCTRL },
  { "RCTRL", SDLK_RCTRL },
  { "PRINTSCREEN", SDLK_PRINT },
  { "UP", SDLK_UP },
  { "DOWN", SDLK_DOWN },
  { "LEFT", SDLK_LEFT },
  { "RIGHT", SDLK_RIGHT },
  { "INSERT", SDLK_INSERT },
  { "HOME", SDLK_HOME },
  { "END", SDLK_END },
  { "PAGEUP", SDLK_PAGEUP },
  { "PAGEDOWN", SDLK_PAGEDOWN },
  { "NP_0", SDLK_KP0 }, /* Number pad keys */
  { "NP_1", SDLK_KP1 },
  { "NP_2", SDLK_KP2 },
  { "NP_3", SDLK_KP3 },
  { "NP_4", SDLK_KP4 },
  { "NP_5", SDLK_KP5 },
  { "NP_6", SDLK_KP6 },
  { "NP_7", SDLK_KP7 },
  { "NP_8", SDLK_KP8 },
  { "NP_9", SDLK_KP9 },
  { "NP_.", SDLK_KP_PERIOD },
  { "NP_/", SDLK_KP_DIVIDE },
  { "NP_*", SDLK_KP_MULTIPLY },
  { "NP_-", SDLK_KP_MINUS },
  { "NP_=", SDLK_KP_EQUALS },
  { "NP_ENTER", SDLK_KP_ENTER }
};

/* Map string keys in the INI file to SDL equivalents */
int keys_mapKeystringToSDL(char *key) {
  int ckey = *(char*)key;
  int retkey = -1; /* Key we return */
  ushort i;
  
  if (strlen(key) == 1) {
    switch (ckey) {
      case 'A':
      case 'a':
        retkey = SDLK_a;
        break;
        
      case 'B':
      case 'b':
        retkey = SDLK_b;
        break;
        
      case 'C':
      case 'c':
        retkey = SDLK_c;
        break;
        
      case 'D':
      case 'd':
        retkey = SDLK_d;
        break;
        
      case 'E':
      case 'e':
        retkey = SDLK_e;
        break;
        
      case 'F':
      case 'f':
        retkey = SDLK_f;
        break;
        
      case 'G':
      case 'g':
        retkey = SDLK_g;
        break;
        
      case 'H':
      case 'h':
        retkey = SDLK_h;
        break;
        
      case 'I':
      case 'i':
        retkey = SDLK_i;
        break;
        
      case 'J':
      case 'j':
        retkey = SDLK_j;
        break;
        
      case 'K':
      case 'k':
        retkey = SDLK_k;
        break;
        
      case 'L':
      case 'l':
        retkey = SDLK_l;
        break;
        
      case 'M':
      case 'm':
        retkey = SDLK_m;
        break;
        
      case 'N':
      case 'n':
        retkey = SDLK_n;
        break;
        
      case 'O':
      case 'o':
        retkey = SDLK_o;
        break;
        
      case 'P':
      case 'p':
        retkey = SDLK_p;
        break;
        
      case 'Q':
      case 'q':
        retkey = SDLK_q;
        break;
        
      case 'R':
      case 'r':
        retkey = SDLK_r;
        break;
        
      case 'S':
      case 's':
        retkey = SDLK_s;
        break;
        
      case 'T':
      case 't':
        retkey = SDLK_t;
        break;
        
      case 'U':
      case 'u':
        retkey = SDLK_u;
        break;
        
      case 'V':
      case 'v':
        retkey = SDLK_v;
        break;
        
      case 'W':
      case 'w':
        retkey = SDLK_w;
        break;
        
      case 'X':
      case 'x':
        retkey = SDLK_x;
        break;
        
      case 'Y':
      case 'y':
        retkey = SDLK_y;
        break;
        
      case 'Z':
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
  }
  
  for (i = 0; i < sizeof(specialkeys)/(sizeof(specialkeys[0])); i++) {
    if (!strcasecmp(key, specialkeys[i].key)) {
      retkey = specialkeys[i].map;
    }
  }
  
#ifdef __DEBUG__
  fprintf(stdout, "keys_mapKeystringToSDL(): Mapped key string \"%s\" to SDL key %d (%#x).\n", key, retkey, retkey);
#endif

  return retkey;
}

void prefs_keys_get() {
  /* [Input_Keyboard1] is not possible to disable */
  if ((prefs_Input_Keyboard[0].disable_pick = iniparser_getboolean(prefs, "Input_Keyboard1:disable_pick", -1)) != 1)
    prefs_Input_Keyboard[0].disable_pick = false;
  else
    prefs_Input_Keyboard[0].disable_pick = true;
  prefs_Input_Keyboard[0].button_green = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_green", INIERROR));
  prefs_Input_Keyboard[0].button_red = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_red", INIERROR));
  prefs_Input_Keyboard[0].button_yellow = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_yellow", INIERROR));
  prefs_Input_Keyboard[0].button_blue = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_blue", INIERROR));
  prefs_Input_Keyboard[0].button_orange = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_orange", INIERROR));
  prefs_Input_Keyboard[0].button_pick_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_pick_up", INIERROR));
  prefs_Input_Keyboard[0].button_pick_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_pick_down", INIERROR));
  prefs_Input_Keyboard[0].button_start = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_start", INIERROR));
  prefs_Input_Keyboard[0].button_select = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_select", INIERROR));
  prefs_Input_Keyboard[0].button_direction_left = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_direction_left", INIERROR));
  prefs_Input_Keyboard[0].button_direction_right = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_direction_right", INIERROR));
  prefs_Input_Keyboard[0].button_direction_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_direction_down", INIERROR));
  prefs_Input_Keyboard[0].button_direction_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:button_direction_up", INIERROR));
  prefs_Input_Keyboard[0].whammy_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:whammy_down", INIERROR));
  prefs_Input_Keyboard[0].whammy_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:whammy_up", INIERROR));
  prefs_Input_Keyboard[0].star_power = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:star_power", INIERROR));
  prefs_Input_Keyboard[0].screenshot = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard1:screenshot", INIERROR));
  
  if ((prefs_Input_Keyboard[1].enabled = iniparser_getboolean(prefs, "Input_Keyboard2:enabled", -1)) != 1)
    prefs_Input_Keyboard[1].enabled = false;
  else { /* If it is enabled, we check for keys */
    prefs_Input_Keyboard[1].enabled = true;
    prefs_Input_Keyboard[1].button_green = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_green", INIERROR));
    prefs_Input_Keyboard[1].button_red = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_red", INIERROR));
    prefs_Input_Keyboard[1].button_yellow = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_yellow", INIERROR));
    prefs_Input_Keyboard[1].button_blue = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_blue", INIERROR));
    prefs_Input_Keyboard[1].button_orange = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_orange", INIERROR));
    prefs_Input_Keyboard[1].button_pick_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_pick_up", INIERROR));
    prefs_Input_Keyboard[1].button_pick_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_pick_down", INIERROR));
    prefs_Input_Keyboard[1].button_start = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_start", INIERROR));
    prefs_Input_Keyboard[1].button_select = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_select", INIERROR));
    prefs_Input_Keyboard[1].button_direction_left = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_direction_left", INIERROR));
    prefs_Input_Keyboard[1].button_direction_right = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_direction_right", INIERROR));
    prefs_Input_Keyboard[1].button_direction_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_direction_down", INIERROR));
    prefs_Input_Keyboard[1].button_direction_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:button_direction_up", INIERROR));
    prefs_Input_Keyboard[1].whammy_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:whammy_down", INIERROR));
    prefs_Input_Keyboard[1].whammy_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:whammy_up", INIERROR));
    prefs_Input_Keyboard[1].star_power = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:star_power", INIERROR));
    prefs_Input_Keyboard[1].screenshot = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard2:screenshot", INIERROR));
  }
  
  if ((prefs_Input_Keyboard[2].enabled = iniparser_getboolean(prefs, "Input_Keyboard3:enabled", -1)) != 1)
    prefs_Input_Keyboard[2].enabled = false;
  else { /* If it is enabled, we check for keys */
    prefs_Input_Keyboard[2].enabled = true;
    prefs_Input_Keyboard[2].button_green = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_green", INIERROR));
    prefs_Input_Keyboard[2].button_red = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_red", INIERROR));
    prefs_Input_Keyboard[2].button_yellow = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_yellow", INIERROR));
    prefs_Input_Keyboard[2].button_blue = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_blue", INIERROR));
    prefs_Input_Keyboard[2].button_orange = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_orange", INIERROR));
    prefs_Input_Keyboard[2].button_pick_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_pick_up", INIERROR));
    prefs_Input_Keyboard[2].button_pick_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_pick_down", INIERROR));
    prefs_Input_Keyboard[2].button_start = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_start", INIERROR));
    prefs_Input_Keyboard[2].button_select = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_select", INIERROR));
    prefs_Input_Keyboard[2].button_direction_left = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_direction_left", INIERROR));
    prefs_Input_Keyboard[2].button_direction_right = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_direction_right", INIERROR));
    prefs_Input_Keyboard[2].button_direction_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_direction_down", INIERROR));
    prefs_Input_Keyboard[2].button_direction_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:button_direction_up", INIERROR));
    prefs_Input_Keyboard[2].whammy_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:whammy_down", INIERROR));
    prefs_Input_Keyboard[2].whammy_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:whammy_up", INIERROR));
    prefs_Input_Keyboard[2].star_power = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:star_power", INIERROR));
    prefs_Input_Keyboard[2].screenshot = keys_mapKeystringToSDL(iniparser_getstring(prefs, "Input_Keyboard3:screenshot", INIERROR));
  }
  
  return;
}
