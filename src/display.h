#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>

static const uint8_t DISPLAY_HEIGHT = 32;
static const uint8_t DISPLAY_WIDTH = 64;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int8_t scale;
    int32_t columns;
    int32_t rows;
    bool pixels[64 * 32]; // 64x32 pixels (The original resolution of Chip-8)
    bool redraw;
} Display;

typedef struct {
} DisplayConfig;

Display Chip8_CreateDisplay(const char* title, int8_t scale);

void Chip8_DestroyDisplay(const Display* display);

void Chip8_ClearDisplay(const Display* display);

void Chip8_ClearPixels(Display* display);

void Chip8_UpdateDisplay(const Display* display);
