/*
* Primitive drawing functions for rendering basic shapes.
* These functions allow for drawing lines, triangles, rectangles, and circles
* These shapes can be filled or outlined, and they support color customization.
* The primitives are defined using simple structures that hold the necessary
* geometric properties and color information for rendering.
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "../../backend/framebuffer.h"

static void swap_points(int* a, int* b);
static void sort_by_y(int* x0, int* y0, int* x1, int* y1, int* x2, int* y2);
static void draw_hline(int x0, int x1, int y, uint32_t color);

void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_triangle_filled(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_rectangle(int x0, int y0, int x1, int y1, uint32_t color);
void draw_circle(int cx, int cy, int radius, uint32_t color);
void draw_circle_filled(int cx, int cy, int radius, uint32_t color);