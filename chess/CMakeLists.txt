cmake_minimum_required(VERSION 3.10)
project(chess C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(chess
    src/chess.c
    src/graph.c
    src/game.c
    src/input.c
)

target_include_directories(chess PRIVATE
    include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(chess
    SDL2::SDL2
    SDL2_image::SDL2_image
)