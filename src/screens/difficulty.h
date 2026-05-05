#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include "freeband.h"
#include "graphics/graphics.h"

#define DIFFHT 0.12

#define DIFFICULTY_EASY 0
#define DIFFICULTY_MEDIUM 1
#define DIFFICULTY_HARD 2
#define DIFFICULTY_EXPERT 3

extern GLcoordsY screenDifficulty_selectionY[];
extern ushort current_difficulty;

bool screenDifficulty_buffer();
GLvoid screenDifficulty();

#endif
