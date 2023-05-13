cmake_minimum_required(VERSION 3.11) # Minimum for FetchContent
project(Asteroids)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
            DOWNLOAD_EXTRACT_TIMESTAMP true
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Add source files
file(GLOB SOURCES "src/*.cpp" "src/*.h")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
#set(raylib_VERBOSE 1)

# Link raylib
if(UNIX)
    target_link_libraries(${PROJECT_NAME} raylib)
else()
    target_link_libraries(${PROJECT_NAME} raylib winmm)

    # Static link on Windows
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

    # Hide console window on Windows Release builds
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")
    endif()
endif(UNIX)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()