#include "chip8.h"
#include "input/input.h"
#include "memory/memory.h"
#include <SDL2/SDL_events.h>
#include <stdlib.h>

Chip8 *CHIP8_Create(DisplayConfig config, const char *rom_file_path) {
  Chip8 *chip8 = malloc(sizeof(Chip8));
  if (NULL == chip8) {
    free(chip8);
    return NULL;
  }

  Display *display = CHIP8_CreateDisplay(config);
  if (NULL == display) {
    free(chip8);
    return NULL;
  }

  Memory *memory = CHIP8_CreateMemory(rom_file_path);
  if (NULL == memory) {
    free(chip8);
    return NULL;
  }

  chip8->display = display;
  chip8->memory = memory;
  chip8->state = RUNNING;

  return chip8;
};

void CHIP8_Destroy(Chip8 *chip8) {
  CHIP8_DestroyDisplay(chip8->display);
  free(chip8);

  return;
};

void CHIP8_Update(Chip8 *chip8) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (CHIP8_HandleInputEvent(chip8, event)) {
    case QUIT:
      chip8->state = STOPPED;
      return;
    case FREEZE:
      chip8->state = PAUSED;
      return;
    case PLAY:
      chip8->state = RUNNING;
      return;
    case NONE:
      break;
    };
  }
}

void CHIP8_Start(Chip8 *chip8) {
  CHIP8_ClearDisplay(chip8->display);

  while (chip8->state != STOPPED) {
    CHIP8_Update(chip8);

    if (chip8->state == PAUSED)
      continue;
  }

  return;
}
