#include "gamestate.h"
#include "constants.h"
#include "asteroid.h"
#include <string>
#include <algorithm>

GameState::GameState(): spaceship(*this) {
    init();
}

void GameState::init() {
    changeResolution(currentResolutionIndex);
    currentState = GameStateType::MainMenu;
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
    switch (currentState) {
        case GameStateType::MainMenu:
            updateMainMenu();
            break;
        case GameStateType::InGame:
            updateInGame();
            break;
        case GameStateType::Options:
            updateOptions();
            break;
        case GameStateType::GameOver:
            updateGameOver();
            break;
    }
}

void GameState::updateMainMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        startGame();
    }

    if (IsKeyPressed(KEY_O)) {
        currentState = GameStateType::Options;
    }
}

void GameState::updateInGame() {
    for (Asteroid &asteroid : asteroids) {
        asteroid.update(spaceship);
        asteroid.draw();
    }

    for (std::size_t i = 0; i < bullets.size();) {
        Bullet &bullet = bullets[i];
        bullet.update();
        bullet.draw();

        if (bullet.getLifetime() <= 0) {
            bullets.erase(bullets.begin() + i);
        } else {
            ++i;
        }
    }

    spaceship.update();
    spaceship.draw();

    checkCollisions();

    removeInactive();

    renderInGame();

    if (asteroids.empty()) {
        nextLevel();
    }
}

