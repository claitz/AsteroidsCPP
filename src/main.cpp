#include "raylib.h"
#include "constants.h"
#include "gamestate.h"

int main() {
    // Initialization
    //-------------------------------------------------------------------------------------

    // Set the current resolution to the default resolution
    InitWindow(Constants::RESOLUTIONS[0].x, Constants::RESOLUTIONS[0].y, "Asteroids");

    // Create a game state
    GameState gameState;

    SetTargetFPS(60);               // Set the desired frame rate

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Input
        if (gameState.getCurrentState() == GameStateType::InGame){
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                gameState.getSpaceship().setRotationDirection(-1.0f);
            } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                gameState.getSpaceship().setRotationDirection(1.0f);
            } else {
                gameState.getSpaceship().setRotationDirection(0);

            }

            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
                gameState.getSpaceship().setThrust(true);
            } else {
                gameState.getSpaceship().setThrust(false);
            }

            if (IsKeyPressed(KEY_SPACE)) {
                gameState.getSpaceship().shoot();
            }
        }

        // Call the update function on the game state
        gameState.update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        switch (gameState.getCurrentState()) {
            case GameStateType::MainMenu:
                gameState.renderMainMenu();
                break;
            case GameStateType::InGame:
                gameState.renderInGame();
                break;
            case GameStateType::Options:
                gameState.renderOptions();
                break;
            case GameStateType::GameOver:
                gameState.renderGameOver();
                break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
