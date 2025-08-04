#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#include "graphics/graphics.h"

typedef struct {
  bool guitar;
  bool bass;
  bool drums;
  bool vocals;
} instrument_s;

extern GLcoordsX screenInstruments_selectionX[];
extern GLcoordsY screenInstruments_selectionY[];
extern GLcoordsX screenInstruments_selectionReset[];

extern instrument_s instrument[];

extern ushort current_instrument;

GLvoid screenInstruments_highlighted(GLuint instSelection);
GLvoid screenInstruments_accept();
bool screenInstruments_buffer();
GLvoid screenInstruments();

#endif
