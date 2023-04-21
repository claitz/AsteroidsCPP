#pragma once
#include <vector>

class SDL_Renderer;
class SDL_FPoint;
class Spaceship;

class Asteroid {

public:
    int level; // Level
    float x, y; // Position
    float dx, dy; // Velocity
    float radius; // Size
    std::vector<SDL_FPoint> points; // Points

    Asteroid createAsteroid(int asteroidLevel);

    void update(Spaceship& spaceship);

    bool collidesWith(Spaceship& spaceship);

    void draw(SDL_Renderer* renderer);
};
