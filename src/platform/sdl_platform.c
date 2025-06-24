#include "sdl_platform.h"

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    AppState *state = (AppState *)appstate;  // Cast appstate to AppState type

    if (result == SDL_APP_FAILURE) {
        SDL_Log("Application quit with failure.");
    } else {
        SDL_Log("Application quit successfully.");
    }

    if (state->window) {
        framebuffer_destroy();  // Clean up framebuffer resources
        SDL_DestroyTexture(state->framebuffer);  // Destroy the framebuffer texture if it exists
        state->framebuffer = NULL;  // Set the framebuffer to NULL after destruction
        SDL_DestroyRenderer(state->renderer);  // Destroy the renderer if it exists
        state->renderer = NULL;  // Set the renderer to NULL after destruction
        SDL_DestroyWindow(state->window);  // Destroy the window if it exists
        state->window = NULL;  // Set the window to NULL after destruction
        SDL_QuitSubSystem(SDL_INIT_VIDEO);  // Clean up initialized subsystems
    }
}

void app_wait_for_frame(void *appstate) {
    AppState *state = (AppState*)appstate;

    Uint64 frame_time = SDL_GetTicks() - state->current_tick;  // Calculate the time since the last frame
    if (frame_time < TARGET_FRAME_TIME) {
        SDL_Delay(TARGET_FRAME_TIME - frame_time);  // Delay to maintain the target frame rate
    }
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState* state = (AppState*)appstate;  // Cast appstate to AppState pointer
    SDL_Event event;

    while (SDL_PollEvent(&event)) {  // Poll for events
        if (event.type == SDL_EVENT_QUIT) {  // Check if quit event is triggered
            return SDL_APP_SUCCESS;  // Allow app to quit
        }
    }

    // Using framebuffer to draw to screen
    framebuffer_clear(0x1F1F1FFF);
    framebuffer_putpixel(100, 100, 0xFF0000FF);  // Example pixel drawing
    framebuffer_present(state);

    return SDL_APP_CONTINUE;  // Allow app to continue running
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState *state = (AppState*)appstate;  // Cast appstate to AppState pointer

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  // Handle quit event
    }

    // Handle other events here (Possibly through an event queue e.g., keyboard, mouse, etc.)
    // ...

    return SDL_APP_CONTINUE;  // Continue processing events
}

void app_update(void *appstate) {
    AppState *state = (AppState*)appstate;  // Cast appstate to AppState pointer
    state->current_tick = SDL_GetTicks();  // Get the current tick count in milliseconds
    state->delta_time = (state->current_tick - state->last_tick) / 1000.0f;  // Calculate delta time in seconds
    state->last_tick = state->current_tick;  // Update last tick to current tick
}