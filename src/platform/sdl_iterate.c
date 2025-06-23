#include "sdl_platform.h"

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

    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);  // Set renderer draw color to black
    SDL_RenderClear(state->renderer);  // Clear the renderer

    // Render your game here

    SDL_RenderPresent(state->renderer);  // Present the rendered frame

    return SDL_APP_CONTINUE;  // Allow app to continue running
}