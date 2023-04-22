#pragma once
#include "raylib.h"
#include <vector>

class Spaceship;

class Asteroid {
public:
    static Asteroid createAsteroid(int asteroidLevel, float asteroidX, float asteroidY);

    void update(Spaceship& spaceship);
    void draw() const;

    // Getters
    int getLevel() const { return level; }
    float getX() const { return x; }
    float getY() const { return y; }
    float getDX() const { return dx; }
    float getDY() const { return dy; }
    float getRadius() const { return radius; }
    const std::vector<Vector2>& getPoints() const { return points; }
    bool isDestroyed() const { return bDestroyed; }

    // Setters
    void setLevel(int newLevel) { level = newLevel; }
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setDX(float newDX) { dx = newDX; }
    void setDY(float newDY) { dy = newDY; }
    void setRadius(float newRadius) { radius = newRadius; }
    void setPoints(const std::vector<Vector2>& newPoints) { points = newPoints; }
    void setDestroyed(bool newDestroyed) { bDestroyed = newDestroyed; }

private:
    int level = 0;
    float x = 0.0f, y = 0.0f;
    float dx = 0.0f, dy = 0.0f;
    float radius = 0.0f;
    std::vector<Vector2> points = {};

    bool bDestroyed = false;
};
