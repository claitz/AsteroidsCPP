#include "asteroid.h"
#include "constants.h"
#include "utils.h"
#include "spaceship.h"
#include "raymath.h"

Asteroid Asteroid::createAsteroid(int asteroidLevel) {
    Asteroid newAsteroid;

    newAsteroid.level = asteroidLevel;
    newAsteroid.x = Utils::randomFloat(0.0f, Constants::SCREEN_WIDTH);
    newAsteroid.y = Utils::randomFloat(0.0f, Constants::SCREEN_HEIGHT);
    newAsteroid.dx = Utils::randomFloat(-Constants::ASTEROID_SPEED, Constants::ASTEROID_SPEED);
    newAsteroid.dy = Utils::randomFloat(-Constants::ASTEROID_SPEED, Constants::ASTEROID_SPEED);
    newAsteroid.radius = newAsteroid.level * 10.0f;

    float angleStep = 2.0f * PI / Constants::ASTEROID_POINTS;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.5f, 1.5f);

    for (int i = 0; i < Constants::ASTEROID_POINTS; ++i) {
        float randomRadius = newAsteroid.radius * dist(gen);
        Vector2 point = { static_cast<float>(cos(angleStep * i) * randomRadius), static_cast<float>(-sin(angleStep * i) * randomRadius) };
        float distance = Vector2Length(point);
        if (distance > newAsteroid.radius) {
            point = Vector2Scale(point, newAsteroid.radius / distance);
        }
        newAsteroid.points.push_back(point);
    }

    return newAsteroid;
}


void Asteroid::update(Spaceship& spaceship) {
    x += dx;
    y += dy;

    // Wrap around screen edges
    if (x < -radius) x += Constants::SCREEN_WIDTH + radius * 2;
    if (x > Constants::SCREEN_WIDTH + radius) x -= Constants::SCREEN_WIDTH + radius * 2;
    if (y < -radius) y += Constants::SCREEN_HEIGHT + radius * 2;
    if (y > Constants::SCREEN_HEIGHT + radius) y -= Constants::SCREEN_HEIGHT + radius * 2;
}

void Asteroid::draw() {

   // TraceLog(LOG_INFO, "Drawing asteroid at (%f, %f) with %d points", x, y, points.size());
    if (points.empty()) return;

    std::vector<Vector2> translated_points = points;
    for (Vector2& point : translated_points) {
        point.x += x;
        point.y += y;
    }
    translated_points.push_back(translated_points[0]);

    Color color = RAYWHITE;
    DrawLineStrip(translated_points.data(), translated_points.size(), color);
}
