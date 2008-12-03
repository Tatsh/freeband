#include "../freeband.h"
#include "audio.h"
#include "ogg.h"
#include "sfx.h"

ALuint buffer_fx[MAXFX];
ALuint source_fxA, source_fxB;

ALvoid openSFX(char path[], ALuint format) {
  switch (format) {
    case OGG:
      openOGG(path);
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
  
  alGenBuffers(2, buffer_fx);
  checkErrorState();
  
  return;
}

bool playbackSFX(ALuint source, ALuint buffer[]) {
  return true;
}

bool playSFX() {
  return true;
}
