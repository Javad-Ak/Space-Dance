cmake_minimum_required(VERSION 3.29)
project(Space-Dance)

set(CMAKE_CXX_STANDARD 20)

add_executable(Space-Dance
        src/main.c
        src/gameLoop.c
        src/menu.c)

target_include_directories(Space-Dance PUBLIC include)

find_package(SDL2 REQUIRED)
target_link_libraries(Space-Dance PUBLIC SDL2::SDL2)

find_package(SDL2_ttf REQUIRED)
target_link_libraries(Space-Dance PUBLIC SDL2_ttf::SDL2_ttf)
