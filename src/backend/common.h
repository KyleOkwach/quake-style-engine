#pragma once

#include <stdint.h>
#include <SDL3/SDL.h>

// This struct stores the state of the app.
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *framebuffer;

    uint64_t last_tick;
    uint64_t current_tick;
    float delta_time;

    int window_width;
    int window_height;
    SDL_WindowFlags window_flags;

    int resolution_width;
    int resolution_height;
} AppState;
