#include "display.h"

#include <assert.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdint.h>
#include <string.h>

Display Chip8_CreateDisplay(const char* title, const int8_t scale) {
    Display display = {
        .columns = DISPLAY_WIDTH * scale,
        .rows = DISPLAY_HEIGHT * scale,
        .scale = scale,
    };

    SDL_Window* window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        display.columns,
        display.rows,
        SDL_WINDOW_RESIZABLE
    );
    if (window == NULL) {
        SDL_Log("ERROR Creating Window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("ERROR Creating Renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    display.window = window;
    display.renderer = renderer;
    memset(&display.pixels[0], false, sizeof(display.pixels));

    return display;
}

void Chip8_DestroyDisplay(const Display* display) {
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
}

void Chip8_ClearDisplay(const Display* display) {
    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
    SDL_RenderClear(display->renderer);
}

void Chip8_ClearPixels(Display* display) {
    memset(&display->pixels[0], false, sizeof display->pixels);
}

void Chip8_UpdateDisplay(const Display* display) {
    Chip8_ClearDisplay(display);
    SDL_Rect rectangle = {0, 0, display->scale, display->scale};

    for (int32_t row = 0; row < (DISPLAY_HEIGHT * DISPLAY_WIDTH); row++) {
        SDL_SetRenderDrawColor(display->renderer, 0xFA, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(display->renderer, &rectangle);
        if (!display->pixels[row]) continue;

        rectangle.x = (row % DISPLAY_WIDTH) * display->scale;
        rectangle.y = (row / DISPLAY_WIDTH) * display->scale;
        SDL_SetRenderDrawColor(display->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(display->renderer, &rectangle);
    }

    SDL_RenderPresent(display->renderer);
}
