#include "chip8.h"
#include "display.h"
#include <SDL2/SDL_log.h>
#include <stdlib.h>

int main(const int argc, char *argv[]) {
  if (argc != 2) {
    SDL_Log("Usage: %s <rom_file_path>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *rom_file_path = argv[1];

  const Display display = Chip8_CreateDisplay("chipoito", 15);
  const Memory memory = Chip8_CreateMemory(rom_file_path);
  Chip8 chip8 = Chip8_Create(display, memory);

  Chip8_Emulate(&chip8);
  Chip8_Stop(&chip8);

  return EXIT_SUCCESS;
}
