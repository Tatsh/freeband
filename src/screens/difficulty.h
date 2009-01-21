#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#define DIFFHT 0.12

#define en_select_difficulty "SELECT DIFFICULTY"
#define en_easy "EASY"
#define en_medium "MEDIUM"
#define en_hard "HARD"
#define en_expert "EXPERT"

extern bool diffEasy, diffMedium, diffHard, diffExpert;

extern GLcoordsY screenDifficulty_selectionY[];

bool screenDifficulty_buffer();
GLvoid screenDifficulty();

#endif
