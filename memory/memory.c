#include "memory.h"
#include <SDL2/SDL_log.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _load_fontset(Memory *memory) {
  uint8_t chip8_fontset[80] = {
      0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
      0x20, 0x60, 0x20, 0x20, 0x70, // 1
      0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
      0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
      0x90, 0x90, 0xF0, 0x10, 0x10, // 4
      0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
      0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
      0xF0, 0x10, 0x20, 0x40, 0x40, // 7
      0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
      0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
      0xF0, 0x90, 0xF0, 0x90, 0x90, // A
      0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
      0xF0, 0x80, 0x80, 0x80, 0xF0, // C
      0xE0, 0x90, 0x90, 0x90, 0xE0, // D
      0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
      0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };

  memcpy(memory->ram, chip8_fontset, sizeof(chip8_fontset));

  return;
}

bool _read_rom(Memory *memory, const char *rom_file_path) {
  FILE *rom = fopen(rom_file_path, "rb");
  if (NULL == rom) {
    SDL_Log("ROM %s not found or could not be opened\n", rom_file_path);
    return false;
  }

  fseek(rom, 0, SEEK_END);
  const long file_size = ftell(rom);
  rewind(rom);

  const long rom_size = sizeof(memory->ram) - ROM_ENTRY_POINT;
  if (file_size > rom_size) {
    SDL_Log("ROM file is too big\n");
    fclose(rom);
    return false;
  }

  if (fread(memory->ram + ROM_ENTRY_POINT, 1, file_size, rom) != 1) {
    SDL_Log("ROM file could not be read\n");
    fclose(rom);
    return false;
  };

  fclose(rom);

  return true;
}

Memory *CHIP8_CreateMemory(const char *rom_file_path) {
  Memory *memory = malloc(sizeof(Memory));
  if (NULL == memory) {
    return NULL;
  }

  memory->PC = ROM_ENTRY_POINT;

  _load_fontset(memory);
  if (!_read_rom(memory, rom_file_path)) {
    free(memory);
    return NULL;
  }

  return memory;
}
