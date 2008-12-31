#ifndef GRAPHICS_H
#define GRAPHICS_H

#define MAX_IMAGES 20

extern bool graphics_loading; /* Whether or not we are buffering textures */

extern GLfloat buttonColour_green[];
extern GLfloat buttonColour_red[];
extern GLfloat buttonColour_yellow[];
extern GLfloat buttonColour_blue[];
extern GLfloat buttonColour_orange[];
extern GLfloat colour_blue_7CA4F6[];
extern GLfloat colour_yellow_F0FF07[];
extern GLfloat defaultAlpha[];
extern GLfloat defVertexZ[];            /* All flat facing user textures use these z values */
extern GLfloat fillBGVertexX[];         /* 'Fill entire background' positions */
extern GLfloat fillBGVertexY[];
extern GLfloat offscreenVertexXY[]; /* Offscreen coordinates */

extern GLUquadricObj *quadratic;

extern SDL_Color yellow;
extern SDL_Color white;

extern GLuint texture[]; /* Storage space for textures; this is the maximum at any given time */

bool graphics_initGL();
bool graphics_resizeWindow(GLuint width, GLuint height);

GLfloat graphics_centreAtX(GLfloat xyz, GLfloat width);
GLfloat graphics_scaleTextureHeight(GLuint pWidth, GLuint pHeight, GLfloat destWidth);
GLfloat graphics_scaleTextureWidth(GLuint pWidth, GLuint pHeight, GLfloat destHeight);

GLint graphics_loadTexture(const char *filename, GLuint index);

GLvoid graphics_clear();
GLvoid graphics_draw();
GLvoid graphics_initColours();
GLvoid graphics_positionTexture(GLfloat *vertexX, GLfloat *vertexY, GLfloat *vertexZ);

#endif
