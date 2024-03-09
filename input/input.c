#include "input.h"
#include <SDL2/SDL_keycode.h>

Event handleKey(SDL_Keycode key, State state) {
  switch (key) {
  case SDLK_ESCAPE:
    return QUIT;
  case SDLK_SPACE:
    return state == RUNNING ? FREEZE : PLAY;
  default:
    return NONE;
  }
}

Event CHIP8_HandleInputEvent(Chip8 *chip8, SDL_Event event) {
  (void)chip8;

  switch (event.type) {
  case SDL_QUIT:
    return QUIT;
  case SDL_KEYDOWN:
    return handleKey(event.key.keysym.sym, chip8->state);
  default:
    return NONE;
  };
}
