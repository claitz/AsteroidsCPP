#include "gamestate.h"
#include "constants.h"
#include "asteroid.h"

GameState::GameState(): spaceship(*this) {

    for (int i = 0; i < Constants::ASTEROID_COUNT; ++i) {
        Asteroid asteroid = Asteroid::createAsteroid(Constants::ASTEROID_LEVELS);
        asteroids.push_back(asteroid);
    }
}

void GameState::update() {
    for (Asteroid &asteroid : asteroids) {
        asteroid.update(spaceship);
        asteroid.draw();
    }

    for (std::size_t i = 0; i < bullets.size();) {
        Bullet &bullet = bullets[i];
        bullet.update();
        bullet.draw();

        if (bullet.lifetime <= 0) {
            bullets.erase(bullets.begin() + i);
        } else {
            ++i;
        }
    }

    spaceship.update();
    spaceship.draw();

    checkCollisions();
}

void GameState::checkCollisions() {
    checkAsteroidCollisions();
    checkBulletCollisions();
}

void GameState::checkAsteroidCollisions() {
    for (Asteroid &asteroid : asteroids) {
        bool bCollision = CheckCollisionCircles({asteroid.x, asteroid.y}, asteroid.radius, spaceship.position, spaceship.radius);

        if (bCollision) {
            spaceship.die();
        }
    }
}

void GameState::checkBulletCollisions() {
    for (Bullet &bullet : bullets) {
        for (Asteroid &asteroid : asteroids) {
            bool bCollision = CheckCollisionCircles({asteroid.x, asteroid.y}, asteroid.radius, {bullet.x, bullet.y}, bullet.radius);

            if (bCollision) {
                TraceLog(LOG_INFO, "Bullet hit asteroid");
            }
        }
    }
}
