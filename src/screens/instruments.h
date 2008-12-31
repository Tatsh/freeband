#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

typedef struct {
  bool guitar;
  bool bass;
  bool drums;
  bool vocals;
} tInstrument;

extern GLfloat screenInstruments_selectionX[];
extern GLfloat screenInstruments_selectionY[];
extern GLfloat screenInstruments_selectionReset[];

extern GLuint screenInstruments_nSelection;

extern tInstrument instrument_P1;
extern tInstrument instrument_P2;
extern tInstrument instrument_P3;
extern tInstrument instrument_P4;

GLvoid screenInstruments_highlighted(GLuint instSelection);
GLvoid screenInstruments_accept();
GLvoid screenInstruments_buffer();
GLvoid screenInstruments();

#endif
