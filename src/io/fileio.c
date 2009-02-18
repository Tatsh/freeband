#include "../freeband.h"
#include "fileio.h"
#include "languages.h"
#include "prefs.h"

bool fileIO_copyFile(char originalPath[], char destinationPath[]) {
  FILE *src, *dest;
  char ch;
  bool success;

  if((src=fopen(originalPath, "rb")) == NULL) {
    fprintf(stderr, "Cannot open input file %s.\n", originalPath);
    return false;
  }

  if((dest=fopen(destinationPath, "wb")) == NULL) {
    printf("Cannot create output file %s.\n", destinationPath);
    return false;
  }

  while(!feof(src)) {
    ch = getc(src);
    if(ferror(src)) {
      fprintf(stderr, "Error reading %s", originalPath);
      success = false;
      break;
    } else {
      if(!feof(src)) putc(ch, dest);
      if(ferror(dest)) {
        fprintf(stderr, "Error writing %s", destinationPath);
        success = false;
        break;
      }
    }
  }

  fclose(src);
  fclose(dest);

  return success;
}
