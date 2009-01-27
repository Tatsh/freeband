#ifndef PAUSE_H
#define PAUSE_H

#define PAUSE_MENU_ITEMS_HT   0.18f
#define PAUSE_MENU_ITEMS_OFFSET -0.25
#define PAUSE_MENU_ITEMS_DIFF 0.15

#define en_paused             "PAUSED"

#define en_resume             "RESUME"
#define en_restart            "RESTART"
#define en_lefty_mode         "LEFTY MODE"
#define en_change_difficulty  "CHANGE DIFFICULTY"
#define en_change_mic_volume  "CHANGE MIC VOLUME"
#define en_quit               "QUIT"

#define en_new_song           "NEW SONG"
#define en_main_menu          "MAIN MENU"

typedef struct changeMicVolume {
  GLuint value;
} pause_micVolume_s;

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
  
  pause_difficultyState_s difficultyState;
  pause_restartState_s restartState;
  pause_leftyMode_s leftyModeChecked;
  pause_micVolume_s micVolumeValue;
  pause_quitState_s quitState;
} pause_fMenuState_s;

extern pause_fMenuState_s pause_menuState;

extern bool gamePaused;

bool screenPause_buffer();
GLvoid screenPause();

#endif
