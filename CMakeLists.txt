cmake_minimum_required(VERSION 3.29)

project(Space-Dance)
set(CMAKE_CXX_STANDARD 20)

# Add /path/to/sdl in your system file directory if not found.
set(CMAKE_PREFIX_PATH "/usr/local/SDL2;/usr/local/SDL2_ttf;/opt/local/SDL2_ttf" ${CMAKE_PREFIX_PATH})

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Add all c source files under the src directory.
file(GLOB SOURCES "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include resources)

# Add SDL2 library
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::TTF)
