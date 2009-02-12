#ifndef SONGLIST_H
#define SONGLIST_H

#ifdef __WIN32__
typedef unsigned int uint;
#endif

typedef uint difficulty_i; /* Difficulty out of 5 */
typedef float bpm_f;
typedef char file_p; /* File path */
typedef char sndfile_p; /* Sound file path */
typedef char sample_p; /* Sound sample file path */

typedef struct songDiffs {
  bool easy; /* Do we have every difficulty? Which ones do we not have? */
  bool medium;
  bool hard;
  bool expert;
  
  difficulty_i guitar; /* These are set in Rock Band 2; other games do not feature difficulty levels */
  difficulty_i bass;
  difficulty_i drums;
  difficulty_i vocals;
} songDiffs_s;

typedef struct songAudioProps {
  bpm_f bpm;
  float samplestart;
  float samplelength;
  
  sndfile_p guitar_p; /* These are 'stream' files */
  sndfile_p bass_p;
  sndfile_p vocals_p;
  
  sample_p kick; /* These are samples; songs may revert to defaults if none are specified */
  sample_p hihat;
  sample_p crash;
} songAudioProps_s;

typedef struct songStr { /* Song string data */
  char *title;
  char *artist;
  char *subtitle;
} songStrings_s;

typedef struct songNode {
  file_p notes; /* Note XML file */
  
  songStrings_s songStrings;
  songDiffs_s songDifficulties;
  songAudioProps_s songAudioProperties;
  
  struct songNode *next;
  struct songNode *prev;
} songNode_s;

typedef struct songList {
  size_t size;
  
  struct songNode *head;
  struct songNode *tail;
} songList_s;

extern songNode_s songNode;
extern songList_s songList;

songNode_s *songs_createSongNode(file_p *notes, songStrings_s *songStrings, songDiffs_s *songDifficulties, songAudioProps_s *songAudioProperties, songNode_s *next);
songNode_s *songs_deleteSongNode(songList_s *list, songNode_s *position);
songList_s *songs_createSongList();

#endif
