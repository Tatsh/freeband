set(GRAPHICS_SRCS graphics.c graphics.h text.c text.h)
add_library(graphics STATIC ${GRAPHICS_SRCS})
target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/..)
