#include "rasterize.h"

static void swap_points(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sort_by_y(int* x0, int* y0, int* x1, int* y1, int* x2, int* y2) {
    if (*y0 > *y1) {
        swap_points(y0, y1);
        swap_points(x0, x1);
    }
    if (*y0 > *y2) {
        swap_points(y0, y2);
        swap_points(x0, x2);
    }
    if (*y1 > *y2) {
        swap_points(y1, y2);
        swap_points(x1, x2);
    }
}

static void draw_hline(int x0, int x1, int y, uint32_t color) {
    if (x0 > x1) {
        int temp = x0;
        x0 = x1;
        x1 = temp;
    }
    for (int x = x0; x <= x1; x++) {
        framebuffer_putpixel(x, y, color);
    }
}

// Bresenham's line algorithm
void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        framebuffer_putpixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

// Draw triangle outline
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}

// Draw filled triangle using scanline algorithm
void draw_triangle_filled(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    sort_by_y(&x0, &y0, &x1, &y1, &x2, &y2);

    if (y0 == y2) {
        draw_hline(x0, x1, y0, color);
        draw_hline(x1, x2, y0, color);
        return;
    }

    int total_height = y2 - y0;

    // Top half
    for (int y = y0; y <= y1; y++) {
        int segment_height = y1 - y0 + 1;
        float alpha = (float)(y - y0) / total_height;
        float beta = segment_height ? (float)(y - y0) / segment_height : 0;

        int ax = x0 + (int)((x2 - x0) * alpha);
        int bx = x0 + (int)((x1 - x0) * beta);

        draw_hline(ax, bx, y, color);
    }

    // Bottom half
    for (int y = y1 + 1; y <= y2; y++) {
        int segment_height = y2 - y1;
        float alpha = (float)(y - y0) / total_height;
        float beta = segment_height ? (float)(y - y1) / segment_height : 0;

        int ax = x0 + (int)((x2 - x0) * alpha);
        int bx = x1 + (int)((x2 - x1) * beta);

        draw_hline(ax, bx, y, color);
    }
}

// Draw rectangle outline
void draw_rectangle(int x0, int y0, int x1, int y1, uint32_t color) {
    draw_line(x0, y0, x1, y0, color);
    draw_line(x1, y0, x1, y1, color);
    draw_line(x1, y1, x0, y1, color);
    draw_line(x0, y1, x0, y0, color);
}

// Draw filled rectangle
void draw_rectangle_filled(int x0, int y0, int x1, int y1, uint32_t color) {
    if (y0 > y1) swap_points(&y0, &y1);
    if (x0 > x1) swap_points(&x0, &x1);

    for (int y = y0; y <= y1; y++) {
        draw_hline(x0, x1, y, color);
    }
}

// Midpoint circle algorithm for outline
void draw_circle(int cx, int cy, int radius, uint32_t color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        framebuffer_putpixel(cx + x, cy + y, color);
        framebuffer_putpixel(cx + y, cy + x, color);
        framebuffer_putpixel(cx - y, cy + x, color);
        framebuffer_putpixel(cx - x, cy + y, color);
        framebuffer_putpixel(cx - x, cy - y, color);
        framebuffer_putpixel(cx - y, cy - x, color);
        framebuffer_putpixel(cx + y, cy - x, color);
        framebuffer_putpixel(cx + x, cy - y, color);

        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

// Filled circle using midpoint algorithm
void draw_circle_filled(int cx, int cy, int radius, uint32_t color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        draw_hline(cx - x, cx + x, cy + y, color);
        draw_hline(cx - x, cx + x, cy - y, color);
        draw_hline(cx - y, cx + y, cy + x, color);
        draw_hline(cx - y, cx + y, cy - x, color);

        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}