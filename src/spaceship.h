#pragma once

class SDL_Renderer;
class Spaceship {

public:
    int lives; // Lives
    float x, y; // Position
    float angle; // Rotation angle
    float speed; // Speed
    float radius; // Size for collision detection

    Spaceship createSpaceship();

    void die();

    void respawn();

    void update();

    void draw(SDL_Renderer* renderer);
};
