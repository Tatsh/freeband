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

/* Compile with gcc -o metronome metronome.c */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

double bpm2bps(double bpm)
{
  double bps = bpm/60;
  return bps;
}

double pulse(double rate, int bars)
{
  double pausetime, pausetime_u;
  pausetime = 1/rate;
  pausetime_u = pausetime*(1000000);
  
  printf("Time between notes is %.2f seconds", pausetime);
  
  printf("\n1\n");
  int notes = (bars*4)-1; /* Always one less note than the total notes because of the first note */
  int i;
  for (i = 0; i < notes; i++)
  {
    usleep(pausetime_u);
    printf("1\n");
  }
  
  return 0;
}

int main(int argc, char *argv[])
{
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
    double bps = bpm2bps((double)atoi(argv[1]));
    printf("Pulsing at %.2f BPM (%.2f beats/second)\nPlaying %s bars (%d notes)\n", (double)atoi(argv[1]), bps, argv[2], atoi(argv[2])*4);
    pulse(bps, atoi(argv[2]));
    exit(EXIT_SUCCESS);
  }
}
