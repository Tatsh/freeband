cmake_minimum_required(VERSION 3.31)
project(freeband VERSION 0.0.0)

include(FindPkgConfig)
include(GNUInstallDirs)

set(CMAKE_C_STANDARD 23)

if(WIN32)
  if(MSVC)
    set(_freeband_default_target_version 0x600)
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(_freeband_default_target_version 0x500)
  else()
    set(_freeband_default_target_version 0x501)
  endif()
  set(TARGET_VERSION ${_freeband_default_target_version}
      CACHE STRING "Target Windows version in 0xMMNN format.")
endif()

find_package(FreeGLUT REQUIRED)
find_package(OpenGL REQUIRED)
pkg_check_modules(PORTAUDIO portaudio-2.0 REQUIRED IMPORTED_TARGET GLOBAL)
pkg_check_modules(SDL12_COMPAT sdl12_compat REQUIRED IMPORTED_TARGET GLOBAL)
pkg_check_modules(SDL_IMAGE SDL_image REQUIRED IMPORTED_TARGET GLOBAL)
pkg_check_modules(SDL_TTF SDL_ttf REQUIRED IMPORTED_TARGET GLOBAL)
pkg_check_modules(SNDFILE sndfile REQUIRED IMPORTED_TARGET GLOBAL)

add_subdirectory(src)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Tatsh")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE.txt)
find_program(NSIS makensis)
if(WIN32 AND NSIS)
  set(CPACK_GENERATOR "NSIS;ZIP")
elseif(WIN32)
  set(CPACK_GENERATOR "ZIP")
endif()
if(WIN32)
  set(CPACK_NSIS_DEFINES "RequestExecutionLevel user
!define /date CURRENT_YEAR \\\"%Y\\\"
VIProductVersion \\\"${PROJECT_VERSION}.0\\\"
VIAddVersionKey \\\"ProductName\\\" \\\"${PROJECT_NAME}\\\"
VIAddVersionKey \\\"CompanyName\\\" \\\"Tatsh\\\"
VIAddVersionKey \\\"FileDescription\\\" \\\"${PROJECT_NAME} installer.\\\"
VIAddVersionKey \\\"FileVersion\\\" \\\"${PROJECT_VERSION}\\\"
VIAddVersionKey \\\"ProductVersion\\\" \\\"${PROJECT_VERSION}.0\\\"
VIAddVersionKey \\\"LegalCopyright\\\" \\\"Copyright © \\\${CURRENT_YEAR} Tatsh.\\\"
VIAddVersionKey \\\"Comments\\\" \\\"https://github.com/Tatsh/freeband\\\"")
  set(CPACK_NSIS_INSTALL_ROOT "$LOCALAPPDATA/Programs")
  set(CPACK_NSIS_CONTACT "https://github.com/Tatsh/freeband/issues")
  set(CPACK_NSIS_MANIFEST_DPI_AWARE ON)
  set(CPACK_NSIS_MODIFY_PATH OFF)
  set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/Tatsh/freeband/issues")
  if(NOT CPACK_SYSTEM_NAME)
    if(CMAKE_GENERATOR_PLATFORM)
      string(TOLOWER "${CMAKE_GENERATOR_PLATFORM}" __freeband_arch)
    else()
      string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" __freeband_arch)
    endif()
    if(__freeband_arch MATCHES "^(arm64|aarch64)$")
      set(CPACK_SYSTEM_NAME winarm64)
    elseif(__freeband_arch MATCHES "^(amd64|x86_64|x64)$")
      set(CPACK_SYSTEM_NAME win64)
    elseif(__freeband_arch MATCHES "^(i[3-6]86|x86|win32)$")
      set(CPACK_SYSTEM_NAME win32)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(CPACK_SYSTEM_NAME win64)
    else()
      set(CPACK_SYSTEM_NAME win32)
    endif()
  endif()
else()
  set(CPACK_GENERATOR "ZIP")
  if(NOT CPACK_SYSTEM_NAME)
    string(TOLOWER "${CMAKE_SYSTEM_NAME}" CPACK_SYSTEM_NAME)
  endif()
endif()
set(CPACK_THREADS 0)
set(CPACK_PACKAGE_FILE_NAME
    ${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${CPACK_SYSTEM_NAME}-${CMAKE_BUILD_TYPE})
include(CPack)
