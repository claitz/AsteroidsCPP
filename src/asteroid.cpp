#include "asteroid.h"
#include "constants.h"
#include "utils.h"
#include "spaceship.h"
#include "SDL.h"

Asteroid Asteroid::createAsteroid(int asteroidLevel) {

    level = asteroidLevel;
    x = Utils::randomFloat(0.0f, Constants::SCREEN_WIDTH);
    y = Utils::randomFloat(0.0f, Constants::SCREEN_HEIGHT);
    dx = Utils::randomFloat(-Constants::ASTEROID_SPEED, Constants::ASTEROID_SPEED);
    dy = Utils::randomFloat(-Constants::ASTEROID_SPEED, Constants::ASTEROID_SPEED);
    radius = level * 10.0f;

    float angleStep = 2.0f * M_PI / Constants::ASTEROID_POINTS;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.5f, 1.5f);

    for (int i = 0; i < Constants::ASTEROID_POINTS; ++i) {
        float randomRadius = radius * dist(gen);
        points.push_back({static_cast<float>(cos(angleStep * i) * randomRadius),static_cast<float>(-sin(angleStep * i) * randomRadius) });
    }

    return {level, x, y, dx, dy, radius, points };
}

void Asteroid::update(Spaceship& spaceship) {
    x += dx;
    y += dy;

    // Wrap around screen edges
    if (x < -radius) x += Constants::SCREEN_WIDTH + radius * 2;
    if (x > Constants::SCREEN_WIDTH + radius) x -= Constants::SCREEN_WIDTH + radius * 2;
    if (y < -radius) y += Constants::SCREEN_HEIGHT + radius * 2;
    if (y > Constants::SCREEN_HEIGHT + radius) y -= Constants::SCREEN_HEIGHT + radius * 2;

    if (collidesWith(spaceship)) {
        spaceship.die();
    }
}

void Asteroid::draw(SDL_Renderer *renderer) {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_FPoint center = {x, y};

    std::vector<SDL_FPoint> translated_points = points;
    for (SDL_FPoint& point : translated_points) {
        point.x += center.x;
        point.y += center.y;
    }
    translated_points.push_back(translated_points[0]);

    SDL_RenderDrawLinesF(renderer, translated_points.data(), translated_points.size());
}

bool Asteroid::collidesWith(Spaceship &spaceship) {
    float dx = x - spaceship.x;
    float dy = y - spaceship.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    return distance < radius + spaceship.radius;
}
