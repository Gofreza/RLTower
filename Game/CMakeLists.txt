cmake_minimum_required(VERSION 3.10)
project(GameProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    /opt/homebrew/Cellar/sdl2/2.30.6/include
    /opt/homebrew/Cellar/sdl2/2.30.6/include/SDL2
    /opt/homebrew/Cellar/sdl2_ttf/2.22.0/include
    /opt/homebrew/Cellar/sdl2_image/2.8.2_1/include
    /opt/homebrew/Cellar/nlohmann-json/3.11.3/include
)

# Library directories
link_directories(
    /opt/homebrew/Cellar/sdl2/2.30.6/lib
    /opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib
    /opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib
)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/**/*.cpp")

# Create executable
add_executable(game ${SOURCES})

# Link libraries
target_link_libraries(game PRIVATE SDL2 SDL2_ttf SDL2_image)

# TO BUILD IN DEBUG MODE
# cmake -DCMAKE_BUILD_TYPE=Debug ..
# make

# Set additional compiler flags for debugging
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(game PRIVATE -Wall -Wextra -g -fsanitize=address)
    target_link_libraries(game PRIVATE -fsanitize=address)
endif()

# Custom target to run lldb
add_custom_target(debug
    COMMAND lldb ${CMAKE_BINARY_DIR}/game
    DEPENDS game
    COMMENT "Running lldb with game executable"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
