#ifndef SONGS_H
#define SONGS_H

#define SORT_TEXT_HT 0.12f
#define offset_screenSongs_sortByTier_x -1.1f
#define offset_screenSongs_sortAZTitle_x -1.0f
#define offset_screenSongs_sortAZArtist_x -1.0f
#define offset_screenSongs_sortbyBPM_x -1.09f
#define SORT_TEXT_Y_OFFSET -0.81f

#define SORT_BY_TIER 0
#define SORT_AZ_TITLE 1
#define SORT_AZ_ARTIST 2
#define SORT_BPM 3

#define en_songs              "SONGS"
#define en_songs_by_tier      "by Tier"
#define en_songs_az           "A-Z by Title"
#define en_songs_alpha_artist "A-Z by Artist"
#define en_songs_by_bpm       "by BPM"

typedef bool song_sort;

extern bool gamePaused;

extern song_sort byTier_s;
extern song_sort titleAZ_s;
extern song_sort artistAZ_s;
extern song_sort byBPM_s;

bool screenSongs_buffer();
GLvoid screenSongs_sort(GLuint type);
GLvoid screenSongs();

#endif
