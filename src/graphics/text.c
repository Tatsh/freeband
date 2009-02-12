#include "../freeband.h"
#include "graphics.h"
#include "text.h"

/* Always extern these. Please keep them separated by a line, and alphabetised.
   Name variables as such:
   char path_<fontStyle>_<fontName>[];
   fontStyles: regular, bold, italic, boldItalic */
font_p path_bold_bitstreamVeraSans[] = "GameData/themes/default/fonts/bold-bitstream-vera-sans-mono.ttf";
font_p path_bold_bitstreamVeraSansMono[] = "GameData/themes/default/fonts/bold-bitstream-vera-sans.ttf";
font_p path_bold_freeSans[] = "GameData/themes/default/fonts/bold-freesans.ttf";

font_p path_italic_crillee[] = "GameData/themes/default/fonts/italic-crillee.ttf";

font_p path_regular_freeSans[] = "GameData/themes/default/fonts/regular-freesans.ttf";
/* End font paths */

GLint text_getHeight(const char text[], TTF_Font *font) {
  SDL_Surface *temp;
  GLint height;
  
  if ((temp = TTF_RenderUTF8_Blended(font, text, white)))
    height = temp->h;
  else
    return -1;
  
  if (temp)
    SDL_FreeSurface(temp);
  
  return height;
}

GLint text_getWidth(const char text[], TTF_Font *font) {
  SDL_Surface *temp;
  GLint width;

  if ((temp = TTF_RenderUTF8_Blended(font, text, white)))
    width = temp->w;
  else
    return -1;
  
  if (temp)
    SDL_FreeSurface(temp);
  
  return width;
}

GLfloat text_scaleWidth(const char text[], TTF_Font *font, GLfloat textureHeight) {
  return graphics_scaleTextureWidth(text_getWidth(text, font), text_getHeight(text, font), textureHeight);
}

GLvoid text_position(GLfloat vertexX[], GLfloat vertexY[], GLfloat vertexZ[]) { /* Wrapper */
  graphics_positionTexture(vertexX, vertexY, vertexZ);
  return;
}

GLint text_load(const char input[], TTF_Font *font, SDL_Color color) {
  SDL_Surface *textTexture;
  GLuint i = 0;
  
  /* Use SDL_ttf to render text */
  if ( (textTexture = TTF_RenderUTF8_Blended(font, input, color)) ) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &text[i]);
    glBindTexture(GL_TEXTURE_2D, text[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, textTexture->w, textTexture->h, GL_RGBA, GL_UNSIGNED_BYTE, textTexture->pixels);
  }
  else {
    fprintf(stderr, "text.c: text_load(): SDL_ttf could render '%s': %s\n", input, TTF_GetError());
    fb_quit(1);
  }

  if (textTexture) /* Clean up */
    SDL_FreeSurface(textTexture);
  else
    return -1;
  
  return text[i];
}
