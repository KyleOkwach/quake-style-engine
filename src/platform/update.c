#include "sdl_platform.h"

void app_update(void *appstate) {
    AppState* state = (AppState*)appstate;  // Cast appstate to AppState pointer
    state->current_tick = SDL_GetTicks();  // Get the current tick count in milliseconds
    state->delta_time = (state->current_tick - state->last_tick) / 1000.0f;  // Calculate delta time in seconds
    state->last_tick = state->current_tick;  // Update last tick to current tick
}