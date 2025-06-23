#pragma once
#include "common.h"
#define TARGET_FPS 60  // Target frames per second
#define TARGET_FRAME_TIME (1000 / TARGET_FPS)  // Target frame time in milliseconds

void app_wait_for_frame(void *appstate);
void app_update(void *appstate);
void SDL_AppQuit(void *appstate, SDL_AppResult result);

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event);
SDL_AppResult SDL_AppIterate(void *appstate);