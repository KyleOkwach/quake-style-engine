#include "common.h"

SDL_AppResult init_window(void *appstate, int width, int height, SDL_WindowFlags flags) {
    AppState *state = (AppState*)appstate;

    state->window = SDL_CreateWindow(
        "Topdown Game",
        width,
        height,
        flags
    );

    if (!state->window) {
        SDL_Log("Failed to create window: %s", SDL_GetError()); // Check if window creation was successful
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}