#include <SDL2/SDL_error.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"

typedef struct {
  const char *title;
  uint8_t scale;
} MonitorConfig;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool is_running;
} SDLInstance;

bool START(SDLInstance *sdl, const MonitorConfig config) {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
    SDL_Log("ERROR Inicializing SDL: %s\n", SDL_GetError());
    return false;
  }

  SDL_Window *window = SDL_CreateWindow(
      config.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      64 * config.scale, 32 * config.scale, SDL_WINDOW_RESIZABLE);

  if (window == NULL) {
    SDL_Log("ERROR Creating Window: %s\n", SDL_GetError());
    return false;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1,
      SDL_RENDERER_SOFTWARE); // It crashes on WSL2 without this flag

  if (renderer == NULL) {
    SDL_Log("ERROR Creating Renderer: %s\n", SDL_GetError());
    return false;
  }

  sdl->window = window;
  sdl->renderer = renderer;

  return true;
}

int DESTROY(const SDLInstance *sdl) {
  SDL_DestroyWindow(sdl->window);
  SDL_DestroyRenderer(sdl->renderer);
  SDL_Quit();

  return EXIT_SUCCESS;
}

void UPDATE(SDLInstance *sdl) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      sdl->is_running = false;
      break;
    }
  }
}

int main() {
  SDLInstance sdl = {.is_running = true};

  MonitorConfig config = {"Chipoito", 15};
  if (!START(&sdl, config)) {
    SDL_Log("ERROR Starting SDL INSTANCE: %s\n", SDL_GetError());

    return EXIT_FAILURE;
  };

  SDL_SetRenderDrawColor(sdl.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(sdl.renderer);

  SDL_RenderPresent(sdl.renderer);

  while (sdl.is_running) {
    UPDATE(&sdl);
  }

  return DESTROY(&sdl);
}
