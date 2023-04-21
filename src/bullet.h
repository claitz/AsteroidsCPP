#pragma once
#include "raylib.h"

class Bullet {
public:
    float x, y; // Position
    float dx, dy; // Direction
    float speed; // Speed
    float lifetime; // Lifetime in seconds

    void createBullet(float startX, float startY, float angle, float startSpeed, float startLifetime);
    void update();
    void draw();
};
