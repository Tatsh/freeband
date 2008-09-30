#!/bin/bash

gcc -o freeband -lSDL -lSDL_image -lSDL_ttf -lGL -D__DEBUG__ -D__GL__ -ansi -Wall -O2 freeband.c screens/main.c graphics/main.c
