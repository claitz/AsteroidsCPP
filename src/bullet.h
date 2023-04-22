#pragma once
#include <vector>
#include <raylib.h>
#include "constants.h"

class Asteroid;

class Bullet {
public:
    void createBullet(float startX, float startY, float angle, float startSpeed);
    void update();
    void draw() const;

    // Setters
    void setDestroyed(bool bNewDestroyed) { bDestroyed = bNewDestroyed; }

    // Getters
    float getX() const { return x; }
    float getY() const { return y; }
    float getSpeed() const { return speed; }
    float getLifetime() const { return lifetime; }
    float getRadius() const { return radius; }
    Color getColor() const { return color; }
    bool isDestroyed() const { return bDestroyed; }

private:
    float x{}, y{}; // Position
    float dx{}, dy{}; // Direction
    float speed{}; // Speed
    float lifetime = Constants::BULLET_LIFETIME; // Lifetime in seconds
    float radius = Constants::BULLET_RADIUS; // Radius
    Color color = Constants::BULLET_COLOR; // Color

    bool bDestroyed = false;
};
