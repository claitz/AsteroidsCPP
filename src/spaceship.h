#pragma once
#include "constants.h"
#include "raylib.h"
#include <vector>

class GameState;

class Spaceship {
public:
    explicit Spaceship(GameState& gameState);

    void update();
    void draw();
    void shoot();

    // Setters
    void setThrust(bool bNewThrust) { bThrust = bNewThrust; }
    void setRotationDirection(float newRotationDirection) { rotationDirection = newRotationDirection; }
    void setDestroyed(bool bNewDestroyed) { bDestroyed = bNewDestroyed; }
    void setPosition(Vector2 newPosition) { position = newPosition; }
    void setVelocity(Vector2 newVelocity) { velocity = newVelocity; }

    // Getters
    bool isDestroyed() const { return bDestroyed; }
    Vector2 getPosition() const { return position; }
    float getRadius() const { return radius; }
    float getAngle() const { return angle; }
    Vector2 getVelocity() const { return velocity; }
    std::vector<Vector2> getShapePoints() const { return shapePoints; }

private:
    GameState& gameState;

    static void createSpaceship(Spaceship &spaceship);

    void move();

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
