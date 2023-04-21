#include "bullet.h"
#include <cmath>

void Bullet::createBullet(float startX, float startY, float angle, float startSpeed) {
    x = startX;
    y = startY;
    speed = startSpeed;

    float radAngle = (angle + 90) * PI / 180.0f;
    dx = -cos(radAngle) * speed;
    dy = -sin(radAngle) * speed;
}

void Bullet::update() {
    x += dx;
    y += dy;
    lifetime -= GetFrameTime();
}

void Bullet::draw() const {
    DrawCircle(x, y, radius, color);
}