#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#define DIFFHT 0.12

#define DIFFICULTY_EASY   0x00
#define DIFFICULTY_MEDIUM 0x01
#define DIFFICULTY_HARD   0x02
#define DIFFICULTY_EXPERT 0x03

extern GLcoordsY screenDifficulty_selectionY[];
extern ushort current_difficulty;

bool screenDifficulty_buffer();
GLvoid screenDifficulty();

#endif
