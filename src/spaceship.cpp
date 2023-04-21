#include "spaceship.h"
#include "constants.h"
#include "SDL.h"
#include <cmath>
#include <iostream>

Spaceship Spaceship::createSpaceship() {
    lives = Constants::STARTING_LIVES;
    x = Constants::STARTING_POSITION_X;
    y = Constants::STARTING_POSITION_Y;
    angle = 0.f;
    speed = Constants::SPACESHIP_SPEED;
    radius = 10.0f;

    return {lives, x, y, angle, speed};
}

void Spaceship::update() {
//    const std::string debug = "X: " + std::to_string(x) + " Y: " + std::to_string(y);
//    std::cout << debug << std::endl;
}

void Spaceship::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    float radAngle = angle * M_PI / 180.0f;
    SDL_FPoint points[] = {
            { static_cast<float>(x + cos(radAngle) * 10), static_cast<float>(y - sin(radAngle) * 10) },
            { static_cast<float>(x + cos(radAngle + M_PI * 2 / 3) * 10), static_cast<float>(y - sin(radAngle + M_PI * 2 / 3) * 10) },
            { static_cast<float>(x + cos(radAngle + M_PI * 4 / 3) * 10), static_cast<float>(y - sin(radAngle + M_PI * 4 / 3) * 10) },
            { static_cast<float>(x + cos(radAngle) * 10), static_cast<float>(y - sin(radAngle) * 10) },
    };

    SDL_RenderDrawLinesF(renderer, points, 4);
}

void Spaceship::die() {

    if (lives > 0) {
        lives--;
        respawn();
    } else {
        std::cout << "Game Over" << std::endl;
        // TODO: Game over
    }
}

void Spaceship::respawn() {
    x = Constants::STARTING_POSITION_X;
    y = Constants::STARTING_POSITION_Y;
    angle = 0.f;
}


