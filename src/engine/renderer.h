/*
* The renderer handles the rendering lifecycle
* This includes drawing shapes to the framebuffer
*/

#pragma once

#include <stdint.h>
#include "../platform/common.h"

void renderer_init();
void render_update();
void renderer_clear();