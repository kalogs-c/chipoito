#include "chip8.h"
#include "display/display.h"
#include <SDL2/SDL_log.h>
#include <stdlib.h>

int main() {
  DisplayConfig config = {.title = "Chipoito", .scale = 15};

  Chip8 *chip8 = CHIP8_Create(config);
  if (chip8 == NULL) {
    SDL_Log("ERROR Starting CHIP8: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  CHIP8_Start(chip8);

  return EXIT_SUCCESS;
}
