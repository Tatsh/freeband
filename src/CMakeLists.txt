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
if(WIN32)
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU" AND CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT TARGET_VERSION
                                                                                MATCHES "^(0x501|0x6)")
    message(FATAL_ERROR
            "Invalid TARGET_VERSION for 64-bit. Must be XP (0x501) or higher. Got: ${TARGET_VERSION}"
    )
  endif()
  target_compile_definitions(freeband PRIVATE _WIN32_WINNT=${TARGET_VERSION}
                                              WINVER=${TARGET_VERSION})
endif()

if(APPLE)
  install(TARGETS freeband
          RUNTIME DESTINATION "freeband.app/Contents/MacOS")
  configure_file("${CMAKE_SOURCE_DIR}/macos/Info.plist.in"
                 "${CMAKE_CURRENT_BINARY_DIR}/Info.plist" @ONLY)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/Info.plist"
          DESTINATION "freeband.app/Contents")
  install(DIRECTORY GameData/languages
          DESTINATION "freeband.app/Contents/Resources")
  install(DIRECTORY GameData/themes
          DESTINATION "freeband.app/Contents/Resources")
  install(FILES GameData/preferences.ini
          DESTINATION "freeband.app/Contents/Resources")
  install(CODE [[
    include(BundleUtilities)
    set(BU_CHMOD_BUNDLE_ITEMS TRUE)
    file(GLOB _freeband_extra_dirs
         "$ENV{HOME}/sdl1-libs/lib"
         "/opt/homebrew/lib"
         "/usr/local/lib")
    fixup_bundle(
      "${CMAKE_INSTALL_PREFIX}/freeband.app/Contents/MacOS/freeband"
      ""
      "${_freeband_extra_dirs}")
  ]])
else()
  install(DIRECTORY GameData/languages DESTINATION ${CMAKE_INSTALL_DATADIR}/freeband)
  install(DIRECTORY GameData/themes DESTINATION ${CMAKE_INSTALL_DATADIR}/freeband)
  install(FILES GameData/preferences.ini DESTINATION ${CMAKE_INSTALL_DATADIR}/freeband)
  install(
    TARGETS freeband
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    RUNTIME_DEPENDENCY_SET freeband)
endif()
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
