cmake_minimum_required(VERSION 3.22)
project(renderer C)

set(CMAKE_C_STANDARD 99)

add_library(glad glad/src/gl.c)
include_directories(glad/include)

add_executable(renderer main.c sdl.c debug.c gl.c gl.h)
target_link_libraries(renderer SDL2 SDL2_image glad)
