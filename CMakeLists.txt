cmake_minimum_required(VERSION 3.29)
project(Space-Dance)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(Space-Dance src/main.c)

target_link_libraries(Space-Dance PUBLIC SDL2::SDL2 SDL2_ttf::SDL2_ttf)
target_include_directories(Space-Dance PUBLIC "src/components")