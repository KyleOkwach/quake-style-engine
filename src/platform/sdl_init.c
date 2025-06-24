#include "sdl_init.h"
#include "sdl_platform.h"

SDL_AppResult init_window(void *appstate) {
    AppState *state = (AppState*)appstate;
    strcpy(state->title, "Boom");
    
    

    state->window = SDL_CreateWindow(
        state->title,
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

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    AppState *state = SDL_malloc(sizeof(AppState));  // Allocate memory for the application state
    *appstate = state;  // Set the appstate pointer to the allocated state

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        // Initialize SDL with video subsystem
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError()); // Check if SDL initialized successfully
        return SDL_APP_FAILURE;
    }

    state->window_width = 1280;
    state->window_height = 720;
    state->window_flags = 0;
    state->resolution_width = 640;
    state->resolution_height = 480;

    if (init_window(state) != SDL_APP_CONTINUE ||
        init_renderer(state) != SDL_APP_CONTINUE ||
        init_framebuffer(state) != SDL_APP_CONTINUE) {
        SDL_AppQuit(state, SDL_APP_FAILURE);  // Clean up and quit if any initialization fails
        SDL_free(state);  // Free the allocated memory for the app state
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;  // Allow app to continue running
}