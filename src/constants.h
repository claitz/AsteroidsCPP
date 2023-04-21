#pragma once
#include "raylib.h"

namespace Constants {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    // Spaceship
    const int STARTING_LIVES = 3;
    const float SPACESHIP_SPEED = 100.f;
    const float SPACESHIP_ROT_SPEED = 100.f;
    const Color SPACESHIP_COLOR = RAYWHITE;

    // Bullets
    const float BULLET_SPEED = 5.f;
    const float BULLET_LIFETIME = 2.f;
    const float BULLET_RADIUS = 2.f;
    const Color BULLET_COLOR = BLUE;

    //Enemy
    const int ENEMY_BASE_SCORE = 100;

    // Asteroids
    const int ASTEROID_COUNT = 5;
    const int ASTEROID_LEVELS = 3;
    const float ASTEROID_SPEED = 1.5f;
    const int ASTEROID_POINTS = 8;
    const Color ASTEROID_COLOR = DARKGRAY;
}