#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#define DIFFHT 0.12

extern bool diffEasy, diffMedium, diffHard, diffExpert;

extern GLcoordsY screenDifficulty_selectionY[];

GLvoid screenDifficulty_buffer();
GLvoid screenDifficulty();

#endif
