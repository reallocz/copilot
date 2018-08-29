cmake_minimum_required(VERSION 3.8)
project(presentor)

# Compiler flags
add_compile_options(-Wall -Wextra -Wpedantic)

# Executables
add_executable( debug 
    src/string.c
    src/window.c
    src/slide.c
    src/main.c
)

target_link_libraries( debug
    SDL2
    SDL2_ttf
    pthread
)
