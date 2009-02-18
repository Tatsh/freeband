#ifndef THEMES_H
#define THEMES_H

typedef char themes_path;

typedef struct { 
} themes_screenMain_s;

typedef struct {
} themes_screenInstruments_s;

typedef struct {
} themes_screenCharacters_s;

typedef struct {
} themes_screenSongs_s;

typedef struct {
} themes_screenGame_s;

typedef struct {
} themes_GamePause_s;

extern bool themes_default;

bool themes_loadTheme(char *theme);
bool themes_loadDefaultTheme();

#endif
