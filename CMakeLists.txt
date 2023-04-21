cmake_minimum_required(VERSION 3.25)
project(Asteroids)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_GENERATOR_PLATFORM x64)

if (UNIX)
    set(RAYLIB_PATH "/home/clait/raylib")
else()
    set(RAYLIB_PATH "E:/CPP/Libraries/raylib64")
endif (UNIX)

# Include raylib headers
include_directories(${RAYLIB_PATH}/include)

# Link raylib library
link_directories(${RAYLIB_PATH}/lib)

# Add source files
file(GLOB SOURCES "src/*.cpp" "src/*.h")

# Create the executable
add_executable(Asteroids ${SOURCES})

# Link the raylib library
if(UNIX)
    target_link_libraries(Asteroids raylib)
else()
    target_link_libraries(Asteroids raylib winmm)
endif(UNIX)