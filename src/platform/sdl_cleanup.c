#include "sdl_platform.h"

/*
* Function to handle quitting the application
* This function is called when the application is about to quit.
*/
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