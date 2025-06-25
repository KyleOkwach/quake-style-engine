#pragma once

#include "common.h"

void framebuffer_init(int width, int height);
void framebuffer_clear(Uint32 color);
void framebuffer_putpixel(int x, int y, Uint32 color);
void framebuffer_present(AppState *state);
void framebuffer_destroy();
void framebuffer_resize(int width, int height);
Uint32 *framebuffer_get_pixels(void);