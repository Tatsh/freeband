set(FREEBAND_SRCS freeband.c freeband.h nonstd.c nonstd.h)

add_subdirectory(audio)
add_subdirectory(graphics)
add_subdirectory(input)
add_subdirectory(io)
add_subdirectory(screens)

add_executable(freeband ${FREEBAND_SRCS})
target_link_libraries(
  freeband
  PRIVATE input
          audio
          screens
          io
          graphics
          FreeGLUT::freeglut
          OpenGL::GL
          OpenGL::GLU
          PkgConfig::PORTAUDIO
          PkgConfig::SDL12_COMPAT
          PkgConfig::SDL_IMAGE
          PkgConfig::SDL_TTF
          PkgConfig::SNDFILE)

install(DIRECTORY GameData/languages DESTINATION ${CMAKE_INSTALL_DATADIR}/freeband)
install(DIRECTORY GameData/themes DESTINATION ${CMAKE_INSTALL_DATADIR}/freeband)
install(FILES GameData/preferences.ini DESTINATION ${CMAKE_INSTALL_DATADIR}/freeband)
install(
  TARGETS freeband
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  RUNTIME_DEPENDENCY_SET freeband)
if(WIN32)
  if(MINGW)
    get_filename_component(_mingw_bin_dir ${CMAKE_C_COMPILER} DIRECTORY)
  endif()
  install(
    RUNTIME_DEPENDENCY_SET
    freeband
    PRE_EXCLUDE_REGEXES
    "."
    PRE_INCLUDE_REGEXES
    "SDL|sndfile|portaudio|freeglut|png|jpeg|tiff|webp|freetype|bz2|ogg|vorbis|FLAC|opus|mpg123|gcc|winpthread|stdc|iconv|zlib"
    DIRECTORIES
    ${CMAKE_INSTALL_PREFIX}/bin
    ${_mingw_bin_dir})
endif()
