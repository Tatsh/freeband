#!/bin/bash

gcc -o freeband -lSDL -lSDL_image -lGL -lGLU -D__DEBUG__ -ansi -Wall -O2 freeband.c screens/main.c graphics/graphics.c
