#ifndef AUDIO_H
#define AUDIO_H

#include "ogg.h"
#include "sfx.h"
#include "track.h"

#define BUFFER_SIZE 65536

#define OGG 0 /* Supported/will-be supported audio formats */
#define MP3 1
#define WAV 2
#define FLAC 3

extern char testTrack[];

#endif
