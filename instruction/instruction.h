#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "../chip8.h"
#include <stdint.h>

typedef struct {
  uint16_t opcode;
  uint8_t NNN;
  uint8_t NN;
  uint8_t N;
  uint8_t X;
  uint8_t Y;
} Instruction;

void CHIP8_EmulateInstruction(Chip8 *chip8);

#endif // !INSTRUCTION_H
