#include "../freeband.h"
#include "../nonstd.h"
#include "keys.h"
#include "prefs.h"

#define INPUTKEYBOARD "Input_Keyboard"

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
  if (retkey != KEYS_NOKEY)
    fprintf(stdout, "keys_mapKeystringToSDL(): Mapped key string \"%s\" to SDL key %d (%#x).\n", key, retkey, retkey);
  else
    fprintf(stdout, "keys_mapKeystringToSDL(): Mapped key string \"%s\" to no key.", key);
#endif

  return retkey;
}

void prefs_keys_get() {
  char iniPref[100];
  char buf[1];
  ushort i;
  
  for (i = 0; i < 3; i++) {
    itoa(i + 1, buf); /* Convert int to string, not a standard C function; void */
    
#ifdef __DEBUG__
    iniPref[0] = '\0';
    strcat(iniPref, INPUTKEYBOARD);
    strcat(iniPref, buf);
    fprintf(stdout, "Getting [%s] preferences from INI...\n", iniPref);
#endif
    
    if (i == 0) {
      iniPref[0] = '\0'; /* Reset string */
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":operator");
      prefs_Input_Keyboard[i].operator = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR)); /* Only on keyboard 1 */
    }
    
    if (i > 0) {
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":enabled");
      if ((prefs_Input_Keyboard[i].enabled = iniparser_getboolean(prefs, iniPref, -1)) != 1)
        prefs_Input_Keyboard[i].enabled = false;
      else
        prefs_Input_Keyboard[i].enabled = true;
      
#ifdef __DEBUG__
      fprintf(stdout, "  Keyboard %d is disabled.\n", i + 1); /* Continuation from above */
#endif
      
      if (prefs_Input_Keyboard[i].enabled) {
        strcat(iniPref, ":disable_pick");
        if ((prefs_Input_Keyboard[i].disable_pick = iniparser_getboolean(prefs, iniPref, -1)) != 1)
          prefs_Input_Keyboard[i].disable_pick = false;
        else
          prefs_Input_Keyboard[i].disable_pick = true;
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_green");
        prefs_Input_Keyboard[i].button_green = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_red");
        prefs_Input_Keyboard[i].button_red = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_yellow");
        prefs_Input_Keyboard[i].button_yellow = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_blue");
        prefs_Input_Keyboard[i].button_blue = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_orange");
        prefs_Input_Keyboard[i].button_orange = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_pick_up");
        prefs_Input_Keyboard[i].button_pick_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_pick_down");
        prefs_Input_Keyboard[i].button_pick_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_start");
        prefs_Input_Keyboard[i].button_start = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_select");
        prefs_Input_Keyboard[i].button_select = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_direction_left");
        prefs_Input_Keyboard[i].button_direction_left = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_direction_right");
        prefs_Input_Keyboard[i].button_direction_right = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_direction_down");
        prefs_Input_Keyboard[i].button_direction_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":button_direction_up");
        prefs_Input_Keyboard[i].button_direction_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":whammy_down");
        prefs_Input_Keyboard[i].whammy_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":whammy_up");
        prefs_Input_Keyboard[i].whammy_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        iniPref[0] = '\0';
        strcat(iniPref, INPUTKEYBOARD);
        strcat(iniPref, buf);
        strcat(iniPref, ":star_power");
        prefs_Input_Keyboard[i].star_power = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
        prefs_Input_Keyboard[i].operator = KEYS_NOKEY;
      }
    }
    else { /* [Input_Keyboard1] is not possible to disable for obvious reasons */
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":disable_pick");
      if ((prefs_Input_Keyboard[i].disable_pick = iniparser_getboolean(prefs, iniPref, -1)) != 1)
        prefs_Input_Keyboard[i].disable_pick = false;
      else
        prefs_Input_Keyboard[i].disable_pick = true;
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_green");
      prefs_Input_Keyboard[i].button_green = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_red");
      prefs_Input_Keyboard[i].button_red = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_yellow");
      prefs_Input_Keyboard[i].button_yellow = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_blue");
      prefs_Input_Keyboard[i].button_blue = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_orange");
      prefs_Input_Keyboard[i].button_orange = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_pick_up");
      prefs_Input_Keyboard[i].button_pick_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_pick_down");
      prefs_Input_Keyboard[i].button_pick_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_start");
      prefs_Input_Keyboard[i].button_start = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_select");
      prefs_Input_Keyboard[i].button_select = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_direction_left");
      prefs_Input_Keyboard[i].button_direction_left = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_direction_right");
      prefs_Input_Keyboard[i].button_direction_right = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_direction_down");
      prefs_Input_Keyboard[i].button_direction_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":button_direction_up");
      prefs_Input_Keyboard[i].button_direction_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":whammy_down");
      prefs_Input_Keyboard[i].whammy_down = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":whammy_up");
      prefs_Input_Keyboard[i].whammy_up = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
      
      iniPref[0] = '\0';
      strcat(iniPref, INPUTKEYBOARD);
      strcat(iniPref, buf);
      strcat(iniPref, ":star_power");
      prefs_Input_Keyboard[i].star_power = keys_mapKeystringToSDL(iniparser_getstring(prefs, iniPref, INIERROR));
    }
  }
  
  return;
}
