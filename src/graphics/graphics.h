#ifndef GRAPHICS_H
#define GRAPHICS_H

#define MAX_IMAGES 20

typedef char texture_p;
typedef GLfloat GLalpha;
typedef GLfloat GLcolour;
typedef GLfloat GLcoordsX;
typedef GLfloat GLcoordsY;
typedef GLfloat GLcoordsZ;
typedef GLuint texture_i;

extern bool graphics_loading; /* Whether or not we are buffering textures */

extern GLalpha defaultAlpha[];

extern GLcolour buttonColour_green[];
extern GLcolour buttonColour_red[];
extern GLcolour buttonColour_yellow[];
extern GLcolour buttonColour_blue[];
extern GLcolour buttonColour_orange[];
extern GLcolour colour_blue_7CA4F6[];
extern GLcolour colour_yellow_F0FF07[];

extern GLcoordsX offscreenVertexXY[]; /* Offscreen coordinates */
extern GLcoordsX fillBGVertexX[];     /* 'Fill entire background' positions */
extern GLcoordsY fillBGVertexY[];
extern GLcoordsZ defVertexZ[];        /* All flat facing user textures use these z values */

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
