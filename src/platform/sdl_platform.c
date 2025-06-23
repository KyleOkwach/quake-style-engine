#include "sdl_platform.h"

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    AppState *state = (AppState *)appstate;  // Cast appstate to AppState type

    if (result == SDL_APP_FAILURE) {
        SDL_Log("Application quit with failure.");
    } else {
        SDL_Log("Application quit successfully.");
    }

    if (state->window) {
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

    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);  // Set renderer draw color to black
    SDL_RenderClear(state->renderer);  // Clear the renderer

    // Render your game here

    SDL_RenderPresent(state->renderer);  // Present the rendered frame

    return SDL_APP_CONTINUE;  // Allow app to continue running
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState* state = (AppState*)appstate;  // Cast appstate to AppState pointer

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  // Handle quit event
    }

    // Handle other events here (e.g., keyboard, mouse, etc.)
    // ...

    return SDL_APP_CONTINUE;  // Continue processing events
}