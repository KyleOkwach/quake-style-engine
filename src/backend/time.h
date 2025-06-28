#pragma once

#include "common.h"

#define TARGET_FPS 60  // Target frames per second
#define TARGET_FRAME_TIME (1000 / TARGET_FPS)  // Target frame time in milliseconds

void wait_for_frame(void *appstate);
void app_update(void *appstate);