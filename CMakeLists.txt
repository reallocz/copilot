cmake_minimum_required(VERSION 3.8)
project(presentor)

# Compiler flags
add_compile_options(-Wall -Wextra -Wpedantic)

# Executables
add_executable( debug 
    src/main.cc
    src/display.cc
)

target_link_libraries( debug
    SDL2
    pthread
)
