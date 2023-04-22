#include "spaceship.h"
#include "gamestate.h"
#include <cmath>
#include <raymath.h>

void Spaceship::createSpaceship(Spaceship &spaceship) {

    spaceship.position = { static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f };
    spaceship.speed = Constants::SPACESHIP_SPEED;
    spaceship.radius = Constants::SPACESHIP_RADIUS;
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

void Spaceship::move() {
    if (bDestroyed) return;

    angle += rotationDirection * rotationSpeed * GetFrameTime();

    if (bThrust) {
        float radAngle = (angle - 90.0f) * PI / 180.0f; // Subtract 90.0f from the angle
        Vector2 thrustDirection = { cos(radAngle), sin(radAngle) };
        Vector2 thrustForce = Vector2Scale(thrustDirection, speed * GetFrameTime());
        velocity = Vector2Add(velocity, thrustForce);
    }

    position = Vector2Add(position, Vector2Scale(velocity, GetFrameTime()));

    // Wrap the spaceship around the screen edges
    if (position.x < 0) position.x += static_cast<float>(GetScreenWidth());
    if (position.y < 0) position.y += static_cast<float>(GetScreenHeight());
    if (position.x >= static_cast<float>(GetScreenWidth())) position.x -= static_cast<float>(GetScreenWidth());
    if (position.y >= static_cast<float>(GetScreenHeight())) position.y -= static_cast<float>(GetScreenHeight());
}



void Spaceship::update() {
    move();
}

void Spaceship::draw() {
    if (bDestroyed) return;

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

    DrawTriangleLines(transformedPoints[0], transformedPoints[1], transformedPoints[2], Constants::SPACESHIP_COLOR);

    for (Bullet& bullet : gameState.getBullets()) {
        bullet.draw();
    }
}

void Spaceship::shoot() {
    if (bDestroyed) return;

    Bullet bullet;

    bullet.createBullet(position.x, position.y, angle, Constants::BULLET_SPEED);
    gameState.addBullet(bullet);
}

Spaceship::Spaceship(GameState &gameState) : gameState(gameState) {
    createSpaceship(*this);
}
