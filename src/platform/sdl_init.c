#include "sdl_platform.h"
#include "sdl_init.h"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    AppState* state = SDL_malloc(sizeof(AppState));  // Allocate memory for the application state
    *appstate = state;  // Set the appstate pointer to the allocated state
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        // Initialize SDL with video subsystem
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError()); // Check if SDL initialized successfully
        return SDL_APP_FAILURE;
    }

    init_window(state, 1280, 720, 0);
    init_renderer(state, state->window);

    return SDL_APP_CONTINUE;  // Allow app to continue running
}