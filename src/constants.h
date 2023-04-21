#pragma once
#include "raylib.h"

namespace Constants {

    // Screen
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;

    // Spaceship
    const int STARTING_LIVES = 3;
    const float SPACESHIP_SPEED = 120.f;
    const float SPACESHIP_ROT_SPEED = 100.f;
    const float SPACESHIP_RADIUS = 10.f;
    const Color SPACESHIP_COLOR = RAYWHITE;

    // Bullets
    const float BULLET_SPEED = 5.f;
    const float BULLET_LIFETIME = 2.5f;
    const float BULLET_RADIUS = 2.f;
    const Color BULLET_COLOR = RAYWHITE;

    //Enemy
    const int ENEMY_BASE_SCORE = 100;

    // Asteroids
    const int ASTEROID_COUNT = 10;
    const int ASTEROID_LEVELS = 3;
    const float ASTEROID_SPEED = 1.5f;
    const int ASTEROID_POINTS = 8;
    const Color ASTEROID_COLOR = DARKGRAY;

    // HUD
    const int FONT_SIZE = 20;
    const int FONT_SPACING = 10;
    const Color FONT_COLOR = RAYWHITE;

    const int FONT_SIZE_LARGE = 50;
}