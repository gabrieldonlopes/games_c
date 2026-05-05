cmake_minimum_required(VERSION 3.10)
project(space-kid C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Método mais simples: deixa o CMake encontrar automaticamente
find_package(SDL2 REQUIRED)

add_executable(space-kid
    src/space-kid.c
    src/graph.c
    src/physics.c
    src/game.c
    src/map.c
)

target_include_directories(space-kid PRIVATE
    include
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(space-kid
    ${SDL2_LIBRARIES}
    m
)

# Apenas copia DLL no Windows se existir
if(WIN32)
    # Tenta encontrar SDL2.dll automaticamente
    get_target_property(SDL2_LOCATION SDL2::SDL2 IMPORTED_LOCATION_RELEASE)
    if(NOT SDL2_LOCATION)
        get_target_property(SDL2_LOCATION SDL2::SDL2 IMPORTED_LOCATION)
    endif()
    
    if(SDL2_LOCATION AND EXISTS "${SDL2_LOCATION}")
        add_custom_command(TARGET space-kid POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL2_LOCATION}"
                $<TARGET_FILE_DIR:space-kid>
        )
    endif()
endif()