#pragma once
#include <map>
#include "raylib.h"

namespace Constants {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    // Starting values
    const int STARTING_LIVES = 3;
    const int STARTING_POSITION_X = 400;
    const int STARTING_POSITION_Y = 300;

    // Spaceship
    const float SPACESHIP_SPEED = 100.f;
    const float SPACESHIP_ROT_SPEED = 100.f;

    // Bullets
    const float BULLET_SPEED = 5.f;
    const float BULLET_LIFETIME = 5.f;
    const float BULLET_RADIUS = 2.f;
    const Color BULLET_COLOR = BLUE;

    // Asteroids
    const int ASTEROID_COUNT = 5;
    const int ASTEROID_LEVELS = 3;
    const float ASTEROID_SPEED = 1.5f;
    const int ASTEROID_POINTS = 8;
}