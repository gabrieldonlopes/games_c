cmake_minimum_required(VERSION 3.10)
project(chess C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

add_executable(chess
    src/chess.c
    src/graph.c
)

target_include_directories(chess PRIVATE
    include
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(chess
    ${SDL2_LIBRARIES}
)