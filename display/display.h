#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  uint32_t columns;
  uint32_t rows;
  bool pixels[64 * 32]; // 64x32 pixels (The original resolution of CHIP-8)
} Display;

typedef struct {
  const char *title;
  uint8_t scale;
} DisplayConfig;

Display *CHIP8_CreateDisplay(DisplayConfig config);
void CHIP8_DestroyDisplay(Display *display);

void CHIP8_ClearDisplay(Display *display);

bool CHIP8_SetPixel(Display *display, uint8_t x, uint8_t y);

#endif // !DISPLAY_H
