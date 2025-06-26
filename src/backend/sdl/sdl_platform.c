#include "../init.h"

SDL_AppResult init_window(void *appstate) {
    AppState *state = (AppState*)appstate;
    
    state->window = SDL_CreateWindow(
        "Boom",
        state->window_width,
        state->window_height,
        state->window_flags
    );

    if (!state->window) {
        SDL_Log("Failed to create window: %s", SDL_GetError()); // Check if window creation was successful
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult init_renderer(void *appstate) {
    AppState *state = (AppState*)appstate;

    state->renderer = SDL_CreateRenderer(state->window, NULL);

    if (!state->renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError()); // Check if renderer creation was successful
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult init_framebuffer(void *appstate) {
    AppState *state = (AppState *)appstate;

    // int width, height;
    // SDL_GetWindowSizeInPixels(state->window, &width, &height);

    state->framebuffer = SDL_CreateTexture(
        state->renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        state->resolution_width,
        state->resolution_height
    );

    if (!state->framebuffer) {
        SDL_Log("Failed to create framebuffer texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    framebuffer_init(state->resolution_width, state->resolution_height);

    return SDL_APP_CONTINUE;
}