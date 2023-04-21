#include "bullet.h"
#include <cmath>

void Bullet::createBullet(float startX, float startY, float angle, float startSpeed, float startLifetime) {
    x = startX;
    y = startY;
    speed = startSpeed;
    lifetime = startLifetime;

    float radAngle = (angle + 90) * PI / 180.0f;
    dx = -cos(radAngle) * speed;
    dy = -sin(radAngle) * speed;
}

void Bullet::update() {
    x += dx;
    y += dy;
    lifetime -= GetFrameTime();
}

void Bullet::draw() {
    DrawCircle(x, y, 2, RAYWHITE);
}
