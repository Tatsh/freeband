#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <portaudio.h>
#include <vorbis/vorbisfile.h>

#define FRAMES_PER_BUFFER 1024

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <ogg file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  int i;
  
  char *pcmout;
  int endian;
  int position;
  int testvar = 1; /* Used to test endianness */
  long ret = 1;
  OggVorbis_File vf;
  vorbis_info *vi;
  
  int numBytes;
  PaError err;
  PaStream *stream;
  PaStreamParameters outputParameters;
  
  if (ov_fopen(argv[1], &vf) < 0) {
    fprintf(stderr, "Input %s does not appear to be an Ogg bitstream.\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  
  vi = ov_info(&vf, -1);
  
  if (*(char *)&testvar) /* Hack taken from Audacity source code */
    endian = 0;  /* little endian, most common */
  else
    endian = 1;
  
  numBytes = FRAMES_PER_BUFFER * vi->channels * 2;
  pcmout = (char*)malloc(numBytes);
  if (pcmout == NULL) {
    fprintf(stdout, "Could not allocate pcmout array.\n");
  }
  bzero(pcmout, FRAMES_PER_BUFFER * vi->channels * 2);
  
  fprintf(stdout, "File information: \n");
  fprintf(stdout, "  File name: %s\n", argv[1]);
  fprintf(stdout, "  Number of channels: %d\n", vi->channels);
  fprintf(stdout, "  Sample rate: %ld\n", vi->rate);
  fprintf(stdout, "  Length (seconds): %.3f\n", ov_time_total(&vf, -1));
  fprintf(stdout, "  Length (samples): %ld\n", (long)ov_pcm_total(&vf, -1));
  fprintf(stdout, "  Byte-order: %s\n", endian ? "MSB" : "LSB");
  
  if (ov_pcm_seek(&vf, 0) != 0) { /* This is because some files do not do this automatically */
    fprintf(stderr, "Error seeking file to position 0.\n");
  }
  else
    fprintf(stdout, "Seeked file to position 0.\n");
  
  if ((err = Pa_Initialize()) != paNoError) {
    fprintf(stderr, "Error initialising PortAudio: %s\n", Pa_GetErrorText(err));
    exit(EXIT_FAILURE);
  }
  else
    fprintf(stdout, "Successfully initialised PortAudio.\n");
  
  outputParameters.device = Pa_GetDefaultOutputDevice();
  outputParameters.channelCount = vi->channels;
  outputParameters.sampleFormat = paInt16;
  outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;
  
  fprintf(stdout, "Device information:\n");
  fprintf(stdout, "  Name: %s\n", Pa_GetDeviceInfo(outputParameters.device)->name);
  fprintf(stdout, "  Number of channels: %d\n", outputParameters.channelCount);
  fprintf(stdout, "  Sample format: paInt16\n");
  fprintf(stdout, "  Latency: %f\n", Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency);
  
  err = Pa_OpenStream(&stream,
                      NULL,
                      &outputParameters,
                      vi->rate,
                      FRAMES_PER_BUFFER,
                      paClipOff,
                      NULL, /* No callback */
                      NULL);
  if (err != paNoError) {
    fprintf(stderr, "Error opening stream: %s\n", Pa_GetErrorText(err));
    exit(EXIT_FAILURE);
  }
  else
    fprintf(stdout, "Successfully opened stream.\n");
  
  if ((err = Pa_StartStream(stream)) != paNoError) {
    fprintf(stderr, "Error starting stream: %s\n", Pa_GetErrorText(err));
    exit(EXIT_FAILURE);
  }
  else
    fprintf(stdout, "Successfully started stream.\n");
  
  /* Main loop */
  while (ret != 0) {
    ret = ov_read(&vf,pcmout,FRAMES_PER_BUFFER,0,2,1,&position);
    fwrite(pcmout,1,ret,stdout);
  }
  
  ov_clear(&vf);
  free(pcmout);
  
  if ((err = Pa_StopStream(stream)) != paNoError) {
    fprintf(stderr, "Error stopping stream: %s\n", Pa_GetErrorText(err));
    exit(EXIT_FAILURE);
  }
  else
    fprintf(stdout, "Successfully stopped stream.\n");
  
  if ((err = Pa_CloseStream(stream)) != paNoError) {
    fprintf(stderr, "Error closing stream: %s\n", Pa_GetErrorText(err));
    exit(EXIT_FAILURE);
  }
  else
    fprintf(stdout, "Successfully closed stream.\n");
  
  if ((err = Pa_Terminate()) != paNoError) {
    fprintf(stderr, "Error terminating PortAudio: %s\n", Pa_GetErrorText(err));
    exit(EXIT_FAILURE);
  }
  else
    fprintf(stdout, "Successfully terminated PortAudio.\n");
  
  exit(EXIT_SUCCESS);
}
