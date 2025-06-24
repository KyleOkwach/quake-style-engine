#pragma once

#include <stdint.h>
#include <SDL3/SDL.h>

#define MAX_TITLE_LENGTH 64

// This struct stores the state of the app.
typedef struct {
    char title[MAX_TITLE_LENGTH];

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *framebuffer;

    Uint64 last_tick;
    Uint64 current_tick;
    float delta_time;

    int window_width;
    int window_height;
    SDL_WindowFlags window_flags;

    int resolution_width;
    int resolution_height;
} AppState;
