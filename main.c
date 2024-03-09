#include "chip8.h"
#include "display/display.h"
#include <SDL2/SDL_log.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    SDL_Log("Usage: %s <rom_file_path>\n", argv[0]);
    return EXIT_FAILURE;
  }

  DisplayConfig config = {.title = "Chipoito", .scale = 15};
  const char *rom_file_path = argv[1];

  Chip8 *chip8 = CHIP8_Create(config, rom_file_path);
  if (NULL == chip8) {
    SDL_Log("ERROR Starting CHIP8: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  CHIP8_Start(chip8);

  return EXIT_SUCCESS;
}
