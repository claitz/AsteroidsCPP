cmake_minimum_required(VERSION 3.25)
project(Asteroids)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SDL2_PATH "E:\\CPP\\Libraries\\SDL2-mingw")
include_directories(${SDL2_PATH}/include)
link_directories(${SDL2_PATH}/lib)

add_executable(Asteroids src/main.cpp src/asteroid.cpp src/asteroid.h src/constants.h src/utils.h src/spaceship.cpp src/spaceship.h)

target_link_libraries(Asteroids SDL2 SDL2main)
