#ifndef AUDIO_H
#define AUDIO_H

#define MAX_AUDIO_DEVICES 20 /* Safe value? */

#include "ogg.h"
#include "sfx.h"
#include "track.h"

/* 100% legal to distribute/link with */
#define OGG 0 /* Supported/will-be supported audio formats */
#define WAV 1
#define FLAC 2

/* Questionable legality */
#ifdef __AUDIOQL__
#define MP3 10
#define AAC 11
#endif

typedef struct audio_devInfo {
  unsigned int maxInputChannels;
  unsigned int maxOutputChannels;
  double defaultHighOutputLatency;
  double defaultLowOutputLatency;
  double defaultHighInputLatency;
  double defaultLowInputLatency;
  double defaultSampleRate;
} audio_deviceInfo_s;

extern audio_deviceInfo_s audio_deviceInfoSupported[];
extern audio_deviceInfo_s audio_deviceInfoUnsupported[];

bool audio_buffer();
bool audio_findSupportedDevices();
int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

#endif
