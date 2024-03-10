#include "instruction.h"
#include "../chip8.h"
#include "../memory/memory.h"
#include "opcodes.h"
#include <stdint.h>

Instruction _mount_intruction(Memory *memory) {
  Instruction instruction;

  instruction.opcode =
      (memory->ram[memory->PC] << 8) | memory->ram[memory->PC + 1];
  memory->PC += 2;

  instruction.X = (instruction.opcode & 0x0F00) >> 8;
  instruction.Y = (instruction.opcode & 0x00F0) >> 4;
  instruction.N = (instruction.opcode & 0x000F);
  instruction.NN = instruction.opcode & 0x00FF;
  instruction.NNN = instruction.opcode & 0x0FFF;

  return instruction;
}

void CHIP8_EmulateInstruction(Chip8 *chip8) {
  Instruction instruction = _mount_intruction(chip8->memory);

  switch (instruction.opcode & 0xF000) {
  case 0x0000:
    CHIP8_0x00__(instruction, chip8);
    break;
  case 0x1000:
    CHIP8_1nnn(instruction, chip8);
    break;
  case 0x2000:
    CHIP8_0x2nnn(instruction, chip8);
    break;
  case 0x3000:
    CHIP8_0x3xnn(instruction, chip8);
    break;
  case 0x4000:
    CHIP8_0x4xnn(instruction, chip8);
    break;
  case 0x5000:
    CHIP8_0x5xy0(instruction, chip8);
    break;
  case 0x6000:
    CHIP8_0x6xnn(instruction, chip8);
    break;
  case 0x7000:
    CHIP8_0x7xnn(instruction, chip8);
    break;
  case 0x8000:
    CHIP8_0x8xy_(instruction, chip8);
    break;
  case 0x9000:
    CHIP8_0x9xy0(instruction, chip8);
    break;
  case 0xA000:
    CHIP8_0xAnnn(instruction, chip8);
    break;
  case 0xB000:
    CHIP8_0xBnnn(instruction, chip8);
    break;
  case 0xC000:
    CHIP8_0xCxnn(instruction, chip8);
    break;
  case 0xD000:
    CHIP8_0xDxyn(instruction, chip8);
    break;
  case 0xE000:
    CHIP8_0xEx__(instruction, chip8);
    break;
  case 0xF000:
    CHIP8_0xFx__(instruction, chip8);
    break;
  }
}
