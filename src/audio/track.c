#include "../freeband.h"
#include "audio.h"

ALvoid openTrack(char path[], ALuint format, ALuint type) {
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
  
  switch (type) {
    case BGM:
      alGenBuffers(2, buffer_bgm);
      checkErrorState();
      alGenSources(1, &source_bgm);
      checkErrorState();
      alSource3f(source_vocals, AL_POSITION,       0.0f, 0.0f, 0.0f);
      alSource3f(source_vocals, AL_VELOCITY,       0.0f, 0.0f, 0.0f);
      alSource3f(source_vocals, AL_DIRECTION,      0.0f, 0.0f, 0.0f);
      alSourcef (source_vocals, AL_ROLLOFF_FACTOR, 0.0f);
      alSourcei (source_bgm, AL_SOURCE_RELATIVE, AL_TRUE);
      break;
      
    case GUITAR:
      alGenBuffers(2, buffer_guitar);
      checkErrorState();
      alGenSources(1, &source_guitar);
      checkErrorState();
      alSource3f(source_vocals, AL_POSITION,        0.0f, 0.0f, 0.0f);
      alSource3f(source_vocals, AL_VELOCITY,        0.0f, 0.0f, 0.0f);
      alSource3f(source_vocals, AL_DIRECTION,       0.0f, 0.0f, 0.0f);
      alSourcef (source_vocals, AL_ROLLOFF_FACTOR,  0.0f);
      alSourcei (source_guitar, AL_SOURCE_RELATIVE, AL_TRUE);
      break;
      
    case BASS:
      alGenBuffers(2, buffer_bass);
      checkErrorState();
      alGenSources(1, &source_bass);
      checkErrorState();
      alSource3f(source_vocals, AL_POSITION,       0.0f, 0.0f, 0.0f);
      alSource3f(source_vocals, AL_VELOCITY,       0.0f, 0.0f, 0.0f);
      alSource3f(source_vocals, AL_DIRECTION,      0.0f, 0.0f, 0.0f);
      alSourcef (source_vocals, AL_ROLLOFF_FACTOR, 0.0f);
      alSourcei (source_bass, AL_SOURCE_RELATIVE, AL_TRUE);
      break;
      
    case DRUMS:
      alGenBuffers(2, buffer_drums);
      checkErrorState();
      alGenSources(1, &source_drums);
      checkErrorState();
      alSource3f(source_vocals, AL_POSITION,       0.0f, 0.0f, 0.0f);
      alSource3f(source_vocals, AL_VELOCITY,       0.0f, 0.0f, 0.0f);
      alSource3f(source_vocals, AL_DIRECTION,      0.0f, 0.0f, 0.0f);
      alSourcef (source_vocals, AL_ROLLOFF_FACTOR, 0.0f);
      alSourcei (source_drums, AL_SOURCE_RELATIVE, AL_TRUE);
      break;
      
    case VOCALS:
      alGenBuffers(2, buffer_vocals);
      checkErrorState();
      alGenSources(1, &source_vocals);
      checkErrorState();
      alSource3f(source_vocals, AL_POSITION,       0.0f, 0.0f, 0.0f);
      alSource3f(source_vocals, AL_VELOCITY,       0.0f, 0.0f, 0.0f);
      alSource3f(source_vocals, AL_DIRECTION,      0.0f, 0.0f, 0.0f);
      alSourcef (source_vocals, AL_ROLLOFF_FACTOR, 0.0f);
      alSourcei (source_vocals, AL_SOURCE_RELATIVE, AL_TRUE);
      break;
      
    default:
      break;
  }
  
  return;
}

bool playingTrack(ALuint source) {
  ALenum state;
  
  alGetSourcei(source, AL_SOURCE_STATE, &state);
  
  return (state == AL_PLAYING);
}

bool streamTrack(ALuint buffer, ALuint format) {
  
  char pcm[BUFFER_SIZE];
  ALuint size = 0;
  ALint section;
  ALint result;
  
  while (size < BUFFER_SIZE) {
    switch (format) {
      case OGG:
        result = ov_read(&oggStream, pcm + size, BUFFER_SIZE - size, 0, 2, 1, &section);
        break;
      
      default:
        break;
    }

    if (result > 0)
      size += result;
    else
      if (result < 0)
        fprintf(stderr, "track.c: streamTrack() error\n");
    else
      break;
  }
  
  if (size == 0)
    return false;

  switch (format) {
    case OGG:
      alBufferData(buffer, channels, pcm, size, vorbisInfo->rate);
      checkErrorState();
      break;
      
    default:
      break;
  }
  
  return true;
}

bool updateTrack(ALuint source, ALuint format) {
  ALint processed;
  bool active = true;
  
  alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
  
  while (processed--) {
    ALuint tBuffer;
    
    alSourceUnqueueBuffers(source, 1, &tBuffer);
    checkErrorState();
    
    active = streamTrack(tBuffer, format);
    
    alSourceQueueBuffers(source, 1, &tBuffer);
    checkErrorState();
  }
  
  return active;
}

bool playbackTrack(ALuint source, ALuint buffer[], ALuint format) {
  if (playingTrack(source))
    return true;
  
  if (!streamTrack(buffer[0], format))
    return false;
  
  if (!streamTrack(buffer[1], format))
    return false;
  
  alSourceQueueBuffers(source, 2, buffer);
  alSourcePlay(source);
  
  return true;
}
