/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    Copyright (C) 2008, Tatsh
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "SDL/SDL.h"
// *** IF USING XCODE ON MACOS X, YOU MAY NEED TO CHANGE THE FOLLOWING LINE TO:  #include "SDL_mixer/SDL_mixer.h"
#include "SDL/SDL_mixer.h"

Mix_Music *music; // Pointer to music in memory
int musicPlaying = 0; // Music is NOT playing

void musicFinished()
{
  //Music is done!
  musicPlaying = 0;
}

int SDLInitialiseAudio()
{
  // For now, standard audio format for CDs (2 * 22050 = 44.1 kHz)
  int audio_rate = 22050;     //Frequency of audio playback
  Uint16 audio_format = AUDIO_S16SYS;   //Format of the audio we're playing
  int audio_channels = 2;     //2 channels = stereo
  int audio_buffers = 4096;   //Size of the audio buffers in memory
    
  // Initialise only audio
  if (SDL_Init(SDL_INIT_AUDIO) != 0) 
  {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }
    
  //Initialize SDL_mixer with our chosen audio settings
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) 
  {
    printf("Unable to initialize audio: %s\n", Mix_GetError());
    return 1;
  }
    
  //Load our music file from disk
  music = Mix_LoadMUS("click.aif");
  if(music == NULL) 
  {
    printf("Unable to load file: %s\n", Mix_GetError());
    return 1;
  }
}

int SDLLoadClick()
{
  // Play music
  if(Mix_PlayMusic(music, 0) == -1) 
  {
    printf("Unable to play OGG file: %s\n", Mix_GetError());
    return 1;
  }
  musicPlaying = 1; // Music is now playing
    
  // This must be called when music is done playing
  Mix_HookMusicFinished(musicFinished);
    
  // Wait for audio to end
  while(musicPlaying)
  {
    //Do nothing for a bit
    SDL_Delay(100);
  }
}

void SDLFreeMemory()
{
  // Release the memory allocated to our music
  Mix_HaltMusic();
  Mix_FreeMusic(music);
}

void SDLCleanUp()
{
  // Need to make sure that SDL_mixer and SDL have a chance to clean up
  Mix_CloseAudio();
  SDL_Quit();
}

double bpm2bps(int bpm)
{
  double bps = (double)bpm/60;
  return bps;
}

double pulse(double rate, double bars)
{
  double pausetime, mpausetime;
  pausetime = 1/rate;
  mpausetime = pausetime*(1000);
  int pausetime_u = (int)mpausetime;

  printf("Time between notes is %d milliseconds\n", pausetime_u);
  printf("Tick\n");
  SDLLoadClick();
  SDL_Delay(pausetime_u/4); // Divide by 4 to compensate for the time it takes for function SDLLoadClick to load, closest for now and may vary on other OS's and systems; SDL_Delay is affected by OS scheduling greatly
  int notes = (bars*4)-1; /* Always one less note than the total notes because of the first note */
  int i;
  for (i = 0; i < notes; i++)
  {
    printf("Tick\n");
    SDLLoadClick();
    SDL_Delay(pausetime_u/4);
  }
  
  return 0;
}

int main(int argc, char *argv[])
{
  // Parse arguments
  if (argv[1] == NULL)
  {
    printf("No BPM specified.\nUsage: %s <bpm> <# of bars>\n", argv[0]);
    return 1;
  }
  if (argv[2] == NULL)
  {
    printf("# of bars not specified.\nUsage: %s <bpm> <# of bars>\n", argv[0]);
    return 1;
  }
  else if (argv[1] == NULL && argv[2] == NULL)
  {
    printf("No BPM or # of bars specified.\nUsage: %s <bpm> <# of bars>\n", argv[0]);
    return 1;
  }
  else
  {
    // SDL
    SDLInitialiseAudio();
    
    // Main app
    double bps = bpm2bps(atoi(argv[1]));
    printf("Pulsing at %d BPM (%.2f beats/second)\nPlaying %s bars (%d notes)\n", atoi(argv[1]), bps, argv[2], atoi(argv[2])*4);
    pulse(bps, atoi(argv[2]));
    
    // SDL
    SDLFreeMemory();
    SDLCleanUp();

    exit(EXIT_SUCCESS);
  }
}
