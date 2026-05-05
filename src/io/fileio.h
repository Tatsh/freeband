#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>

bool fileIO_copyFile(char originalPath[], char destinationPath[]);

#ifdef _WIN32
bool fileIO_unix2dos(FILE *in);
#endif /* _WIN32 */

#endif
