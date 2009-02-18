#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#define INSTRUMENT_GUITAR 0x00
#define INSTRUMENT_BASS   0x01
#define INSTRUMENT_DRUMS  0x02
#define INSTRUMENT_VOCALS 0x03

typedef struct {
  bool guitar;
  bool bass;
  bool drums;
  bool vocals;
} tInstrument;

extern GLcoordsX screenInstruments_selectionX[];
extern GLcoordsY screenInstruments_selectionY[];
extern GLcoordsX screenInstruments_selectionReset[];

extern tInstrument instrument_P1;
extern tInstrument instrument_P2;
extern tInstrument instrument_P3;
extern tInstrument instrument_P4;

extern ushort current_instrument;

GLvoid screenInstruments_highlighted(GLuint instSelection);
GLvoid screenInstruments_accept();
bool screenInstruments_buffer();
GLvoid screenInstruments();

#endif
