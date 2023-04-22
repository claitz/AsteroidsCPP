#pragma once
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include <vector>

enum class GameStateType {
    MainMenu,
    InGame,
    Options,
    GameOver
};

class GameState {
public:
    GameState();

    void update();

    void renderInGame() const;

    void renderMainMenu() const;

    void renderOptions();

    void renderGameOver() const;

    void changeResolution(int newResolutionIndex);

    void addBullet(Bullet bullet) { bullets.push_back(bullet); }

    // Setters
    void setCurrentState(GameStateType newState) { currentState = newState; }

    // Getters
    GameStateType getCurrentState() const { return currentState; }
    Spaceship &getSpaceship() { return spaceship; }
    std::vector<Asteroid> &getAsteroids() { return asteroids; }
    std::vector<Bullet> &getBullets() { return bullets; }
    int getScore() const { return score; }
    int getLives() const { return lives; }
    int getLevel() const { return level; }

private:
    int level = 1;
    int score = 0;
    int lives = Constants::STARTING_LIVES;

    Spaceship spaceship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    GameStateType currentState;

    int currentResolutionIndex = 2; // 800x600

    Rectangle increaseResolutionButton;
    Rectangle decreaseResolutionButton;

    void init();

    void spawnAsteroids(int count);

    void updateMainMenu();

    void updateInGame();

    void updateOptions();

    void updateGameOver();

    void checkCollisions();

    void checkAsteroidCollisions();

    void checkBulletCollisions();

    void removeInactive();

    void addScore(int enemyLevel);

    void die();

    void respawnSpaceship();

    static std::vector<Asteroid> subdivideAsteroid(Asteroid &parentAsteroid);

    void startGame();

    void nextLevel();

    void endGame();

    void resetGame();

    static void centerWindow();
};