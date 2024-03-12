#include "opcodes.h"
#include "instruction.h"
#include <SDL2/SDL_log.h>
#include <stdint.h>

void CHIP8_0x00__(Instruction instruction, Chip8 *chip8) {
  switch (instruction.opcode) {
  case 0x00E0:
    SDL_Log("Instruction 0x00E0: Clear Screen");
    CHIP8_ClearPixels(chip8->display);
    break;
  case 0x00EE:
    SDL_Log("Instruction 0x00EE: Return from subroutine");
    chip8->memory->PC = chip8->memory->stack[chip8->memory->SP];
    break;
  }
}

void CHIP8_0x1nnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x1nnn: Jump to address NNN (0x%04X)", instruction.NNN);
  chip8->memory->PC = instruction.NNN;
}

void CHIP8_0x2nnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x2nnn: Call subroutine at NNN (0x%04X)",
          instruction.NNN);
  chip8->memory->SP++;
  chip8->memory->stack[chip8->memory->SP] = chip8->memory->PC;
  chip8->memory->PC = instruction.NNN;
}

void CHIP8_0x3xnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x3xnn: Skip next instruction if Vx (%X) == NN (0x%02X)",
          instruction.X, instruction.NN);
  if (chip8->memory->V[instruction.X] == instruction.NN) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0x4xnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x4xnn: Skip next instruction if Vx (%X) != NN (0x%02X)",
          instruction.X, instruction.NN);
  if (chip8->memory->V[instruction.X] != instruction.NN) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0x5xy0(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x5xy0: Skip next instruction if Vx (%X) == Vy (%X)",
          instruction.X, instruction.Y);
  if (chip8->memory->V[instruction.X] == chip8->memory->V[instruction.Y]) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0x6xnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x6xnn: Set Vx (%X) to NN (0x%02X)", instruction.X,
          instruction.NN);
  chip8->memory->V[instruction.X] = instruction.NN;
}

void CHIP8_0x7xnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x7xnn: Set Vx (%X) to NN (0x%02X) + Vx (%X)",
          instruction.X, instruction.NN, instruction.X);
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

void CHIP8_0xDxyn(Instruction instruction, Chip8 *chip8) {
  // TODO
  (void)instruction;
  (void)chip8;
}

void CHIP8_0xEx__(Instruction instruction, Chip8 *chip8) {
  switch (instruction.NN) {
  case 0x9E:
    if (chip8->keypad[chip8->memory->V[instruction.X]]) {
      chip8->memory->PC += 2;
    }
    break;
  case 0xA1:
    if (!chip8->keypad[chip8->memory->V[instruction.X]]) {
      chip8->memory->PC += 2;
    }
    break;
  }
}

void CHIP8_0xFx__(Instruction instruction, Chip8 *chip8) {
  switch (instruction.NN) {
  case 0x07:
    chip8->memory->V[instruction.X] = chip8->memory->delay_timer;
    break;
  case 0x0A:
    // TODO
    break;
  case 0x15:
    chip8->memory->delay_timer = chip8->memory->V[instruction.X];
    break;
  case 0x18:
    chip8->memory->sound_timer = chip8->memory->V[instruction.X];
    break;
  case 0x1E:
    chip8->memory->I += chip8->memory->V[instruction.X];
    break;
  case 0x29:
    // TODO
    break;
  case 0x33: {
    uint8_t value = chip8->memory->V[instruction.X];
    chip8->memory->ram[chip8->memory->I] = value / 100;
    chip8->memory->ram[chip8->memory->I + 1] = (value / 10) % 10;
    chip8->memory->ram[chip8->memory->I + 2] = value % 10;
    break;
  }
  case 0x55:
    // TODO
    break;
  case 0x65:
    // TODO
    break;
  }
}
