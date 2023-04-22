# Asteroids

A clone of the classic Atari's Asteroids game.

The game is being developed in C++ and [Raylib](https://github.com/raysan5/raylib).

## Features

- [x] Menu
- [x] Settings
- [x] Endless Gameplay
- [ ] Pause
- [ ] Sound Effects
- [ ] Music
- [ ] High Score

## Controls

- **W/A/S/D or Arrow Keys**: Move
- **Space**: Shoot
- **Esc**: Exit/Pause
- **O**: Options
- **R**: Restart
- **Enter**: Select

# Building

## Prerequisites

- C++ Compiler with C++11 support
- [Raylib](https://github.com/raysan5/raylib) library (fetched automatically by CMake)
- [CMake](https://cmake.org/) (3.11 or higher)

## Windows

1. Clone the repository
2. Install a C++ compiler, such as Visual Studio, MinGW, or Cygwin.
3. Install CMake
4. Open a terminal and navigate to the repository folder
5. Run:
    ```bash
    mkdir build
    cd build
    cmake .. -G "Visual Studio 16 2019"  # Replace with your compiler
    cmake --build . --config Release
    ```
6. The executable will be in `build/Release/`

## Linux

1. Clone the repository
2. Install the required packages:
    ```bash
    sudo apt-get install build-essential cmake libraylib-dev
    ```
3. Open a terminal and navigate to the repository folder
4. Run:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
5. The executable will be in `build/`

# Screenshots
![AsteroidCPP Gameplay](https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExNTkxNTNlZTFjMDIwMWJmZTY4ZWU2MmVmYTBmNjI0YzhkOGIwMGNjYSZlcD12MV9pbnRlcm5hbF9naWZzX2dpZklkJmN0PWc/gpiTxrImfJGCwYCKgs/giphy.gif?text=AsteroidsCPP)

![AsteroidCPP Main Screen](https://imgur.com/Da09sci.png)

![AsteroidCPP Screenshot](https://imgur.com/6Ps9tFE.png)

# License

[MIT License](https://choosealicense.com/licenses/mit/)


