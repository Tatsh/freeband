#ifndef TRACK_H
#define TRACK_H

#define BGM 0 /* Audio types that are not sound F/X */
#define GUITAR 1
#define BASS 2
#define DRUMS 3
#define VOCALS 4

ALuint buffer_bgm[2];
ALuint buffer_guitar[2], buffer_bass[2], buffer_drums[2], buffer_vocals[2];

ALuint source_bgm;
ALuint source_guitar, source_bass, source_drums, source_vocals;

ALvoid openTrack(char path[], ALuint format, ALuint type);
bool playbackTrack(ALuint source, ALuint buffer[], ALuint format);
bool playingTrack(ALuint source);
bool streamTrack(ALuint buffer, ALuint format);
bool updateTrack(ALuint source, ALuint format);

#endif
