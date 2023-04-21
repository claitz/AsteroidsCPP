#pragma once
#include "constants.h"
#include "raylib.h"
#include <vector>

class GameState;

class Spaceship {
    GameState& gameState;

public:
    explicit Spaceship(GameState& gameState);

    static void createSpaceship(Spaceship &spaceship);

    void update();
    void draw();
    void setThrust(bool bNewThrust);
    void move();
    void die();
    void shoot();

    Vector2 velocity{};
    Vector2 position{};
    float angle{};
    float radius{};

    bool bThrust{};
    float speed{};
    float rotationSpeed{};
    float rotationDirection{};

    std::vector<Vector2> shapePoints;

    bool bDestroyed = false;
};
