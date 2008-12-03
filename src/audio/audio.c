#include "../freeband.h"
#include "audio.h"

ALenum channels;

char testTrack[] = "music.ogg";

ALvoid checkErrorState() {
  ALint error = alGetError();
  
  if (error != AL_NO_ERROR)
    fprintf(stderr, "OpenAL had an error: %d\n", error);
  
  return;
}

ALvoid emptyQueued(ALuint source) {
  ALint queued;
  
  alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
  
  while (queued--) {
    ALuint buffer;
    
    alSourceUnqueueBuffers(source, 1, &buffer);
    checkErrorState();
  }
  
  return;
}

ALvoid releaseAudio(ALuint source, ALuint buffer[], ALuint format) {
  alSourceStop(source);
  emptyQueued(source);
  alDeleteSources(1, &source);
#ifdef __DEBUG__
  fprintf(stdout, "Deleting sources.\n");
#endif
  emptyQueued(source);
  alDeleteBuffers(1, buffer);
#ifdef __DEBUG__
  fprintf(stdout, "Deleting buffers.\n");
#endif
  emptyQueued(source);
  
  switch (format) {
    case OGG:
      ov_clear(&oggStream);
      break;
      
    case MP3:
      break;
      
    case WAV:
      break;
      
    case FLAC:
      break;
      
    default:
      break;
  }
  
  return;
}

ALvoid playTrack() { /* Test function only */
  openTrack(testTrack, OGG, BGM);
  releaseAudio(source_bgm, buffer_bgm, OGG);
}
