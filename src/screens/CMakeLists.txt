set(SCREENS_SRC demo.c difficulty.c difficulty.h game.c game.h instruments.c instruments.h main.c main.h online.c options.c pause.c pause.h songlist.c songlist.h songs.c songs.h)
add_library(screens STATIC ${SCREENS_SRC})
target_include_directories(screens PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/..)
