cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

# Set The name of this Project.
project(Space-Dance)

# Optional: Configure /path/to in your system file directory if SDL is not found.
set(CMAKE_PREFIX_PATH "/path/to/SDL2;/path/to/SDL2_ttf" ${CMAKE_PREFIX_PATH})

# Add SDL2 CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Add all C source files under the src directory.
file(GLOB SOURCES "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add all headers files under the include directory.
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add all assets under the assets directory.
target_include_directories(${PROJECT_NAME} PRIVATE assets)

# Add SDL2 libraries.
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::TTF SDL2::Mixer)

# Add run command.
add_custom_target(
    run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/assets
    COMMENT "Runnig Project..."
)
