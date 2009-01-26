#include "../freeband.h"
#include "audio.h"

audio_deviceInfo_s audio_deviceInfoSupported[MAX_AUDIO_DEVICES];
audio_deviceInfo_s audio_deviceInfoUnsupported[MAX_AUDIO_DEVICES];

bool audio_verifyFiletype(GLuint filetype, char path[]) {
  bool ok = false;
  
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
  
  return ok;
}

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
  /* Do not call any PortAudio functions here except for Pa_StreamTime() and Pa_GetCPULoad() */
  
  return 0;
}

bool audio_buffer() {
  const PaDeviceInfo *deviceInfo;
  PaError err;
  int i, numDevices;

  if ((err = Pa_Initialize()) != paNoError) {
    fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText( err ));
    return false;
  }
#ifdef __DEBUG__
  else
    fprintf(stdout, "PortAudio initialised successfully.\n");
#endif
  
  if ((numDevices = Pa_GetDeviceCount()) < 0) {
    fprintf(stderr, "Error: Pa_CountDevices returned %d devices.\n", numDevices);
    return false;
  }
  else {
#ifdef __DEBUG__
    fprintf(stdout, "PortAudio found %d devices.\n", numDevices);
#endif

    for (i = 0; i < numDevices; i++) {
      deviceInfo = Pa_GetDeviceInfo(i);
      
      /* We only care that the device supports sample rates 44100 or higher
         Negative latency values are not usable
         Devices must support at least 1 or more channels for input
         Must support at least 2 output channel */
      if (deviceInfo->defaultSampleRate >= 44100.0f &&
          deviceInfo->maxInputChannels >= 1 &&
          deviceInfo->maxOutputChannels >= 2 &&
          deviceInfo->defaultLowInputLatency >= 0.0f &&
          deviceInfo->defaultLowOutputLatency >= 0.0f &&
          deviceInfo->defaultHighInputLatency >= 0.0f &&
          deviceInfo->defaultLowInputLatency >= 0.0f) {
        fprintf(stdout, "%s is a usable audio device.\n", deviceInfo->name);
        fprintf(stdout, "  Max input channels:  %d\n", deviceInfo->maxInputChannels);
        fprintf(stdout, "  Max output channels: %d\n", deviceInfo->maxOutputChannels);
        fprintf(stdout, "  High output latency: %f\n", deviceInfo->defaultHighOutputLatency);
        fprintf(stdout, "  Low output latency:  %f\n", deviceInfo->defaultLowOutputLatency);
        fprintf(stdout, "  High input latency:  %f\n", deviceInfo->defaultHighInputLatency);
        fprintf(stdout, "  Low input latency:   %f\n", deviceInfo->defaultLowInputLatency);
        fprintf(stdout, "  Best sample rate:    %f\n", deviceInfo->defaultSampleRate);
        
        if (i < MAX_AUDIO_DEVICES) { /* Add device to working list */
          audio_deviceInfoSupported[i].maxInputChannels = deviceInfo->maxInputChannels;
          audio_deviceInfoSupported[i].maxOutputChannels = deviceInfo->maxOutputChannels;
          audio_deviceInfoSupported[i].defaultHighOutputLatency = deviceInfo->defaultHighOutputLatency;
          audio_deviceInfoSupported[i].defaultLowOutputLatency = deviceInfo->defaultLowOutputLatency;
          audio_deviceInfoSupported[i].defaultHighInputLatency = deviceInfo->defaultHighInputLatency;
          audio_deviceInfoSupported[i].defaultLowInputLatency = deviceInfo->defaultLowInputLatency;
          audio_deviceInfoSupported[i].defaultSampleRate = deviceInfo->defaultSampleRate;
        }
      }
      else {
        if (i < MAX_AUDIO_DEVICES) { /* We add to non-working list */
          audio_deviceInfoUnsupported[i].maxInputChannels = deviceInfo->maxInputChannels;
          audio_deviceInfoUnsupported[i].maxOutputChannels = deviceInfo->maxOutputChannels;
          audio_deviceInfoUnsupported[i].defaultHighOutputLatency = deviceInfo->defaultHighOutputLatency;
          audio_deviceInfoUnsupported[i].defaultLowOutputLatency = deviceInfo->defaultLowOutputLatency;
          audio_deviceInfoUnsupported[i].defaultHighInputLatency = deviceInfo->defaultHighInputLatency;
          audio_deviceInfoUnsupported[i].defaultLowInputLatency = deviceInfo->defaultLowInputLatency;
          audio_deviceInfoUnsupported[i].defaultSampleRate = deviceInfo->defaultSampleRate;
        }
      }
    }
  }
  
  return true;
}

bool audio_sfx_buffer() {
  return true;
}

void audio_playBGM() {
}

void audio_playGuitar() {
}

void audio_playBass() {
}

void audio_playDrums() { /* This plays samples, not a long stream to sync with */
}

void audio_playVocals() {
}
