#ifndef CHIP8_H
#define CHIP8_H

#include "display/display.h"
#include "memory/memory.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum {
  RUNNING,
  STOPPED,
  PAUSED,
} State;

typedef struct {
  Display *display;
  State state;
  Memory *memory;
  bool keypad[16]; // Keypad. 0x0 - 0xF.
  char *rom;       // ROM.
} Chip8;

Chip8 *CHIP8_Create(DisplayConfig config, const char *rom_file_path);
void CHIP8_Destroy(Chip8 *chip8);

void CHIP8_Start(Chip8 *chip8);

#endif // !CHIP8_H
