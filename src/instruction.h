#pragma once

#include "chip8.h"
#include <stdint.h>

typedef struct {
  uint16_t opcode;
  uint16_t NNN;
  uint8_t NN;
  uint8_t N;
  uint8_t X;
  uint8_t Y;
} Instruction;

void Chip8_EmulateInstruction(Chip8 *chip8);
