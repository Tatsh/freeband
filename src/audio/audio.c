#include "../freeband.h"
#include "../io/prefs.h"
#include "audio.h"

audio_deviceInfo_s audio_deviceInfoSupported[MAX_AUDIO_DEVICES];
audio_deviceInfo_s audio_deviceInfoUnsupported[MAX_AUDIO_DEVICES];

audio_deviceInfo_s audio_deviceInfoTemplate;

bool audio_verifyFiletype(unsigned short filetype, char path[]) {
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
  ushort i, numDevices;

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
    
    /* Initialise template struct for arrays */
    audio_deviceInfoTemplate.maxInputChannels = 0;
    audio_deviceInfoTemplate.maxOutputChannels = 0;
    audio_deviceInfoTemplate.defaultHighOutputLatency = 0.0f;
    audio_deviceInfoTemplate.defaultLowOutputLatency = 0.0f;
    audio_deviceInfoTemplate.defaultHighInputLatency = 0.0f;
    audio_deviceInfoTemplate.defaultLowInputLatency = 0.0f;
    audio_deviceInfoTemplate.defaultSampleRate = 0.0f;
    for (i = 0; i < MAX_AUDIO_DEVICES; i++) audio_deviceInfoSupported[i] = audio_deviceInfoTemplate;
    for (i = 0; i < MAX_AUDIO_DEVICES; i++) audio_deviceInfoUnsupported[i] = audio_deviceInfoTemplate;
    
    /* Query devices for options screen
       On this screen there should be AUDIO INPUT and AUDIO OUTPUT; we will have devices with just output in AUDIO OUTPUT and 
       devices with just input in AUDIO INPUT; if a device has both, it will be listed in both */
    for (i = 0; i < numDevices; i++) {
      deviceInfo = Pa_GetDeviceInfo(i);
      /* Windows is different in that it will have 2 devices of the same name but 1 with input channels and 1 with output channels
         Since we are using the default device by default, we will not worry about this yet
         It may confusing to the Windows user in the options menu since devices have the same name, so maybe we should add (input) and (output) to the 
         strings? */
#ifdef __WIN32__
      if (deviceInfo->defaultSampleRate >= 44100.0f &&
          deviceInfo->defaultLowInputLatency >= 0.0f &&
          deviceInfo->defaultLowOutputLatency >= 0.0f &&
          deviceInfo->defaultHighInputLatency >= 0.0f &&
          deviceInfo->defaultLowInputLatency >= 0.0f) {
#else
      /* All other OS: We only care that the device supports sample rates 44100 or higher
         Negative latency values are not usable
         Devices must support at least 1 or more channels for input
         Must support at least 1 output channel (mono) */
      if (deviceInfo->defaultSampleRate >= 44100.0f &&
          deviceInfo->maxInputChannels >= 1 && /* Without at least 1 input, microphone (vocals) mode cannot be utilised */
          deviceInfo->maxOutputChannels >= 1 &&
          deviceInfo->defaultLowInputLatency >= 0.0f &&
          deviceInfo->defaultLowOutputLatency >= 0.0f &&
          deviceInfo->defaultHighInputLatency >= 0.0f &&
          deviceInfo->defaultLowInputLatency >= 0.0f) {
#endif
        fprintf(stdout, "%s is a 100%% compatible audio device.\n", deviceInfo->name);
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
        fprintf(stdout, "%s is not a 100%% compatible audio device.\n", deviceInfo->name);
#ifdef __DEBUG__
        fprintf(stdout, "  Max input channels:  %d\n", deviceInfo->maxInputChannels);
        fprintf(stdout, "  Max output channels: %d\n", deviceInfo->maxOutputChannels);
        fprintf(stdout, "  High output latency: %f\n", deviceInfo->defaultHighOutputLatency);
        fprintf(stdout, "  Low output latency:  %f\n", deviceInfo->defaultLowOutputLatency);
        fprintf(stdout, "  High input latency:  %f\n", deviceInfo->defaultHighInputLatency);
        fprintf(stdout, "  Low input latency:   %f\n", deviceInfo->defaultLowInputLatency);
        fprintf(stdout, "  Best sample rate:    %f\n", deviceInfo->defaultSampleRate);
#endif

        if (i < MAX_AUDIO_DEVICES) { /* We add to non-working list, allow user to force these in options? */
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

  if (!audio_findSupportedDevices()) {
    fprintf(stderr, "Could not find a usable audio device.\n");
    return false;
  }
  else { /* Get default devices until settings file has been established */
    i = Pa_GetDefaultInputDevice();
    deviceInfo = Pa_GetDeviceInfo(i);
    fprintf(stdout, "Default input device: %s\n", deviceInfo->name);
    i = Pa_GetDefaultOutputDevice();
    deviceInfo = Pa_GetDeviceInfo(i);
    fprintf(stdout, "Default output device: %s\n", deviceInfo->name);
  }
  
  return true;
}

bool audio_findSupportedDevices() {
  ushort i, supported = 0;
  
  for ( i = 0; i < MAX_AUDIO_DEVICES; i++ ) { /* Must support at least 1 output channel */
    if (audio_deviceInfoSupported[i].maxOutputChannels != 0)
      supported++;
  }
  
  if (supported == 0)
    return false;
  
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
