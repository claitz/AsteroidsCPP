#pragma once
#include "raylib.h"
#include <vector>

class Spaceship;

class Asteroid {
public:
    static Asteroid createAsteroid(int asteroidLevel, float asteroidX, float asteroidY);

    void update(Spaceship& spaceship);
    void draw() const;

    int level = 0;
    float x = 0.0f, y = 0.0f;
    float dx = 0.0f, dy = 0.0f;
    float radius = 0.0f;
    std::vector<Vector2> points = {};

    bool bDestroyed = false;
};
