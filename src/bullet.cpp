#include "bullet.h"
#include <cmath>

void Bullet::createBullet(float startX, float startY, float angle, float startSpeed, int startLifetime) {
    x = startX;
    y = startY;
    speed = startSpeed;
    lifetime = startLifetime;

    float radAngle = angle * PI / 180.0f;
    dx = cos(radAngle) * speed;
    dy = -sin(radAngle) * speed;
}

void Bullet::update() {
    x += dx;
    y += dy;
    lifetime--;
}

void Bullet::draw() {
    //DrawPixelV(Vector2{ x, y }, RAYWHITE);
}
