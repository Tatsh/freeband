DIST_SUBDIRS = GameData io
bin_PROGRAMS = freeband
SUBDIRS = audio graphics input screens .
freeband_SOURCES = freeband.c
freeband_DEPENDENCIES = input/libFreebandInput.a audio/libFreebandAudio.a screens/libFreebandScreens.a graphics/libFreebandGraphics.a
freeband_LDADD = input/libFreebandInput.a audio/libFreebandAudio.a  screens/libFreebandScreens.a graphics/libFreebandGraphics.a
