#pragma once
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include <vector>

class GameState {
public:
    Spaceship spaceship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    GameState();

    void update();
};