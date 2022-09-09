cmake_minimum_required(VERSION 3.22)
project(graphics)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER ${CMAKE_SOURCE_DIR}/src/*.h)

SET(STB_SOURCE_DIR "lib/stb")

add_library(stb STATIC)

set_target_properties(stb PROPERTIES LINKER_LANGUAGE C)

target_sources(stb PRIVATE
        "${STB_SOURCE_DIR}/stb_c_lexer.h"
        "${STB_SOURCE_DIR}/stb_connected_components.h"
        "${STB_SOURCE_DIR}/stb_ds.h"
        "${STB_SOURCE_DIR}/stb_dxt.h"
        "${STB_SOURCE_DIR}/stb_easy_font.h"
        "${STB_SOURCE_DIR}/stb_herringbone_wang_tile.h"
        "${STB_SOURCE_DIR}/stb_hexwave.h"

        "${STB_SOURCE_DIR}/stb_image.h"
        "${STB_SOURCE_DIR}/stb_image_resize.h"
        "${STB_SOURCE_DIR}/stb_image_write.h"

        "${STB_SOURCE_DIR}/stb_include.h"
        "${STB_SOURCE_DIR}/stb_leakcheck.h"
        "${STB_SOURCE_DIR}/stb_rect_pack.h"
        "${STB_SOURCE_DIR}/stb_sprintf.h"
        "${STB_SOURCE_DIR}/stb_textedit.h"
        "${STB_SOURCE_DIR}/stb_tilemap_editor.h"
        "${STB_SOURCE_DIR}/stb_truetype.h")

target_include_directories(stb
        PUBLIC ${STB_SOURCE_DIR})

add_executable(graphics
        ${SRC}
        tests/other/widget.cpp)

target_link_libraries(graphics
        PUBLIC stb)

target_include_directories(graphics
        PUBLIC lib/stb)
