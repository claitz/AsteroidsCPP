#include "gamestate.h"
#include "constants.h"
#include "asteroid.h"
#include <string>
#include <algorithm>

GameState::GameState(): spaceship(*this) {
    spawnInitialAsteroids();
}

void GameState::spawnInitialAsteroids() {
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

    removeInactive();

    renderHUD();
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
                bullet.bDestroyed = true;
                asteroid.bDestroyed = true;
                addScore(asteroid.level);
            }
        }
    }
}

void GameState::renderHUD() const {
    const int fontSize = 20;
    const int fontSpacing = 10;

    // Score
    std::string scoreText = "Score: " + std::to_string(score);
    DrawText(scoreText.c_str(), fontSpacing, fontSpacing, fontSize, WHITE);

    // Lives
    std::string livesText = "Lives: " + std::to_string(lives);
    int livesTextWidth = MeasureText(livesText.c_str(), fontSize);
    DrawText(livesText.c_str(), GetScreenWidth() - livesTextWidth - fontSpacing, fontSpacing, fontSize, WHITE);

    // Level
    std::string levelText = "Level: " + std::to_string(level);
    int levelTextWidth = MeasureText(levelText.c_str(), fontSize);
    DrawText(levelText.c_str(), GetScreenWidth() / 2 - levelTextWidth / 2, fontSpacing, fontSize, WHITE);
}

void GameState::removeInactive() {

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [](const Bullet& bullet) { return bullet.bDestroyed; }),
                  bullets.end());

    asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                   [](const Asteroid& asteroid) { return asteroid.bDestroyed; }),
                    asteroids.end());
}

void GameState::addScore(int enemyLevel) {
    score += enemyLevel * Constants::ENEMY_BASE_SCORE;
}

void GameState::respawnSpaceship() {
    spaceship.position = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
    spaceship.velocity = {0.0f, 0.0f};
    spaceship.bDestroyed = false;
}
