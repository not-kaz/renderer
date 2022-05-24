cmake_minimum_required(VERSION 3.22)
project(renderer C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -O0)

add_library(glad glad/src/gl.c)
include_directories(glad/include cglm/include)

add_executable(renderer main.c util.c sdl.c gl.c shader.c texture.c)
target_link_libraries(renderer SDL2 SDL2_image glad m)
