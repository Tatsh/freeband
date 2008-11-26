#!/bin/bash

gcc -g -o freeband -lm -lopenal -lalut -lvorbis -lvorbisfile -lSDL -lSDL_image -lSDL_ttf -lGL -lGLU -lglut -D__DEBUG__ -D__XBOX360XPLORER__ -ansi -Wall -O2 freeband.c graphics/graphics.c screens/game.c screens/main.c screens/instruments.c screens/songs.c input/input.c
