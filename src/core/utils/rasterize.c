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

static void draw_vline(int x, int y0, int y1, uint32_t color) {
    if (y0 > y1) {
        swap_points(&y0, &y1);
    }
    for (int y = y0; y <= y1; y++) {
        framebuffer_putpixel(x, y, color);
    }
}

static void draw_antialiased_hline(int x0, int x1, int y, uint32_t color) {
    if (x0 > x1) {
        int temp = x0;
        x0 = x1;
        x1 = temp;
    }
    
    // Inner pixels get full color
    for (int x = x0 + 1; x < x1; x++) {
        framebuffer_putpixel(x, y, color);
    }
    
    // Edge pixels get semi-transparent color
    uint32_t edge_color = (color & 0xFFFFFF00) | ((color & 0xFF) * 100/100);
    framebuffer_putpixel(x0, y, edge_color);
    framebuffer_putpixel(x1, y, edge_color);
}

static SDL_Color hex_to_rgba(uint32_t pixel) {
    SDL_Color rgb_color;
    
    // Assuming pixel format is 0xRRGGBBAA
    rgb_color.r = (pixel >> 24) & 0xFF;
    rgb_color.g = (pixel >> 16) & 0xFF;
    rgb_color.b = (pixel >> 8) & 0xFF;
    rgb_color.a = pixel & 0xFF;
    
    return rgb_color;
}

static uint32_t rgba_to_hex(SDL_Color rgba_color) {
    return(
        ((rgba_color.r & 0xFF) << 24) |  // Convert red value to RR byte
        ((rgba_color.g & 0xFF) << 16) |  // Convert green value to GG byte
        ((rgba_color.b & 0xFF) << 8) |  // Convert blue value to BB byte
        (rgba_color.a & 0xFF)  // Convert alpha value to AA byte
    );
}

// ---------------------------------------------------------------------

void draw_polygon(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color, float light_intensity) {
    // Draw polygon with varying intensity for shading
    SDL_Color rgba_color = hex_to_rgba(color);  // Convert to rgba
    float min_intensity = 0.5;

    // Darken the color to the specified intensity
    rgba_color.r *= fmax(light_intensity, min_intensity);
    rgba_color.b *= fmax(light_intensity, min_intensity);
    rgba_color.a *= fmax(light_intensity, min_intensity);

    draw_triangle_filled(x0, y0, x1, y1, x2, y2, rgba_to_hex(rgba_color));
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color, int thickness) {
    if (thickness <= 1) {
        // Original Bresenham's algorithm
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
        return;
    }

    // For thickness > 1, draw multiple offset lines
    // Calculate the perpendicular direction
    int dx = x1 - x0;
    int dy = y1 - y0;
    float length = sqrtf(dx * dx + dy * dy);
    float perp_x = -(float)dy / length;
    float perp_y = (float)dx / length;

    int half = thickness / 2;
    for (int t = -half; t <= half; t++) {
        int ox0 = x0 + (int)(perp_x * t);
        int oy0 = y0 + (int)(perp_y * t);
        int ox1 = x1 + (int)(perp_x * t);
        int oy1 = y1 + (int)(perp_y * t);

        // Call the original line function recursively with thickness 1
        draw_line(ox0, oy0, ox1, oy1, color, 1);
    }
}

// Draw triangle outline
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    draw_line(x0, y0, x1, y1, color, 3);
    draw_line(x1, y1, x2, y2, color, 3);
    draw_line(x2, y2, x0, y0, color, 3);
}

// Draw filled triangle using scanline algorithm
void draw_triangle_filled(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // Sort vertices by y-coordinate - this is important for scanline fill
    // First point is the topmost, second is middle, third is bottommost
    sort_by_y(&x0, &y0, &x1, &y1, &x2, &y2);

    // Edge cases
    if (y0 == y2) {
        // Degenerate case: all points are on the same horizontal line
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

        // Add +1 pixel to the right edge to ensure coverage
        if (ax > bx) {
            draw_antialiased_hline(bx, ax, y, color);
        } else {
            draw_antialiased_hline(ax, bx, y, color);
        }
    }


    // Bottom half
    for (int y = y1; y <= y2; y++) {
        int segment_height = y2 - y1 + 1;
        float alpha = (float)(y - y0) / total_height;
        float beta = segment_height ? (float)(y - y1) / segment_height : 0;

        int ax = x0 + (int)((x2 - x0) * alpha);
        int bx = x1 + (int)((x2 - x1) * beta);

        // Add +1 pixel to the right edge to ensure coverage
        if (ax > bx) {
            draw_antialiased_hline(bx, ax, y, color);
        } else {
            draw_antialiased_hline(ax, bx, y, color);
        }
    }
}

// Draw rectangle outline
void draw_rectangle(int x0, int y0, int x1, int y1, uint32_t color) {
    draw_line(x0, y0, x1, y0, color, 2);
    draw_line(x1, y0, x1, y1, color, 2);
    draw_line(x1, y1, x0, y1, color, 2);
    draw_line(x0, y1, x0, y0, color, 2);
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