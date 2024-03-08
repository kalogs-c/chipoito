#include "chip8.h"
#include "./input/input.h"
#include <SDL2/SDL_events.h>

Chip8 *CHIP8_Create(DisplayConfig config) {
  Chip8 *chip8 = malloc(sizeof(Chip8));
  if (!chip8) {
    return NULL;
  }

  Display *display = CHIP8_CreateDisplay(config);
  if (!display) {
    return NULL;
  }

  chip8->display = display;
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
    case NONE:
      break;
    };
  }
}

void CHIP8_Start(Chip8 *chip8) {
  CHIP8_ClearDisplay(chip8->display);

  while (chip8->state != STOPPED) {
    CHIP8_Update(chip8);
  }

  return;
}
