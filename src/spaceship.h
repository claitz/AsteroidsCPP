#pragma once
#include "constants.h"
#include "raylib.h"
#include <vector>

class GameState;

class Spaceship {
    GameState& gameState;

public:
    Spaceship(GameState& gameState);

    static void createSpaceship(Spaceship &spaceship);

    void update();
    void draw();
    void setThrust(bool bThrust);
    void move();
    void die();
    void respawn();
    void shoot();

    int lives = Constants::STARTING_LIVES;
    Vector2 velocity{};
    Vector2 position{};
    float angle{};
    float radius{};

    bool bThrust{};
    float speed{};
    float rotationSpeed{};
    float rotationDirection{};

    std::vector<Vector2> shapePoints;
};
