/* These are separated to allow 100% 'legal builds' for distros like gNewSense and for anyone
   else who feels the need. */
/* Supported formats:
   - AC3 (liba52)
   - MP3 (lame)
*/

#include <stdio>
#include "a52dec/a52.h"
#include "lame/lame.h"

char findCodec();

void playNonfree();
