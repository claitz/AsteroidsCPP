#pragma once
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include <vector>

class GameState {
public:
    int level = 1;
    int score = 0;
    int lives = Constants::STARTING_LIVES;

    Spaceship spaceship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    bool bDestroyed = false;

    GameState();

    void spawnInitialAsteroids();

    void update();

    void checkCollisions();

    void checkAsteroidCollisions();

    void checkBulletCollisions();

    void renderHUD() const;

    void removeInactive();

    void addScore(int enemyLevel);

    void respawnSpaceship();
};