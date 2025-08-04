#include "freeband.h"
#include "songs.h"
#include "songlist.h"

songNode_s songNode; /* 1 song */
songList_s songList; /* The song list */

/* All functions here return NULL if an error occurs */

songList_s *songs_createSongList() {
  songList_s *list = malloc(sizeof *list);
  
  if (list != NULL) {
    list->head = songs_createSongNode(NULL, NULL, NULL, NULL, NULL);
    list->size = 0;
    
    if (list->head != NULL) {
      /* Circular references */
      list->head->next = list->head;
      list->head->prev = list->head;
    }
    else {
      free(list);
      list = NULL;
    }
  }
  
  return list;
}

songNode_s *songs_createSongNode(file_p *notes,
                                 songStrings_s *songStrings,
                                 songDiffs_s *songDifficulties,
                                 songAudioProps_s *songAudioProperties,
                                 songNode_s *next) {
  songNode_s *node = malloc(sizeof *node);
  if (node !=NULL) {
    node->next = next;
  }
  
  return node;
}

songNode_s *songs_insertSongNodeAfter(file_p *notes,
                                      songStrings_s *songStrings,
                                      songDiffs_s *songDifficulties,
                                      songAudioProps_s *songAudioProperties,
                                      songList_s *list,
                                      songNode_s *position) {
  songNode_s *ref = NULL;
  
  if (list != NULL && position != NULL) {
    ref = songs_createSongNode(notes, songStrings, songDifficulties, songAudioProperties, position->next);
    
    if (ref != NULL) {
      position->next->prev = ref;
      position->next = ref;
      ++list->size;
    }
  }
  
  return ref;
}

songNode_s *songs_insertSongNodeBefore(file_p *notes,
                                       songStrings_s *songStrings,
                                       songDiffs_s *songDifficulties,
                                       songAudioProps_s *songAudioProperties,
                                       songList_s *list,
                                       songNode_s *position) {
  songNode_s *ref = NULL;
  
  if (list != NULL && position != NULL) {
    ref = songs_createSongNode(notes, songStrings, songDifficulties, songAudioProperties, position->prev);
    
    if (ref != NULL) {
      position->prev->next = ref;
      position->prev = ref;
      ++list->size;
    }
  }
  
  return ref;
}

songNode_s *songs_deleteSongNode(songList_s *list, songNode_s *position) {
  songNode_s *node = NULL;
  
  if ( list != NULL && position != NULL ) {
    if (position != list->head ) {
      /* Remove non-header node */
      node = position;
      
      /* Reset the list links */
      node->prev->next = node->next;
      node->next->prev = node->prev;
      
      /* Clean up the old node */
      node->prev = node->next = NULL;
      --list->size;
    }
  }
  
  return node;
}

/* These functions are not ready yet :),
songNode_s *songs_insertSongSortedTier(file_p *notes,
                                   songStrings_s *songStrings,
                                   songDiffs_s *songDifficulties,
                                   songAudioProps_s *songAudioProperties,
                                   songList_s *list);

songNode_s *songs_insertSongSortedTitle(file_p *notes,
                                   songStrings_s *songStrings,
                                   songDiffs_s *songDifficulties,
                                   songAudioProps_s *songAudioProperties,
                                   songList_s *list) {
  songNode_s *node = NULL;
  
Compare title string here
  
  return node;
}

songNode_s *songs_insertSongSortedBPM(file_p *notes,
                                   songStrings_s *songStrings,
                                   songDiffs_s *songDifficulties,
                                   songAudioProps_s *songAudioProperties,
                                   songList_s *list);

songNode_s *songs_insertSongSortedArtist(file_p *notes,
                                   songStrings_s *songStrings,
                                   songDiffs_s *songDifficulties,
                                   songAudioProps_s *songAudioProperties,
                                   songList_s *list); */

GLvoid songs_destroySongList(songList_s *list) {
  while (list->size > 0) {
    list->head = songs_deleteSongNode(list, list->head);
    --list->size;
  }
  
}
