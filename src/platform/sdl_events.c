#include "sdl_platform.h"

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState* state = (AppState*)appstate;  // Cast appstate to AppState pointer

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  // Handle quit event
    }

    // Handle other events here (e.g., keyboard, mouse, etc.)
    // ...

    return SDL_APP_CONTINUE;  // Continue processing events
}