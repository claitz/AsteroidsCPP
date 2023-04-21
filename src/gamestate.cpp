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

    spaceship.update();
    spaceship.draw();
}
