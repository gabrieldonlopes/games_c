cmake_minimum_required(VERSION 3.10)
project(space-kid C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

add_executable(space-kid
    src/space-kid.c
    src/graph.c
    src/physics.c
)

target_include_directories(space-kid PRIVATE
    include
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(space-kid
    SDL2::SDL2
)