#include "../freeband.h"
#include "audio.h"

bool handleAudioThreads() {

  return true;
}

bool verifyFiletype(int filetype, char path[]) {
  bool verified = false;
  
  switch (filetype) {
    case OGG:
      break;
      
    case WAV:
      break;
      
    case FLAC:
      break;
      
#ifdef __AUDIOQUL__
    case MP3:
      break;
      
    case AAC:
      break;
#endif
      
    default:
      break;
  }
  
  return verified;
}

void playBGM() {
}

void playGuitar() {
}

void playBass() {
}

void playDrums() {
}

void playVocals() {
}

void sfxBuffer() {
}
