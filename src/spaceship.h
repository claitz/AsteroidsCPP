#pragma once
#include "raylib.h"
#include <vector>
#include "bullet.h"
#include "constants.h"

class Spaceship {
public:
    static Spaceship createSpaceship();

    void update();
    void draw();
    void move();
    void die();
    void respawn();
    void shoot();

    int lives = Constants::STARTING_LIVES;
    float x = 0.0f, y = 0.0f;
    float angle = 0.0f;
    float radius = 10.0f;

    bool bThrust = false;
    float speed = Constants::SPACESHIP_SPEED;
    float rotationSpeed = Constants::SPACESHIP_ROT_SPEED;
    float rotationDirection = 0.0f;

    const std::vector<Vector2> shapePoints  = {
            { 0.0f, -10.0f },
            { 10.0f, 10.0f },
            { -10.0f, 10.0f }
    };

    std::vector<Bullet> bullets;
};
