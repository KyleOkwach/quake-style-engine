#pragma once

#include <SDL3/SDL.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint64 last_tick;
    Uint64 current_tick;
    float delta_time;
} AppState;  // Application state structure

SDL_AppResult init_window(void *appstate, int width, int height, SDL_WindowFlags flags);
SDL_AppResult init_renderer(void *appstate, SDL_Window *window);