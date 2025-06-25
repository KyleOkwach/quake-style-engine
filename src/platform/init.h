#pragma once

#include "common.h"
#include "framebuffer.h"

SDL_AppResult init_window(void *appstate);
SDL_AppResult init_renderer(void *appstate);
SDL_AppResult init_framebuffer(void *appstate);