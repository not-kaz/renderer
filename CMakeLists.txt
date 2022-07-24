cmake_minimum_required(VERSION 3.22)
project(renderer C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS -O0)

IF (WIN32)
    set(SDL2_INCLUDE_DIRS
            "${CMAKE_CURRENT_LIST_DIR}/sdl2/include"
            "${CMAKE_CURRENT_LIST_DIR}/sdl2_image/include")
    set(SDL2_LIB_DIR
            "${CMAKE_CURRENT_LIST_DIR}/sdl2/lib"
            "${CMAKE_CURRENT_LIST_DIR}/sdl2_image/lib")

    include_directories(${SDL2_INCLUDE_DIRS})
    link_directories(${SDL2_LIB_DIR})
ELSE()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_Image REQUIRED)
ENDIF ()

add_library(glad glad/src/gl.c)
include_directories(glad/include cglm/include)

add_executable(renderer main.c util.c sdl.c gl.c shader.c texture.c)

IF (WIN32)
    target_link_libraries(renderer mingw32 SDL2main SDL2 SDL2_Image glad)
ELSE ()
    target_link_libraries(renderer SDL2 SDL2_image glad m)
ENDIF ()

