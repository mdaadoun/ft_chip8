cmake_minimum_required(VERSION 3.14)
project(chip8)

set(CMAKE_CXX_STANDARD 98)

#add_subdirectory(3rdParty/glad EXCLUDE_FROM_ALL)
#add_subdirectory(3rdParty/sdl-2.0.20 EXCLUDE_FROM_ALL)
#add_subdirectory(3rdParty/imgui-1.88 EXCLUDE_FROM_ALL)

add_executable(chip8 src/main.cpp src/Chip8.cpp src/utils.cpp src/utils.hpp)

target_compile_options(chip8 PRIVATE -Wall -Wextra -Werror -Wpedantic)

#target_link_libraries(chip8 PRIVATE glad SDL2 imgui)
