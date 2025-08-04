set(AUDIO_SRCS audio.c audio.h ogg.c ogg.h sfx.c sfx.h track.c track.h)
add_library(audio STATIC ${AUDIO_SRCS})
target_include_directories(audio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/..)
