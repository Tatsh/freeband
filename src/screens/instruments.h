#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#define en_select_instrument "SELECT INSTRUMENT"
#define en_guitar "GUITAR"
#define en_bass "BASS"
#define en_drums "DRUMS"
#define en_vocals "VOCALS"

typedef struct {
  bool guitar;
  bool bass;
  bool drums;
  bool vocals;
} tInstrument;

extern GLcoordsX screenInstruments_selectionX[];
extern GLcoordsY screenInstruments_selectionY[];
extern GLcoordsX screenInstruments_selectionReset[];

extern GLuint screenInstruments_nSelection;

extern tInstrument instrument_P1;
extern tInstrument instrument_P2;
extern tInstrument instrument_P3;
extern tInstrument instrument_P4;

GLvoid screenInstruments_highlighted(GLuint instSelection);
GLvoid screenInstruments_accept();
bool screenInstruments_buffer();
GLvoid screenInstruments();

#endif
