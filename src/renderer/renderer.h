#pragma once

#include <stdint.h>

typedef struct {
    int width;
    int height;
    uint32_t* color_buffer;
    float* z_buffer;
} Framebuffer;

void renderer_init(int width, int height);
void renderer_clear(uint32_t color);
void renderer_draw_pixel(int x, int y, uint32_t color);
void renderer_present();
void renderer_shutdown();
