set(INPUT_SRCS input.c input.h screenDifficulty.c screenDifficulty.h screenGame.c screenGame.h screenInstruments.c screenInstruments.h screenMain.c screenMain.h screenPause.c screenPause.h screenSongs.c screenSongs.h)
add_library(input STATIC ${INPUT_SRCS})
target_include_directories(input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/..)
