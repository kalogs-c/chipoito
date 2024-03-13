#include "display.h"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

Display *CHIP8_CreateDisplay(DisplayConfig config) {
  Display *display = malloc(sizeof(Display));
  if (NULL == display) {
    SDL_Log("ERROR Creating Display: %s\n", SDL_GetError());
    free(display);
    return NULL;
  }

  memset(display, 0, sizeof(Display));

  display->columns = DISPLAY_WIDTH * config.scale;
  display->rows = DISPLAY_HEIGHT * config.scale;
  display->scale = config.scale;

  SDL_Window *window = SDL_CreateWindow(
      config.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      display->columns, display->rows, SDL_WINDOW_RESIZABLE);

  if (NULL == window) {
    SDL_Log("ERROR Creating Window: %s\n", SDL_GetError());
    free(display);
    return NULL;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (NULL == renderer) {
    SDL_Log("ERROR Creating Renderer: %s\n", SDL_GetError());
    free(display);
    return NULL;
  }

  display->window = window;
  display->renderer = renderer;
  memset(&display->pixels[0], false, sizeof(display->pixels));

  return display;
}

void CHIP8_DestroyDisplay(Display *display) {
  SDL_DestroyRenderer(display->renderer);
  SDL_DestroyWindow(display->window);
  free(display);
}

void CHIP8_ClearDisplay(Display *display) {
  SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
  SDL_RenderClear(display->renderer);
  SDL_RenderPresent(display->renderer);
}

void CHIP8_ClearPixels(Display *display) {
  memset(&display->pixels[0], false, sizeof display->pixels);
}

void CHIP8_UpdateDisplay(Display display) {
  SDL_Rect rectangle = {0, 0, display.scale, display.scale};

  for (uint16_t row = 0; row < sizeof display.pixels; row++) {
    rectangle.x = (row % DISPLAY_WIDTH) * display.scale;
    rectangle.y = (row / DISPLAY_WIDTH) * display.scale;

    const bool pixel = display.pixels[row];
    if (pixel) {
      SDL_SetRenderDrawColor(display.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderFillRect(display.renderer, &rectangle);
    } else {
      SDL_SetRenderDrawColor(display.renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(display.renderer, &rectangle);
    }
  }

  SDL_RenderPresent(display.renderer);
}
