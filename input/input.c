#include "input.h"
#include <SDL2/SDL_keycode.h>

Event handleKey(SDL_Keycode key) {
  switch (key) {
  case SDLK_ESCAPE:
    return QUIT;
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
    return handleKey(event.key.keysym.sym);
  default:
    return NONE;
  };
}
