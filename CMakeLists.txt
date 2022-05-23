cmake_minimum_required(VERSION 3.22)
project(renderer C)

set(CMAKE_C_STANDARD 90)

add_executable(renderer main.c)
target_link_libraries(renderer SDL2 SDL2_image)