void GameState::updateOptions() {
    Vector2 mousePosition = GetMousePosition();

    // Increase resolution
    if (CheckCollisionPointRec(mousePosition, increaseResolutionButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        changeResolution(currentResolutionIndex + 1);
    }

    // Decrease resolution
    if (CheckCollisionPointRec(mousePosition, decreaseResolutionButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        changeResolution(currentResolutionIndex - 1);
    }

    // Return to the main menu
    if (IsKeyPressed(KEY_ENTER)) {
        currentState = GameStateType::MainMenu;
    }
}

void GameState::updateGameOver() {
    if (IsKeyPressed(KEY_ENTER)) {
        resetGame();
    }
}

void GameState::checkCollisions() {
    checkAsteroidCollisions();
    checkBulletCollisions();
}

void GameState::checkAsteroidCollisions() {
    for (Asteroid &asteroid : asteroids) {
        bool bCollision = CheckCollisionCircles({asteroid.getX(), asteroid.getY()}, asteroid.getRadius(), spaceship.getPosition(), spaceship.getRadius());

        if (bCollision) {
            die();
        }
    }
}

void GameState::checkBulletCollisions() {
    for (Bullet &bullet : bullets) {
        for (Asteroid &asteroid : asteroids) {
            bool bCollision = CheckCollisionCircles({asteroid.getX(), asteroid.getY()}, asteroid.getRadius(), {bullet.getX(), bullet.getY()}, bullet.getRadius());

            if (bCollision) {
                bullet.setDestroyed(true);
                asteroid.setDestroyed(true);
                addScore(asteroid.getLevel());
            }
        }
    }
}

void GameState::renderMainMenu() const{
    const int fontSizeLarge = Constants::FONT_SIZE_LARGE * 2;
    const int fontSize = Constants::FONT_SIZE_LARGE;
    const int fontSizeSmall = Constants::FONT_SIZE_LARGE / 2;

    const int margin = GetScreenHeight() / 10;
    const Color fontColor = Constants::FONT_COLOR;

    // Title
    std::string titleText = "Asteroids";
    int titleTextWidth = MeasureText(titleText.c_str(), fontSizeLarge);
    DrawText(titleText.c_str(), GetScreenWidth() / 2 - titleTextWidth / 2, margin, fontSizeLarge, fontColor);

    // Start
    std::string instructionsText = "Press ENTER to start";
    int instructionsTextWidth = MeasureText(instructionsText.c_str(), fontSize);
    DrawText(instructionsText.c_str(), GetScreenWidth() / 2 - instructionsTextWidth / 2, GetScreenHeight() / 2, fontSize, fontColor);

    // Options
    std::string optionsText = "[O] Options";
    int optionsTextWidth = MeasureText(optionsText.c_str(), fontSizeSmall);
    DrawText(optionsText.c_str(), GetScreenWidth() / 2 - optionsTextWidth / 2, GetScreenHeight() / 2 + margin, fontSizeSmall, fontColor);
}

void GameState::renderInGame() const {
    const int fontSize = Constants::FONT_SIZE;
    const int fontSpacing = GetScreenHeight() / 50;
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
}

void GameState::renderOptions() {
    const int fontSize = Constants::FONT_SIZE;
    const Color fontColor = Constants::FONT_COLOR;

    const int margin = GetScreenHeight() / 5;

    const int buttonMargin = 10;

    // Current Resolution
    std::string resolutionText = std::to_string(GetScreenWidth()) + "x" + std::to_string(GetScreenHeight());
    int resolutionTextWidth = MeasureText(resolutionText.c_str(), fontSize);
    DrawText(resolutionText.c_str(), GetScreenWidth() / 2 - resolutionTextWidth / 2, margin, fontSize, fontColor);

    // Increase Resolution Button
    std::string increaseText = " + ";
    increaseResolutionButton = {static_cast<float>(GetScreenWidth() / 2 + resolutionTextWidth / 2) + buttonMargin, static_cast<float>(margin), static_cast<float>(fontSize), static_cast<float>(fontSize)};
    DrawText(increaseText.c_str(), increaseResolutionButton.x, increaseResolutionButton.y, fontSize, fontColor);
    DrawRectangleLinesEx(increaseResolutionButton, 2, fontColor);

    // Decrease Resolution Button
    std::string decreaseText = " - ";
    decreaseResolutionButton = {static_cast<float>(GetScreenWidth() / 2 - resolutionTextWidth / 2 - fontSize) - buttonMargin, static_cast<float>(margin), static_cast<float>(fontSize), static_cast<float>(fontSize)};
    DrawText(decreaseText.c_str(), decreaseResolutionButton.x, decreaseResolutionButton.y, fontSize, fontColor);
    DrawRectangleLinesEx(decreaseResolutionButton, 2, fontColor);

    // Options
    std::string returnText = "ENTER to return to the main menu";
    int returnTextWidth = MeasureText(returnText.c_str(), fontSize);
    DrawText(returnText.c_str(), GetScreenWidth() / 2 - returnTextWidth / 2, GetScreenHeight() / 2 + margin, fontSize, fontColor);
}

void GameState::renderGameOver() const{
    const int fontSize = Constants::FONT_SIZE_LARGE;
    const int topMargin = GetScreenHeight() / 10;
    const Color fontColor = Constants::FONT_COLOR;

    std::string gameOverText = "GAME OVER";
    int gameOverTextWidth = MeasureText(gameOverText.c_str(), fontSize);
    DrawText(gameOverText.c_str(), GetScreenWidth() / 2 - gameOverTextWidth / 2, GetScreenHeight() / 2 - topMargin, fontSize, fontColor);

    // Start
    std::string instructionsText = "Press ENTER to restart";
    int instructionsTextWidth = MeasureText(instructionsText.c_str(), fontSize / 2);
    DrawText(instructionsText.c_str(), GetScreenWidth() / 2 - instructionsTextWidth / 2, GetScreenHeight() / 2, fontSize / 2, fontColor);
}


void GameState::removeInactive() {
    // Remove destroyed bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [](const Bullet& bullet) { return bullet.isDestroyed(); }),
                  bullets.end());

    // Remove destroyed asteroids and spawn new ones
    std::vector<Asteroid> newAsteroids;
    for (auto it = asteroids.begin(); it != asteroids.end();) {
        if (it->isDestroyed()) {
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

    spaceship.setPosition({static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2});
    spaceship.setVelocity({0, 0});
    spaceship.setDestroyed(false);
}

std::vector<Asteroid> GameState::subdivideAsteroid(Asteroid &parentAsteroid) {
    std::vector<Asteroid> newAsteroids;
    if (parentAsteroid.getLevel() > 1) {
        for (int i = 0; i < 2; ++i) {
            Asteroid asteroid = Asteroid::createAsteroid(parentAsteroid.getLevel() - 1, parentAsteroid.getX(), parentAsteroid.getY());
            newAsteroids.push_back(asteroid);
        }
    }
    return newAsteroids;
}

void GameState::startGame() {
    currentState = GameStateType::InGame;
    spawnAsteroids(Constants::ASTEROID_COUNT * level);
}

void GameState::nextLevel() {
    ++level;
    spawnAsteroids(Constants::ASTEROID_COUNT * level);
}

void GameState::endGame() {
    currentState = GameStateType::GameOver;
    bullets.clear();
    asteroids.clear();
}

void GameState::resetGame() {
    score = 0;
    level = 1;
    lives = Constants::STARTING_LIVES;
    respawnSpaceship();
    spawnAsteroids(Constants::ASTEROID_COUNT);
    currentState = GameStateType::InGame;
}


void GameState::changeResolution(int newResolutionIndex) {

    if (newResolutionIndex < 0) {
        newResolutionIndex = Constants::RESOLUTIONS.size() - 1;
    } else if (newResolutionIndex >= Constants::RESOLUTIONS.size()) {
        newResolutionIndex = 0;
    }

    SetWindowSize(Constants::RESOLUTIONS[newResolutionIndex].x, Constants::RESOLUTIONS[newResolutionIndex].y);
    currentResolutionIndex = newResolutionIndex;

    centerWindow();
}

void GameState::centerWindow() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int monitorWidth = GetMonitorWidth(0); // Assuming primary monitor
    int monitorHeight = GetMonitorHeight(0); // Assuming primary monitor

    int windowPosX = (monitorWidth - screenWidth) / 2;
    int windowPosY = (monitorHeight - screenHeight) / 2;

    SetWindowPosition(windowPosX, windowPosY);
}

void GameState::die() {

    lives -= 1;
    spaceship.setDestroyed(true);

    if (lives <= 0) {
        endGame();
    } else {
        respawnSpaceship();
    }

}
