#pragma once
#include <vector>
#include <raylib.h>
#include "constants.h"

class Asteroid;

class Bullet {
public:
    float x, y; // Position
    float dx, dy; // Direction
    float speed; // Speed
    float lifetime = Constants::BULLET_LIFETIME; // Lifetime in seconds
    float radius = Constants::BULLET_RADIUS; // Radius
    Color color = Constants::BULLET_COLOR; // Color

    bool bDestroyed = false;

    void createBullet(float startX, float startY, float angle, float startSpeed);
    void update();
    void draw();
};
