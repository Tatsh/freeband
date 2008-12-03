#ifndef SFX_H
#define SFX_H

#define MAXFX 16 /* 28 to 32 audio buffers is the limit often on Windows */

ALvoid openSFX(char path[], ALuint format);
bool playbackSFX(ALuint source, ALuint buffer[]);
bool playingSFX();
bool playSFX();
bool updateSFX();

#endif
