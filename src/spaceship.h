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
    Vector2 velocity = {0.0f, 0.0f};
    Vector2 position = {Constants::STARTING_POSITION_X, Constants::STARTING_POSITION_Y};
    float angle = 0.0f;
    float radius = 10.0f;

    bool bThrust = false;
    float speed = Constants::SPACESHIP_SPEED;
    float rotationSpeed = Constants::SPACESHIP_ROT_SPEED;
    float rotationDirection = 0.0f;


    const std::vector<Vector2> shapePoints  = {
            { 0.0f, -radius },
            { radius, radius },
            { -radius, radius }
    };

    std::vector<Bullet> bullets;
};
