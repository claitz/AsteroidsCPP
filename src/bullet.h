#pragma once
#include "raylib.h"

class Bullet {
public:
    float x, y; // Position
    float dx, dy; // Direction
    float speed; // Speed
    int lifetime; // Lifetime in frames

    void createBullet(float startX, float startY, float angle, float startSpeed, int startLifetime);
    void update();
    void draw();
};
