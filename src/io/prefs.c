#include "../freeband.h"
#include "prefs.h"

prefs_directory prefs_root[255];
prefs_directory prefs_songs[255];
prefs_directory prefs_themes[255];

prefs_ushort prefs_audio_mic_volume; /* Ranges from 0-100 */
#ifdef __WIN32__

#else

bool prefs_nixPrefsDirExists() {
  GLint exists, ret;
  struct stat buffer;

  strcat(prefs_root, getenv("HOME"));
  if (prefs_root == NULL) {
    fprintf(stderr, "Could not find home directory.\nTry setting $HOME to a path.");
    return false;
  }
  
  strcat(prefs_root, "/Freeband");
  
  if ((exists = stat(prefs_root, &buffer)) == 0) {
    fprintf(stdout, "Found Freeband preferences root: %s.\n", prefs_root);
    
    /* Validate folder paths, fix if necessary */
    strcat(prefs_songs, prefs_root);
    strcat(prefs_songs, "/songs");
    if ((exists = stat(prefs_songs, &buffer)) == 0)
      fprintf(stdout, "Found Freeband songs folder: %s.\n", prefs_songs);
    else {
      fprintf(stderr, "Could not find songs folder. Creating one now...\n");
      if ((ret = mkdir(prefs_songs, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0)
        return false;
    }
    
    strcat(prefs_themes, prefs_root);
    strcat(prefs_themes, "/themes");
    if ((exists = stat(prefs_themes, &buffer)) == 0)
      fprintf(stdout, "Found Freeband themes folder: %s.\n", prefs_themes);
    else {
      fprintf(stderr, "Could not find themes folder. Creating one now...\n");
      if ((ret = mkdir(prefs_themes, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0)
        return false;
    }
  }
  else {
    fprintf(stderr, "Could not find Freeband directory. Creating one now...\n");
    return false;
  }
  
  return true;
}

bool prefs_nixPrefsDirCreate() {
  GLint ret;
  
  if (prefs_root == NULL) {
    fprintf(stderr, "Could not find home directory.\nTry setting $HOME to a path.");
    return false;
  }
  if ((ret = mkdir(prefs_root, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0)
    return false;
  
  /* We can assume it will work from this point on */
  strcat(prefs_songs, prefs_root);
  strcat(prefs_songs, "/songs");
  mkdir(prefs_songs, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  
  strcat(prefs_themes, prefs_root);
  strcat(prefs_themes, "/themes");
  mkdir(prefs_themes, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  
  return true;
}
#endif
