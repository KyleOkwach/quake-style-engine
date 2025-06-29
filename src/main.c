#define SDL_MAIN_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "config.h"
#include "backend/common.h"
#include "backend/time.h"
#include "backend/init.h"
#include "backend/framebuffer.h"
#include "game/game.h"

void app_render(void *appstate) {
    AppState *state = (AppState *)appstate;
    framebuffer_clear(0x1F1F1FFF);
    game_update(state);  // Call the game update function to handle game logic and rendering
    framebuffer_present(state);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    AppState *state = (AppState *)appstate;  // Cast appstate to AppState type

    if (result == SDL_APP_FAILURE) {
        SDL_Log("Application quit with failure.");
    } else {
        SDL_Log("Application quit successfully.");
    }

    if (state->window) {
        game_quit();  // Call the game quit function to clean up game resources
        framebuffer_present(state);  // Present the framebuffer before quitting
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

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState* state = (AppState*)appstate;  // Cast appstate to AppState pointer
    SDL_Event event;

    while (SDL_PollEvent(&event)) {  // Poll for events
        if (event.type == SDL_EVENT_QUIT) {  // Check if quit event is triggered
            return SDL_APP_SUCCESS;  // Allow app to quit
        }
    }

    app_render(state);  // Render the application state
    wait_for_frame(state);  // Wait for the next frame to render

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

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    AppState *state = SDL_malloc(sizeof(AppState));  // Allocate memory for the application state
    *appstate = state;  // Set the appstate pointer to the allocated state

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        // Initialize SDL with video subsystem
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError()); // Check if SDL initialized successfully
        return SDL_APP_FAILURE;
    }

    state->window_width = 1280;
    state->window_height = 960;
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

    SDL_SetTextureScaleMode(state->framebuffer, SDL_SCALEMODE_NEAREST);  // Set the texture scale mode to nearest neighbor
    SDL_SetWindowTitle(state->window, "Software Renderer");  // Set window title
    SDL_SetWindowPosition(state->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);  // Center the window on the screen
    SDL_Log("Application initialized successfully.");

    if(!game_init(state) == SDL_APP_CONTINUE) {
        SDL_Log("Failed to initialize game: %s", SDL_GetError());  // Check if game initialization was successful
        SDL_AppQuit(state, SDL_APP_FAILURE);  // Clean up and quit if game_init is not defined
        SDL_free(state);  // Free the allocated memory for the app state
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;  // Allow app to continue running
}

int SDL_main(int argc, char *argv[]) {
    void *appstate = NULL;
    if (SDL_AppInit(&appstate, argc, argv) != SDL_APP_CONTINUE)
        return 1;

    SDL_AppResult result = SDL_APP_CONTINUE;
    while (result == SDL_APP_CONTINUE) {
        result = SDL_AppIterate(appstate);
    }

    SDL_AppQuit(appstate, result);
    SDL_free(appstate);
    return (result == SDL_APP_SUCCESS) ? 0 : 1;
}