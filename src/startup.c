#include <stdio.h>

#include "debug.h"
#include "error.h"
#include "test.h"
#ifdef __WINDOWS__
#include "windows.h"
#endif

int main(int argc, char *argv[])
{
  bool debugMode = false;
  
  /* System requirements test */
  if(testSysReqs() != 0)
    showSysStats();
    showSysReqs();
    printf("Your computer does not meet recommended system requirements. Continue anyway (y/n)?");
    testSysReqsContinue();

 /* SDL and SDL audio test */
 if(testSDL() != 0 || testSDLSound() != 0)
    printf("Problem with SDL. Quiting...\n");
    return 1;
  
  /* OpenGL test */
  if(testOpenGL() != 0)
    printf("Problem with OpenGL. Quitting...\n");
    return 1;

#ifdef __WINDOWS__
  /* For Windows, a DirectX test */ 
  if(testDirectX() != 0)
      printf("Problem with DirectX. Quitting...\n");
      reutrn 1;
#endif
  
  /* Make sure all necessary resource files are present */
  if(testNeededFiles() != 0)
    printf("Some files missing. Quitting...\n");
    showFilesMissing();
    return 1;
}
