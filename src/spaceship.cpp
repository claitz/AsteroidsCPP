#include "spaceship.h"
#include <cmath>
#include <iostream>
#include <raymath.h>

Spaceship Spaceship::createSpaceship() {

    return Spaceship();
}

void Spaceship::move() {
    angle += rotationDirection * rotationSpeed * GetFrameTime();

    if (bThrust) {
        float radAngle = (angle - 90.0f) * PI / 180.0f; // Subtract 90.0f from the angle
        Vector2 velocity = { cos(radAngle), sin(radAngle) };
        position = Vector2Add(position, Vector2Scale(velocity, speed * GetFrameTime()));
    }
}

void Spaceship::update() {
    move();
    for (Bullet& bullet : bullets) {
        bullet.update();
    }

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [](const Bullet& bullet) { return bullet.lifetime <= 0; }),
                  bullets.end());
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

    for (Bullet& bullet : bullets) {
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
    std::cout << "Shoot" << std::endl;

    Bullet bullet;

    bullet.createBullet(position.x, position.y, angle, Constants::BULLET_SPEED);
    bullets.push_back(bullet);
}

