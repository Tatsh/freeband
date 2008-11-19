#!/bin/bash

gcc -g -o freeband -lSDL -lSDL_image -lSDL_ttf -lGL -lGLU -D__DEBUG__ -ansi -Wall -O2 freeband.c graphics/graphics.c screens/main.c input/input.c
