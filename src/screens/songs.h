#ifndef SONGS_H
#define SONGS_H

#include "freeband.h"

#define SORT_TEXT_HT 0.12f
#define offset_screenSongs_sortByTier_x -1.02f
#define offset_screenSongs_sortAZTitle_x -1.0f
#define offset_screenSongs_sortAZArtist_x -1.0f
#define offset_screenSongs_sortbyBPM_x -1.09f
#define SORT_TEXT_Y_OFFSET -0.81f

typedef bool song_sort;

extern bool gamePaused;

extern song_sort byTier_s;
extern song_sort titleAZ_s;
extern song_sort artistAZ_s;
extern song_sort byBPM_s;

bool screenSongs_buffer();
void screenSongs_sort(ushort type);
GLvoid screenSongs();

#endif
