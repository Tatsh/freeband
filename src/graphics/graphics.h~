#define DEFAULT_TEXT_PT 72

extern bool menuQuit;
extern bool loading; /* Whether or not we are buffering textures */

extern char defaultFont[];
extern char bitstreamFont[];
extern char bitstreamMonoBoldFont[];
extern char freeSansFont[];
extern char freeSansBoldFont[];

extern GLfloat buttonColour_green[];
extern GLfloat buttonColour_red[];
extern GLfloat buttonColour_yellow[];
extern GLfloat buttonColour_blue[];
extern GLfloat buttonColour_orange[];
extern GLfloat colour_blue_7CA4F6[];
extern GLfloat colour_yellow_F0FF07[];
extern GLfloat defaultAlpha[];
extern GLfloat defVertexZ[];            /* All flat facing user textures use this z value */
extern GLfloat fillBGVertexX[];         /* 'Fill entire background' position */
extern GLfloat fillBGVertexY[];
extern GLfloat offscreenVertexXY[];
extern GLUquadricObj *quadratic;

extern SDL_Color yellow;
extern SDL_Color white;

bool initGL();
bool resizeWindow(GLuint width, GLuint height);

GLuint loadText(char *input, TTF_Font *font, SDL_Color color, GLuint index);
GLuint loadTexture(const char *filename, GLuint index);

GLvoid clearScreen();
GLvoid drawFreeband();
GLvoid positionTexture(GLfloat *vertexX, GLfloat *vertexY, GLfloat *vertexZ);
GLvoid setupColors();

