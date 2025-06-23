#pragma once
#define SDL_MAIN_USE_CALLBACKS  // Enable SDL main callbacks
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "common.h"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv);