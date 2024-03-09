#include "display.h"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

Display *CHIP8_CreateDisplay(DisplayConfig config) {
  Display *display = malloc(sizeof(Display));
  if (NULL == display) {
    SDL_Log("ERROR Creating Display: %s\n", SDL_GetError());
    free(display);
    return NULL;
  }

  display->columns = 64;
  display->rows = 32;

  SDL_Window *window =
      SDL_CreateWindow(config.title, SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, display->columns * config.scale,
                       display->rows * config.scale, SDL_WINDOW_RESIZABLE);

  if (NULL == window) {
    SDL_Log("ERROR Creating Window: %s\n", SDL_GetError());
    free(display);
    return NULL;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1,
      SDL_RENDERER_PRESENTVSYNC); // It crashes on WSL2 without this flag

  if (NULL == renderer) {
    SDL_Log("ERROR Creating Renderer: %s\n", SDL_GetError());
    free(display);
    return NULL;
  }

  display->window = window;
  display->renderer = renderer;

  return display;
}

void CHIP8_DestroyDisplay(Display *display) {
  SDL_DestroyRenderer(display->renderer);
  SDL_DestroyWindow(display->window);
  free(display);

  return;
}

void CHIP8_ClearDisplay(Display *display) {
  SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
  SDL_RenderClear(display->renderer);
  SDL_RenderPresent(display->renderer);

  return;
}
