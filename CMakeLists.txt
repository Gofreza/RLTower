cmake_minimum_required(VERSION 3.10)
project(GameProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform-specific configuration
if(WIN32)
    # Windows-specific paths (adjust to where you extracted SDL2)
    set(SDL2_DIR "$ENV{HOME}/Documents/cross-compile/windows-libs/SDL2-2.32.10/x86_64-w64-mingw32")
    set(SDL2_TTF_DIR "$ENV{HOME}/Documents/cross-compile/windows-libs/SDL2_ttf-2.24.0/x86_64-w64-mingw32")
    set(SDL2_IMAGE_DIR "$ENV{HOME}/Documents/cross-compile/windows-libs/SDL2_image-2.8.8/x86_64-w64-mingw32")
    
    include_directories(
        ${SDL2_DIR}/include
        ${SDL2_DIR}/include/SDL2
        ${SDL2_TTF_DIR}/include
        ${SDL2_IMAGE_DIR}/include
        /opt/homebrew/Cellar/nlohmann-json/3.12.0/include
    )
    
    link_directories(
        ${SDL2_DIR}/lib
        ${SDL2_TTF_DIR}/lib
        ${SDL2_IMAGE_DIR}/lib
    )
elseif(APPLE)
    # macOS paths
    include_directories(
        /opt/homebrew/Cellar/sdl2/2.32.10/include
        /opt/homebrew/Cellar/sdl2/2.32.10/include/SDL2
        /opt/homebrew/Cellar/sdl2_ttf/2.24.0/include
        /opt/homebrew/Cellar/sdl2_image/2.8.8/include
        /opt/homebrew/Cellar/nlohmann-json/3.12.0/include
    )
    
    link_directories(
        /opt/homebrew/Cellar/sdl2/2.32.10/lib
        /opt/homebrew/Cellar/sdl2_ttf/2.24.0/lib
        /opt/homebrew/Cellar/sdl2_image/2.8.8/lib
    )
endif()

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/**/*.cpp")

# Create executable
if(WIN32)
    add_executable(RLTower WIN32 ${SOURCES})  # WIN32 flag hides console
else()
    add_executable(RLTower ${SOURCES})
endif()

# Link libraries - ORDER MATTERS on Windows!
if(WIN32)
    target_link_libraries(RLTower PRIVATE 
        mingw32
        SDL2main
        SDL2
        SDL2_ttf
        SDL2_image
    )
    set_target_properties(RLTower PROPERTIES SUFFIX ".exe")
elseif(APPLE)
    target_link_libraries(RLTower PRIVATE 
        SDL2 
        SDL2_ttf 
        SDL2_image
    )
endif()

# Set additional compiler flags for debugging
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(RLTower PRIVATE -Wall -Wextra -g)
    if(NOT WIN32)
        # AddressSanitizer may not work well with cross-compilation
        target_compile_options(RLTower PRIVATE -fsanitize=address)
        target_link_libraries(RLTower PRIVATE -fsanitize=address)
    endif()
endif()

# Custom target to run lldb (macOS only)
if(NOT WIN32)
    add_custom_target(debug
        COMMAND lldb ${CMAKE_BINARY_DIR}/RLTower
        DEPENDS RLTower
        COMMENT "Running lldb with RLTower executable"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()