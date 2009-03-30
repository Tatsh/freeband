#ifndef KEYS_H
#define KEYS_H

#define KEYS_NOKEY -1

/* Thanks to syntropy for this method */
typedef struct {
  char *key;
  int map;
} keymap_s;

typedef struct {
  char *iniItem;
  uint user_value;
  uint default_value;
} keyPrefs_s;

extern keyPrefs_s keyPrefs[];

int keys_mapKeystringToSDL(char *key);

#endif
