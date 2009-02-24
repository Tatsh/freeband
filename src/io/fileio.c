#include "../freeband.h"
#include "fileio.h"
#include "languages.h"
#include "prefs.h"

#ifdef __WIN32__
#include <utime.h>
#include "unix2dos.h"
#endif

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

#ifdef __WIN32__
/* Based on unix2dos */
bool fileIO_unix2dos(FILE *in) {
  FILE *temp;
  char path_temp[16];
  int temp_char;
  
  path_temp[0] = '\0';
  strcpy(path_temp, "./u2dtmp");
  strcat(path_temp, "XXXXXX");  if (fopen(path_temp, "w+") == NULL)
      return false;
  
#ifdef __DEBUG__
  fprintf(stderr, "fileIO_unix2dos(): using %s as temporary file...\n", path_temp);
#endif /* __DEBUG__ */
  
  while ((temp_char = getc(in)) != EOF) {
    if ((temp_char == '\x0a') && (putc('\x0d', path_temp) == EOF) ||
       (temp_char == '\x0d') && (((temp_char = getc(in)) == EOF) ||
       (putc('\x0d', path_temp) == EOF)) || (putc(U2DAsciiTable[temp_char], path_temp) == EOF)) {
         return false;
    }
  }
  
  if ((rename(path_temp, in) == -1) {
    fprintf(stderr, "unix2dos: Error renaming %s to original file.\n", path_temp);
    fprintf(stderr, "          Output file remains %s.\n", path_temp);
  }
  
  return true;
}
#endif /* __WIN32__ */
