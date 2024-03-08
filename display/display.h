#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} Display;

typedef struct {
  const char *title;
  uint8_t scale;
} DisplayConfig;

Display *CHIP8_CreateDisplay(DisplayConfig config);
void CHIP8_DestroyDisplay(Display *display);

void CHIP8_ClearDisplay(Display *display);

#endif // !DISPLAY_H
