#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "constants.h"
#include "asteroid.h"
#include "spaceship.h"
#include <cmath>
#include <vector>

// Globals
std::vector<Asteroid> asteroids;

int main(int argc, char* argv[]) {
#pragma region SDL Setup
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Constants::SCREEN_WIDTH,Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return 1;
    }

#pragma endregion SDL Setup

    // Create a spaceship
    Spaceship spaceship;
    spaceship.createSpaceship();

    // Create starting asteroids
    for (int i = 0; i < Constants::ASTEROID_COUNT; ++i) {
        Asteroid asteroid;

        asteroid.createAsteroid(Constants::ASTEROID_LEVELS);
        asteroids.push_back(asteroid);
    }

    // Game loop
    bool running = true;
    SDL_Event event;

    while (running) {
        // Event loop
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Input
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
        if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A]) {
            spaceship.angle += 0.05f;
        }
        if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D]) {
            spaceship.angle -= 0.05f;
        }
        if (keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_W]) {
            float radAngle = spaceship.angle * M_PI / 180.0f;
            spaceship.x += cos(radAngle) * spaceship.speed;
            spaceship.y -= sin(radAngle) * spaceship.speed;
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Update game state

        // Asteroids
        for (Asteroid& asteroid : asteroids) {
            asteroid.update(spaceship);
            asteroid.draw(renderer);
        }

        // Spaceship
        spaceship.update();
        spaceship.draw(renderer);

        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
