#include "time.h"
#include "common.h"

#define TARGET_FPS 60  // Target frames per second
#define TARGET_FRAME_TIME (1000 / TARGET_FPS)  // Target frame time in milliseconds

void app_wait_for_frame(void *appstate) {
    AppState *state = (AppState*)appstate;

    Uint64 frame_time = SDL_GetTicks() - state->current_tick;  // Calculate the time since the last frame
    if (frame_time < TARGET_FRAME_TIME) {
        SDL_Delay(TARGET_FRAME_TIME - frame_time);  // Delay to maintain the target frame rate
    }
}

void app_update(void *appstate) {
    AppState *state = (AppState*)appstate;  // Cast appstate to AppState pointer
    state->current_tick = SDL_GetTicks();  // Get the current tick count in milliseconds
    state->delta_time = (state->current_tick - state->last_tick) / 1000.0f;  // Calculate delta time in seconds
    state->last_tick = state->current_tick;  // Update last tick to current tick
}