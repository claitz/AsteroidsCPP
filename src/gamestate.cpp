#include "gamestate.h"
#include "constants.h"
#include "asteroid.h"
#include <string>
#include <algorithm>

GameState::GameState(): spaceship(*this) {

    spawnAsteroids(Constants::ASTEROID_COUNT);

}

void GameState::spawnAsteroids(int count) {
    for (int i = 0; i < count; ++i) {

        auto asteroidX = GetRandomValue(0, GetScreenWidth());
        auto asteroidY = GetRandomValue(0, GetScreenHeight());

        Asteroid asteroid = Asteroid::createAsteroid(Constants::ASTEROID_LEVELS, static_cast<float>(asteroidX), static_cast<float>(asteroidY));
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
    const int fontSize = Constants::FONT_SIZE;
    const int fontSpacing = Constants::FONT_SPACING;
    const int fontSizeLarge = Constants::FONT_SIZE_LARGE;
    const Color fontColor = Constants::FONT_COLOR;

    // Score
    std::string scoreText = "Score: " + std::to_string(score);
    DrawText(scoreText.c_str(), fontSpacing, fontSpacing, fontSize, fontColor);

    // Lives
    std::string livesText = "Lives: " + std::to_string(lives);
    int livesTextWidth = MeasureText(livesText.c_str(), fontSize);
    DrawText(livesText.c_str(), GetScreenWidth() - livesTextWidth - fontSpacing, fontSpacing, fontSize, fontColor);

    // Level
    std::string levelText = "Level: " + std::to_string(level);
    int levelTextWidth = MeasureText(levelText.c_str(), fontSize);
    DrawText(levelText.c_str(), GetScreenWidth() / 2 - levelTextWidth / 2, fontSpacing, fontSize, fontColor);

    // Game Over
    if (bGameOver){
        std::string gameOverText = "GAME OVER";
        int gameOverTextWidth = MeasureText(gameOverText.c_str(), fontSizeLarge);
        DrawText(gameOverText.c_str(), GetScreenWidth() / 2 - gameOverTextWidth / 2, GetScreenHeight() / 2, fontSizeLarge, fontColor);
    }
}

void GameState::removeInactive() {

    // Remove destroyed bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [](const Bullet& bullet) { return bullet.bDestroyed; }),
                  bullets.end());

    // Remove destroyed asteroids and spawn new ones
    std::vector<Asteroid> newAsteroids;
    for (auto it = asteroids.begin(); it != asteroids.end();) {
        if (it->bDestroyed) {
            auto subdividedAsteroids = subdivideAsteroid(*it);
            newAsteroids.insert(newAsteroids.end(), subdividedAsteroids.begin(), subdividedAsteroids.end());
            it = asteroids.erase(it);
        } else {
            ++it;
        }
    }
    asteroids.insert(asteroids.end(), newAsteroids.begin(), newAsteroids.end());
}

void GameState::addScore(int enemyLevel) {
    score += enemyLevel * Constants::ENEMY_BASE_SCORE;
}

void GameState::respawnSpaceship() {
    spaceship.position = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
    spaceship.velocity = {0.0f, 0.0f};
    spaceship.bDestroyed = false;
}

std::vector<Asteroid> GameState::subdivideAsteroid(Asteroid &parentAsteroid) {
    std::vector<Asteroid> newAsteroids;
    if (parentAsteroid.level > 1) {
        for (int i = 0; i < 2; ++i) {
            Asteroid asteroid = Asteroid::createAsteroid(parentAsteroid.level - 1, parentAsteroid.x, parentAsteroid.y);
            newAsteroids.push_back(asteroid);
        }
    }
    return newAsteroids;
}

void GameState::endGame() {
    bGameOver = true;
}

