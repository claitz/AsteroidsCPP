#pragma once
#include "raylib.h"
#include <vector>
#include "spaceship.h"

class Asteroid {
public:
    static Asteroid createAsteroid(int asteroidLevel);

    void update(Spaceship& spaceship);
    void draw();
    bool collidesWith(Spaceship& spaceship);

    int level = 0;
    float x = 0.0f, y = 0.0f;
    float dx = 0.0f, dy = 0.0f;
    float radius = 0.0f;
    std::vector<Vector2> points = {};
    bool bDestroy = false;
};
