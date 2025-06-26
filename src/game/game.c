#include "game.h"

SDL_AppResult init_game(void) {
    // Initialize game components, systems, and resources here
    // This function will be called at the start of the game
    // Can be used initialize the renderer, load assets, etc.
    
    Mesh mesh;
    Tri tris[] = {
        // South
        { .p = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}} },
        { .p = {{1, 0, 0}, {1, 1, 0}, {0, 1, 0}} },

        // East
        { .p = {{1, 0, 0}, {1, 0, 1}, {1, 1, 0}} },
        { .p = {{1, 0, 1}, {1, 1, 1}, {1, 1, 0}} },

        // North
        { .p = {{1, 0, 1}, {0, 0, 1}, {1, 1, 1}} },
        { .p = {{0, 0, 1}, {0, 1, 1}, {1, 1, 1}} },

        // West
        { .p = {{0, 0, 1}, {0, 0, 0}, {0, 1, 1}} },
        { .p = {{0, 0, 0}, {0, 1, 0}, {0, 1, 1}} },

        // Top
        { .p = {{0, 1, 0}, {1, 1, 0}, {0, 1, 1}} },
        { .p = {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}} },

        // Bottom
        { .p = {{0, 0, 0}, {1, 0, 0}, {0, 0, 1}} },
        { .p = {{1, 0, 0}, {1, 0, 1}, {0, 0, 1}} }
    };
    mesh.tris = tris;

    Entity cude = create_entity();
    add_mesh(cude, &mesh);

    return SDL_APP_CONTINUE;  // Indicate that the game initialization was successful
}

void game_update(void) {
    // Update game logic here
    // This function will be called every frame to update the game state
    
}