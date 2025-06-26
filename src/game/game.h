#pragma once
#include "../backend/common.h"
#include "../core/ecs.h"
#include "../core/systems/camera.h"
#include "../core/systems/mesh.h"

SDL_AppResult game_init(void *appState);
void game_update(void *appstate);
void game_render(void);
void game_quit(void);