#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT(Freeband, prealpha, ddrtist@gmail.com)
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([src/freeband.c])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB([GL], [glGetString], [], [AC_MSG_ERROR([OpenGL not found])])
AC_CHECK_LIB([GLU], [gluGetString], [], [AC_MSG_ERROR([GLU not found])])
AC_CHECK_LIB([glut], [glutInit], [], [AC_MSG_ERROR([GLUT not found])])
AC_CHECK_LIB([portaudio], [Pa_Initialize], [], [AC_MSG_ERROR([PortAudio not found])])
AC_CHECK_LIB([sndfile], [sf_open], [], [AC_MSG_ERROR([libsndfile not found])])
AC_CHECK_LIB([vorbis], [vorbis_comment_init], [], [AC_MSG_ERROR([Vorbis not found])])
AC_CHECK_LIB([vorbisfile], [ov_open], [], [AC_MSG_ERROR([Vorbisfile not found])])

dnl Mingw AC_CHECK_LIB([opengl32], [glGetString], [], [AC_MSG_ERROR([OpenGL not found])])
dnl Mingw AC_CHECK_LIB([glut32], [glutInit], [], [AC_MSG_ERROR([GLUT not found])])
dnl Mingw AC_CHECK_LIB([glu32], [gluGetString], [], [AC_MSG_ERROR([GLU not found])])

# Check for SDL
SDL_VERSION=1.2.0
AM_PATH_SDL($SDL_VERSION, :, AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))
CFLAGS="$CFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"
AC_CHECK_LIB([SDL_image], [IMG_Load], [], [AC_MSG_ERROR([SDL_image not found])])
AC_CHECK_LIB([SDL_ttf], [TTF_RenderUTF8_Blended], [], [AC_MSG_ERROR([SDL_ttf not found])])

# Check for OpenGL headers
AC_CHECK_HEADERS([GL/gl.h OpenGL/gl.h], [gl_found_header=yes])
AC_CHECK_HEADERS([GL/glu.h OpenGL/glu.h], [glu_found_header=yes])
AC_CHECK_HEADERS([GL/glut.h OpenGL/glut.h], [glu_found_header=yes])
CPPFLAGS="$fp_save_cppflags"
if test x"$gl_found_header" = xno || test x"$glu_found_header" = xno; then
  AC_MSG_FAILURE([No OpenGL headers found.])
fi

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([math.h])
AC_CHECK_HEADERS(ogg/ogg.h vorbis/vorbisfile.h)
# check for OpenGL include files
gl_found_header=no
glu_found_header=no
glut_found_header=no
fp_save_cppflags="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $X_CFLAGS"
AC_CHECK_HEADERS(SDL/SDL.h SDL/SDL_image.h SDL/SDL_ttf.h)

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# More CFLAGS we want
CFLAGS="$CFLAGS -D__DEBUG__ -D__XBOX360XPLORER__ -Wall -Wextra -Wfatal-errors -ansi -std=c99 -pedantic -pipe"

# Checks for library functions.

AC_CONFIG_FILES([ Makefile ])
AC_CONFIG_FILES([ src/Makefile ])
AC_CONFIG_FILES([ src/audio/Makefile ])
AC_CONFIG_FILES([ src/graphics/Makefile ])
AC_CONFIG_FILES([ src/input/Makefile ])
AC_CONFIG_FILES([ src/io/Makefile ])
AC_CONFIG_FILES([ src/screens/Makefile ])
AC_OUTPUT
