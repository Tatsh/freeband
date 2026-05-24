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
  string(TIMESTAMP FREEBAND_COPYRIGHT_YEAR "%Y")
  configure_file("${CMAKE_SOURCE_DIR}/win32/freeband.rc.in"
                 "${CMAKE_CURRENT_BINARY_DIR}/freeband.rc" @ONLY)
  target_sources(freeband PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/freeband.rc")
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/freeband.rc"
                              PROPERTIES COMPILE_DEFINITIONS $<$<CONFIG:Release>:NDEBUG=1>)
endif()

if(APPLE)
  install(TARGETS freeband
          RUNTIME DESTINATION "Freeband.app/Contents/MacOS")
  configure_file("${CMAKE_SOURCE_DIR}/macos/Info.plist.in"
                 "${CMAKE_CURRENT_BINARY_DIR}/Info.plist" @ONLY)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/Info.plist"
          DESTINATION "Freeband.app/Contents")
  install(DIRECTORY GameData/languages
          DESTINATION "Freeband.app/Contents/Resources")
  install(DIRECTORY GameData/themes
          DESTINATION "Freeband.app/Contents/Resources")
  install(FILES GameData/preferences.ini
          DESTINATION "Freeband.app/Contents/Resources")
  find_program(SIPS_EXE sips REQUIRED)
  find_program(ICONUTIL_EXE iconutil REQUIRED)
  set(_freeband_icon_src "${CMAKE_CURRENT_SOURCE_DIR}/freeband.png")
  set(_freeband_iconset_dir "${CMAKE_CURRENT_BINARY_DIR}/Freeband.iconset")
  set(_freeband_icns "${CMAKE_CURRENT_BINARY_DIR}/Freeband.icns")
  add_custom_command(
    OUTPUT "${_freeband_icns}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${_freeband_iconset_dir}"
    COMMAND ${SIPS_EXE} -z 16 16 "${_freeband_icon_src}" --out
            "${_freeband_iconset_dir}/icon_16x16.png"
    COMMAND ${SIPS_EXE} -z 32 32 "${_freeband_icon_src}" --out
            "${_freeband_iconset_dir}/icon_16x16@2x.png"
    COMMAND ${SIPS_EXE} -z 32 32 "${_freeband_icon_src}" --out
            "${_freeband_iconset_dir}/icon_32x32.png"
    COMMAND ${SIPS_EXE} -z 64 64 "${_freeband_icon_src}" --out
            "${_freeband_iconset_dir}/icon_32x32@2x.png"
    COMMAND ${SIPS_EXE} -z 128 128 "${_freeband_icon_src}" --out
            "${_freeband_iconset_dir}/icon_128x128.png"
    COMMAND ${ICONUTIL_EXE} --convert icns --output "${_freeband_icns}"
            "${_freeband_iconset_dir}"
    DEPENDS "${_freeband_icon_src}"
    VERBATIM)
  add_custom_target(freeband_icns ALL DEPENDS "${_freeband_icns}")
  add_dependencies(freeband freeband_icns)
  install(FILES "${_freeband_icns}" DESTINATION "Freeband.app/Contents/Resources")
  install(CODE [[
    include(BundleUtilities)
    set(BU_CHMOD_BUNDLE_ITEMS TRUE)
    file(GLOB _freeband_extra_dirs
         "$ENV{HOME}/sdl1-libs/lib"
         "/opt/homebrew/lib"
         "/usr/local/lib")
    fixup_bundle(
      "${CMAKE_INSTALL_PREFIX}/Freeband.app/Contents/MacOS/freeband"
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
  if(NOT WIN32)
    configure_file("${CMAKE_SOURCE_DIR}/linux/sh.tat.freeband.desktop.in"
                   "${CMAKE_CURRENT_BINARY_DIR}/sh.tat.freeband.desktop" @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/sh.tat.freeband.desktop"
            DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/freeband.png"
            DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/128x128/apps
            RENAME sh.tat.freeband.png)
  endif()
endif()
if(WIN32)
  get_filename_component(_compiler_bin_dir ${CMAKE_C_COMPILER} DIRECTORY)
  install(
    RUNTIME_DEPENDENCY_SET
    freeband
    PRE_EXCLUDE_REGEXES
    [=[api-ms-]=]
    [=[ext-ms-]=]
    [[kernel32\.dll]]
    POST_EXCLUDE_REGEXES
    [=[.*system32\/.*\.dll]=]
    DIRECTORIES
    ${_compiler_bin_dir}
    $<TARGET_FILE_DIR:freeband>
    DESTINATION ${CMAKE_INSTALL_BINDIR})
  # sdl12-compat (SDL.dll) loads SDL2.dll at runtime through SDL_LoadObject,
  # so SDL2 is absent from the PE import graph that the walker above sees.
  install(FILES ${_compiler_bin_dir}/SDL2.dll DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
