#include "opcodes.h"
#include "instruction.h"
#include <stdint.h>

void CHIP8_0x00__(Instruction instruction, Chip8 *chip8) {
  switch (instruction.opcode) {
  case 0x00E0:
    CHIP8_ClearPixels(chip8->display);
    break;
  case 0x00EE:
    chip8->memory->PC = chip8->memory->stack[chip8->memory->SP];
    break;
  }
}

void CHIP8_1nnn(Instruction instruction, Chip8 *chip8) {
  chip8->memory->PC = instruction.NNN;
}

void CHIP8_0x2nnn(Instruction instruction, Chip8 *chip8) {
  chip8->memory->SP++;
  chip8->memory->stack[chip8->memory->SP] = chip8->memory->PC;
  chip8->memory->PC = instruction.NNN;
}

void CHIP8_0x3xnn(Instruction instruction, Chip8 *chip8) {
  if (chip8->memory->V[instruction.X] == instruction.NN) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0x4xnn(Instruction instruction, Chip8 *chip8) {
  if (chip8->memory->V[instruction.X] != instruction.NN) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0x5xy0(Instruction instruction, Chip8 *chip8) {
  if (chip8->memory->V[instruction.X] == chip8->memory->V[instruction.Y]) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0x6xnn(Instruction instruction, Chip8 *chip8) {
  chip8->memory->V[instruction.X] = instruction.NN;
}

void CHIP8_0x7xnn(Instruction instruction, Chip8 *chip8) {
  chip8->memory->V[instruction.X] += instruction.NN;
}

void CHIP8_0x8xy_(Instruction instruction, Chip8 *chip8) {
  switch (instruction.N) {
  case 0:
    chip8->memory->V[instruction.X] = chip8->memory->V[instruction.Y];
    break;

  case 1:
    chip8->memory->V[instruction.X] |= chip8->memory->V[instruction.Y];
    break;

  case 2:
    chip8->memory->V[instruction.X] &= chip8->memory->V[instruction.Y];
    break;

  case 3:
    chip8->memory->V[instruction.X] ^= chip8->memory->V[instruction.Y];
    break;

  case 4: {
    uint16_t sum =
        chip8->memory->V[instruction.X] + chip8->memory->V[instruction.Y];
    if (sum > 0xFF) {
      chip8->memory->V[0xF] = 1;
    } else {
      chip8->memory->V[0xF] = 0;
    }
    chip8->memory->V[instruction.X] = sum & 0xFF;
    break;
  }

  case 5:
    if (chip8->memory->V[instruction.X] > chip8->memory->V[instruction.Y]) {
      chip8->memory->V[0xF] = 1;
    } else {
      chip8->memory->V[0xF] = 0;
    }
    chip8->memory->V[instruction.X] -= chip8->memory->V[instruction.Y];
    break;

  case 6:
    chip8->memory->V[0xF] = chip8->memory->V[instruction.X] & 0x1;
    chip8->memory->V[instruction.X] >>= 0x1;
    break;

  case 7:
    if (chip8->memory->V[instruction.Y] > chip8->memory->V[instruction.X]) {
      chip8->memory->V[0xF] = 1;
    } else {
      chip8->memory->V[0xF] = 0;
    }
    chip8->memory->V[instruction.X] =
        chip8->memory->V[instruction.Y] - chip8->memory->V[instruction.X];
    break;

  case 0xE:
    chip8->memory->V[0xF] = chip8->memory->V[instruction.X] & 0x80;
    chip8->memory->V[instruction.X] <<= 0x1;
    break;
  }
}

void CHIP8_0x9xy0(Instruction instruction, Chip8 *chip8) {
  if (chip8->memory->V[instruction.X] != chip8->memory->V[instruction.Y]) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0xAnnn(Instruction instruction, Chip8 *chip8) {
  chip8->memory->I = instruction.NNN;
}

void CHIP8_0xBnnn(Instruction instruction, Chip8 *chip8) {
  chip8->memory->PC = chip8->memory->V[0] + instruction.NNN;
}

void CHIP8_0xCxnn(Instruction instruction, Chip8 *chip8) {
  chip8->memory->V[instruction.X] = (rand() % 0xFF) & instruction.NN;
}

void CHIP8_0xDxyn(Instruction instruction, Chip8 *chip8) {}
