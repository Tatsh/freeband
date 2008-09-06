/* Loading screen 
   Read a text-block from data/loading.xml and show it while the game loads
   information into memory. This can be tips, random information about the song
   or band, etc. */

#include "../error.h"

int getLoadingText();

/* Return 0 for success, return 1 for error and display error from error.c */
int showLoadingScreen();
