#include "raylib.h"
#include "constants.h"
#include "asteroid.h"
#include "spaceship.h"
#include <cmath>
#include <vector>

// Globals
std::vector<Asteroid> asteroids;

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = Constants::SCREEN_WIDTH;
    int screenHeight = Constants::SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, "Asteroids");

    // Create a spaceship
    Spaceship spaceship = Spaceship::createSpaceship();

    // Create starting asteroids
    for (int i = 0; i < Constants::ASTEROID_COUNT; ++i) {
        Asteroid asteroid = Asteroid::createAsteroid(Constants::ASTEROID_LEVELS);
        asteroids.push_back(asteroid);
    }

    SetTargetFPS(60);               // Set the desired frame rate

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Input
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            spaceship.rotationDirection = -1.0f;
        } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            spaceship.rotationDirection = 1.0f;
        } else {
            spaceship.rotationDirection = 0.0f;
        }

        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
            spaceship.bThrust = true;
        } else {
            spaceship.bThrust = false;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            spaceship.shoot();
        }

        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(BLACK);
        // Draw game elements (e.g., spaceship and asteroids)
        for (Asteroid &asteroid: asteroids) {
            asteroid.update(spaceship);
            asteroid.draw();
        }

        spaceship.update();
        spaceship.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
