#include "spaceship.h"
#include <cmath>
#include <iostream>

Spaceship Spaceship::createSpaceship() {

    Spaceship newSpaceship;

    newSpaceship.x = Constants::STARTING_POSITION_X;
    newSpaceship.y = Constants::STARTING_POSITION_Y;

    return newSpaceship;
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

void Spaceship::move() {
    angle += rotationDirection * rotationSpeed * GetFrameTime();

    if (bThrust) {
        float radAngle = (angle + 90.0f) * PI / 180.0f; // Subtract 90.0f from the angle
        x -= cos(radAngle) * speed * GetFrameTime();
        y -= sin(radAngle) * speed * GetFrameTime();
    }
}

void Spaceship::draw() {
    auto transformedPoints = shapePoints;

    // Apply rotation transformationw
    float radAngle = angle * PI / 180.0f;
    for (auto& point : transformedPoints) {
        float newX = point.x * cos(radAngle) - point.y * sin(radAngle);
        float newY = point.x * sin(radAngle) + point.y * cos(radAngle);
        point.x = newX;
        point.y = newY;
    }

    // Apply translation transformation
    for (auto& point : transformedPoints) {
        point.x += x;
        point.y += y;
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
    x = Constants::STARTING_POSITION_X;
    y = Constants::STARTING_POSITION_Y;
    angle = 0.f;
}

void Spaceship::shoot() {
    std::cout << "Shoot" << std::endl;
    float margin = 5.0f;
    float radAngle = angle * PI / 180.0f;
    float bulletStartX = x + cos(radAngle) * (radius + margin);
    float bulletStartY = y - sin(radAngle) * (radius + margin);

    Bullet bullet;
    bullet.createBullet(bulletStartX, bulletStartY, angle, Constants::BULLET_SPEED, Constants::BULLET_LIFETIME);
    bullets.push_back(bullet);
}


