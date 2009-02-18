#ifndef PAUSE_H
#define PAUSE_H

#define PAUSE_MENU_ITEMS_HT   0.14f
#define PAUSE_MENU_ITEMS_OFFSET -0.26 /* How far away from 'PAUSED' text this starts at */
#define PAUSE_MENU_ITEMS_DIFF 0.11 /* How close the menu items are */

typedef struct changeDifficulty {
  bool easy;
  bool medium;
  bool hard;
  bool expert;
} pause_difficultyState_s;

typedef struct pauseItemRestart {
  bool yes;
  bool no;
} pause_restartState_s;

typedef struct leftyModeChecked_t {
  bool checked;
} pause_leftyMode_s;

typedef struct pauseItemQ {
  bool new_song;
  bool main_menu;
} pause_quitState_s;

typedef struct pauseItem {
  bool resume;
  bool restart;
  bool lefty_mode;
  bool change_difficulty;
  bool change_mic_volume;
  bool quit;
  
  pause_difficultyState_s difficultyState;
  pause_restartState_s restartState;
  pause_leftyMode_s leftyModeChecked;
  pause_quitState_s quitState;
} pause_fMenuState_s;

extern pause_fMenuState_s pause_menuState;

extern bool gamePaused;

bool screenPause_buffer();
GLvoid screenPause();

#endif
