#pragma once

#include "common.h"

void framebuffer_init(int width, int height);
void framebuffer_clear(uint32_t color);
void framebuffer_putpixel(int x, int y, uint32_t color);
void framebuffer_present(AppState *state);
void framebuffer_destroy();
void framebuffer_resize(int width, int height);
uint32_t *framebuffer_get_pixels(void);