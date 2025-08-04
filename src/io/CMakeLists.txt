set(IO_SRCS dictionary.c dictionary.h fileio.c fileio.h iniparser.c iniparser.h joypad.h keys.c keys.h languages.c languages.h prefs.c prefs.h themes.c themes.h unix2dos.h)
add_library(io STATIC ${IO_SRCS})
target_include_directories(io PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/..)
