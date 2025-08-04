cmake_minimum_required(VERSION 3.31)
project(freeband)

include(FindPkgConfig)
include(GNUInstallDirs)

set(CMAKE_C_STANDARD 23)

find_package(FreeGLUT REQUIRED)
find_package(OpenGL REQUIRED)
pkg_check_modules(PORTAUDIO portaudio-2.0 REQUIRED IMPORTED_TARGET GLOBAL)
pkg_check_modules(SDL12_COMPAT sdl12_compat REQUIRED IMPORTED_TARGET GLOBAL)
pkg_check_modules(SDL_IMAGE SDL_image REQUIRED IMPORTED_TARGET GLOBAL)
pkg_check_modules(SDL_TTF SDL_ttf REQUIRED IMPORTED_TARGET GLOBAL)
pkg_check_modules(SNDFILE sndfile REQUIRED IMPORTED_TARGET GLOBAL)

add_subdirectory(src)
