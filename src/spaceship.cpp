#include "spaceship.h"
#include "gamestate.h"
#include <cmath>
#include <iostream>
#include <raymath.h>

void Spaceship::createSpaceship(Spaceship &spaceship) {

    spaceship.position = { Constants::SCREEN_WIDTH / 2.0f, Constants::SCREEN_HEIGHT / 2.0f };
    spaceship.speed = Constants::SPACESHIP_SPEED;
    spaceship.radius = 10.0f;
    spaceship.velocity = { 0.0f, 0.0f };
    spaceship.rotationDirection = 0.0f;
    spaceship.rotationSpeed = Constants::SPACESHIP_ROT_SPEED;
    spaceship.bThrust = false;

    spaceship.shapePoints = {
            { 0.0f, -spaceship.radius },
            { spaceship.radius, spaceship.radius },
            { -spaceship.radius, spaceship.radius }
    };
}

void Spaceship::setThrust(bool bThrust) {
    this->bThrust = bThrust;
}

void Spaceship::move() {
    angle += rotationDirection * rotationSpeed * GetFrameTime();

    if (bThrust) {
        float radAngle = (angle - 90.0f) * PI / 180.0f; // Subtract 90.0f from the angle
        Vector2 thrustDirection = { cos(radAngle), sin(radAngle) };
        velocity = Vector2Scale(thrustDirection, speed);
    } else {
        velocity = {0, 0};
    }

    position = Vector2Add(position, Vector2Scale(velocity, GetFrameTime()));
}


void Spaceship::update() {
    move();
}

void Spaceship::draw() {
    auto transformedPoints = shapePoints;

    // Apply rotation transformation
    float radAngle = angle * PI / 180.0f;
    for (auto& point : transformedPoints) {
        float newX = point.x * cos(radAngle) - point.y * sin(radAngle);
        float newY = point.x * sin(radAngle) + point.y * cos(radAngle);
        point.x = newX;
        point.y = newY;
    }

    // Apply translation transformation
    for (auto& point : transformedPoints) {
        point = Vector2Add(point, position);
    }

    Color color = RAYWHITE;
    DrawTriangleLines(transformedPoints[0], transformedPoints[1], transformedPoints[2], color);

    for (Bullet& bullet : gameState.bullets) {
        bullet.draw();
    }
}


void Spaceship::die() {
    if (lives > 0) {
        lives--;
        respawn();
    } else {
        std::cout << "Game Over" << std::endl;
        // TODO: Game over
    }
}

void Spaceship::respawn() {
    position.x = Constants::STARTING_POSITION_X;
    position.y = Constants::STARTING_POSITION_Y;
    angle = 0.f;
}

void Spaceship::shoot() {
    Bullet bullet;

    bullet.createBullet(position.x, position.y, angle, Constants::BULLET_SPEED);
    gameState.bullets.push_back(bullet);
}

Spaceship::Spaceship(GameState &gameState) : gameState(gameState) {
    createSpaceship(*this);
}
