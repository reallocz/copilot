cmake_minimum_required(VERSION 3.8)
project(copilot)

# Compiler flags
set(CMAKE_C_COMPILER clang)
add_compile_options(-std=c11)
add_compile_options(-Wall -Wextra -Wpedantic)

# Executables
add_executable( debug 
    src/string.c
    src/view/style.c
    src/view/view.c
    src/renderer.c
    src/window.c
    src/slide.c
    src/main.c
)

target_link_libraries( debug
    SDL2
    SDL2_ttf
    pthread
)
