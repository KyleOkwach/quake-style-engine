#include "common.h"

SDL_AppResult init_renderer(void *appstate, SDL_Window *window) {
    AppState *state = (AppState*)appstate;

    state->renderer = SDL_CreateRenderer(window, NULL);

    if (!state->renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError()); // Check if renderer creation was successful
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(state->renderer, 320, 180, SDL_LOGICAL_PRESENTATION_LETTERBOX); // Set logical presentation for the renderer

    return SDL_APP_CONTINUE;
}