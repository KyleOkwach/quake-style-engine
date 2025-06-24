#include "framebuffer.h"

Uint32 *pixel_buffer = NULL;
static int fb_width = 0, fb_height = 0;

void framebuffer_init(int width, int height) {
    if (width <= 0 || height <= 0) {
        SDL_Log("Invalid framebuffer dimensions: %dx%d", width, height);
        return;
    }

    fb_width = width, fb_height = height;
    pixel_buffer = (Uint32*)SDL_malloc(width * height * sizeof(Uint32));
    
    if (!pixel_buffer) {
        SDL_Log("Failed to allocate framebuffer memory");
    }

    SDL_Log("Framebuffer initialized: %dx%d", width, height);
}

Uint32 *framebuffer_get_pixels(void) {
    return pixel_buffer;
}

void framebuffer_clear(Uint32 color) {
    for (int i = 0; i < fb_width * fb_height; ++i)
        pixel_buffer[i] = color;
}

void framebuffer_putpixel(int x, int y, Uint32 color) {
    if (x < 0 || x >= fb_width || y < 0 || y >= fb_height) return;
    pixel_buffer[y * fb_width + x] = color;
}

void framebuffer_present(AppState *state) {
    SDL_UpdateTexture(state->framebuffer, NULL, pixel_buffer, fb_width * sizeof(Uint32));

    // Scale to window size automatically
    SDL_RenderClear(state->renderer);
    SDL_RenderTexture(state->renderer, state->framebuffer, NULL, NULL);
    SDL_RenderPresent(state->renderer);
}

void framebuffer_destroy(void) {
    SDL_free(pixel_buffer);
    pixel_buffer = NULL;
}