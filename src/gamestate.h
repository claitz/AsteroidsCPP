#pragma once
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include <vector>

enum class GameStateType {
    MainMenu,
    InGame,
    GameOver
};


class GameState {
public:
    int level = 1;
    int score = 0;
    int lives = Constants::STARTING_LIVES;

    Spaceship spaceship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    GameStateType currentState;

    GameState();

    void spawnAsteroids(int count);

    void update();

    void updateMainMenu();

    void updateInGame();

    void updateGameOver();

    void checkCollisions();

    void checkAsteroidCollisions();

    void checkBulletCollisions();

    void renderInGame() const;

    void renderMainMenu() const;

    void renderGameOver() const;

    void removeInactive();

    void addScore(int enemyLevel);

    void respawnSpaceship();

    static std::vector<Asteroid> subdivideAsteroid(Asteroid &parentAsteroid);

    void startGame();

    void nextLevel();

    void endGame();
};