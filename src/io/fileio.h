#ifndef FILEIO_H
#define FILEIO_H

bool fileIO_copyFile(char originalPath[], char destinationPath[]);

#ifdef __WIN32__
bool fileIO_unix2dos(FILE *in)
#endif /* __WIN32__ */

#endif
