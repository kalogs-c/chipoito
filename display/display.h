#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>

#define DISPLAY_HEIGHT 32
#define DISPLAY_WIDTH 64

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  uint8_t scale;
  uint32_t columns;
  uint32_t rows;
  bool pixels[DISPLAY_WIDTH * DISPLAY_HEIGHT]; // 64x32 pixels (The original
                                               // resolution of CHIP-8)
} Display;

typedef struct {
  const char *title;
  uint8_t scale;
} DisplayConfig;

Display *CHIP8_CreateDisplay(DisplayConfig config);
void CHIP8_DestroyDisplay(Display *display);
void CHIP8_ClearDisplay(Display *display);
void CHIP8_ClearPixels(Display *display);
void CHIP8_UpdateDisplay(Display display);

#endif // !DISPLAY_H
