#include "../freeband.h"
#include "audio.h"

OggVorbis_File oggStream;
vorbis_info *vorbisInfo;

ALvoid openOGG(char path[]) {
  FILE *oggFile;
  ALint result;
  
  if (!(oggFile = fopen(path, "rb")))
    fprintf(stderr, "Could not open %s.\n", path);
#ifdef __DEBUG__
  else
    fprintf(stdout, "ogg.c: openOGG(): Opened %s\n", path);
#endif

#ifdef __WIN32__
  if ((result = ov_fopen(oggFile, &oggStream, NULL, 0)) < 0) {
#else
  if ((result = ov_open(oggFile, &oggStream, NULL, 0)) < 0) {
#endif
    fclose(oggFile);
    fprintf(stderr, "Vorbis failed to open %s.\n", path);
  }
  
  vorbisInfo = ov_info(&oggStream, -1);
  
  if (vorbisInfo->channels == 1) /* Safe to force to 16-bit for OGG files */
    channels = AL_FORMAT_MONO16;
  else
    channels = AL_FORMAT_STEREO16;
  
#ifdef __DEBUG__
  fprintf(stdout, "Channels: %d\n", vorbisInfo->channels);
  fprintf(stdout, "Rate (Hz): %li\n", vorbisInfo->rate);
#endif

  return;
}
