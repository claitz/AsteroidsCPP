#include "raylib.h"
#include "constants.h"
#include "gamestate.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "Asteroids");

    // Create a game state
    GameState gameState;

    SetTargetFPS(60);               // Set the desired frame rate

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Input
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            gameState.spaceship.rotationDirection = -1.0f;
        } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            gameState.spaceship.rotationDirection = 1.0f;
        } else {
            gameState.spaceship.rotationDirection = 0.0f;
        }

        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
            gameState.spaceship.setThrust(true);
        } else {
            gameState.spaceship.setThrust(false);
        }

        if (IsKeyPressed(KEY_SPACE)) {
            gameState.spaceship.shoot();
        }

        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(BLACK);

        // Call the update function on the game state
        gameState.update();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
