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
    chip8->memory->PC = chip8->memory->stack[--chip8->memory->SP];
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
          chip8->memory->V[instruction.X], instruction.NN);
  if (chip8->memory->V[instruction.X] == instruction.NN) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0x4xnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x4xnn: Skip next instruction if Vx (%X) != NN (0x%02X)",
          chip8->memory->V[instruction.X], instruction.NN);
  if (chip8->memory->V[instruction.X] != instruction.NN) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0x5xy0(Instruction instruction, Chip8 *chip8) {
  if (instruction.N == 0) {
    return;
  }

  SDL_Log("Instruction 0x5xy0: Skip next instruction if Vx (%X) == Vy (%X)",
          chip8->memory->V[instruction.X], chip8->memory->V[instruction.Y]);
  if (chip8->memory->V[instruction.X] == chip8->memory->V[instruction.Y]) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0x6xnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x6xnn: Set Vx (0x%X) to NN (0x%02X)",
          chip8->memory->V[instruction.X], instruction.NN);
  chip8->memory->V[instruction.X] = instruction.NN;
}

void CHIP8_0x7xnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x7xnn: Set Vx to NN (0x%02X) + Vx (%X)", instruction.NN,
          chip8->memory->V[instruction.X]);
  chip8->memory->V[instruction.X] += instruction.NN;
}

void CHIP8_0x8xy_(Instruction instruction, Chip8 *chip8) {
  switch (instruction.N) {
  case 0:
    SDL_Log("Instruction 0x8xy0: Set Vx (%X) to Vy (%X)",
            chip8->memory->V[instruction.X], chip8->memory->V[instruction.Y]);
    chip8->memory->V[instruction.X] = chip8->memory->V[instruction.Y];
    break;

  case 1:
    SDL_Log("Instruction 0x8xy1: Set Vx to Vy (%X) OR Vx (%X)",
            chip8->memory->V[instruction.Y], chip8->memory->V[instruction.X]);
    chip8->memory->V[instruction.X] |= chip8->memory->V[instruction.Y];
    break;

  case 2:
    SDL_Log("Instruction 0x8xy2: Set Vx to Vy (%X) AND Vx (%X)",
            chip8->memory->V[instruction.Y], chip8->memory->V[instruction.X]);
    chip8->memory->V[instruction.X] &= chip8->memory->V[instruction.Y];
    break;

  case 3:
    SDL_Log("Instruction 0x8xy3: Set Vx to Vy (%X) XOR Vx (%X)",
            chip8->memory->V[instruction.Y], chip8->memory->V[instruction.X]);
    chip8->memory->V[instruction.X] ^= chip8->memory->V[instruction.Y];
    break;

  case 4: {
    SDL_Log("Instruction 0x8xy4: Set Vx to the last two bytes of Vy (%X) "
            "+ Vx (%X) if carry",
            chip8->memory->V[instruction.Y], chip8->memory->V[instruction.X]);
    uint16_t carry =
        chip8->memory->V[instruction.X] + chip8->memory->V[instruction.Y];
    if (carry > 0xFF) {
      chip8->memory->V[0xF] = 1;
    } else {
      chip8->memory->V[0xF] = 0;
    }
    chip8->memory->V[instruction.X] = carry & 0xFF;
    break;
  }

  case 5:
    SDL_Log("Instruction 0x8xy5: Set Vx to Vx (%X) - Vy (%X) and set VF "
            "to 1 if Vx > Vy, otherwise set VF to 0",
            chip8->memory->V[instruction.X], chip8->memory->V[instruction.Y]);
    if (chip8->memory->V[instruction.X] > chip8->memory->V[instruction.Y]) {
      chip8->memory->V[0xF] = 1;
    } else {
      chip8->memory->V[0xF] = 0;
    }
    chip8->memory->V[instruction.X] -= chip8->memory->V[instruction.Y];
    break;

  case 6:
    SDL_Log("Instruction 0x8xy6: Set Vx to Vx / 2 and set VF to the last "
            "bit of Vx (%X)",
            chip8->memory->V[instruction.X]);
    chip8->memory->V[0xF] = chip8->memory->V[instruction.X] & 0x1;
    chip8->memory->V[instruction.X] >>= 0x1;
    break;

  case 7:
    SDL_Log("Instruction 0x8xy7: Set Vx to Vy (%X) - Vx (%X) and set VF "
            "to 1 if Vy > Vx, otherwise set VF to 0",
            chip8->memory->V[instruction.Y], chip8->memory->V[instruction.X]);
    if (chip8->memory->V[instruction.Y] > chip8->memory->V[instruction.X]) {
      chip8->memory->V[0xF] = 1;
    } else {
      chip8->memory->V[0xF] = 0;
    }
    chip8->memory->V[instruction.X] =
        chip8->memory->V[instruction.Y] - chip8->memory->V[instruction.X];
    break;

  case 0xE:
    SDL_Log("Instruction 0x8xyE: Set Vx (%X) to Vx * 2 and set VF to the first "
            "bit of Vx",
            chip8->memory->V[instruction.X]);
    chip8->memory->V[0xF] = chip8->memory->V[instruction.X] & 0x80;
    chip8->memory->V[instruction.X] <<= 0x1;
    break;
  }
}

void CHIP8_0x9xy0(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0x9xy0: Skip next instruction if Vx (%X) != Vy (%X)",
          chip8->memory->V[instruction.X], chip8->memory->V[instruction.Y]);
  if (chip8->memory->V[instruction.X] != chip8->memory->V[instruction.Y]) {
    chip8->memory->PC += 2;
  }
}

void CHIP8_0xAnnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0xAnnn: Set I to NNN (0x%04X)", instruction.NNN);
  chip8->memory->I = instruction.NNN;
}

void CHIP8_0xBnnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0xBnnn: Set PC to V0 (0x%04X) + NNN (0x%04X)",
          chip8->memory->V[0], instruction.NNN);
  chip8->memory->PC = chip8->memory->V[0] + instruction.NNN;
}

void CHIP8_0xCxnn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0xCxnn: Set Vx (%X) to a random number between 0 and "
          "255 AND NN (0x%02X)",
          chip8->memory->V[instruction.X], instruction.NN);
  chip8->memory->V[instruction.X] = (rand() % 0xFF) & instruction.NN;
}

void CHIP8_0xDxyn(Instruction instruction, Chip8 *chip8) {
  SDL_Log("Instruction 0xDxyn: TODO - Would draw a sprite at Vx (%X), Vy (%X)",
          chip8->memory->V[instruction.X], chip8->memory->V[instruction.Y]);
  uint8_t x = chip8->memory->V[instruction.X] % DISPLAY_WIDTH;
  uint8_t y = chip8->memory->V[instruction.Y] % DISPLAY_HEIGHT;

  const uint8_t initial_x = x;

  chip8->memory->V[0xF] = 0;

  for (uint8_t row = 0; row < instruction.N; row++) {
    uint8_t sprite = chip8->memory->ram[chip8->memory->I + row];
    x = initial_x;

    for (int8_t column = 7; column >= 0; column--) {
      bool *pixel = &chip8->display->pixels[y * DISPLAY_WIDTH + x];
      const bool mask = (sprite & (1 << column));

      if (mask && *pixel) {
        chip8->memory->V[0xF] = 1;
      }

      *pixel ^= mask;

      x += 1;
      if (x >= DISPLAY_WIDTH) {
        break;
      }
    }

    y += 1;
    if (y >= DISPLAY_HEIGHT) {
      break;
    }
  }
}

void CHIP8_0xEx__(Instruction instruction, Chip8 *chip8) {
  switch (instruction.NN) {
  case 0x9E:
    SDL_Log(
        "Instruction 0xEx9E: Skip next instruction if key Vx (%X) is pressed",
        chip8->memory->V[instruction.X]);
    if (chip8->keypad[chip8->memory->V[instruction.X]]) {
      chip8->memory->PC += 2;
    }
    break;
  case 0xA1:
    SDL_Log("Instruction 0xExA1: Skip next instruction if key Vx (%X) is not "
            "pressed",
            chip8->memory->V[instruction.X]);
    if (!chip8->keypad[chip8->memory->V[instruction.X]]) {
      chip8->memory->PC += 2;
    }
    break;
  }
}

void CHIP8_0xFx__(Instruction instruction, Chip8 *chip8) {
  switch (instruction.NN) {
  case 0x07:
    SDL_Log("Instruction 0xFx07: Set Vx (%X) to the delay timer",
            chip8->memory->V[instruction.X]);
    chip8->memory->V[instruction.X] = chip8->memory->delay_timer;
    break;
  case 0x0A:
    // TODO
    SDL_Log(
        "Instruction 0xFx0A: TODO - Wait for a key press and store it on Vx");
    break;
  case 0x15:
    SDL_Log("Instruction 0xFx15: Set the delay timer to Vx (%X)",
            chip8->memory->V[instruction.X]);
    chip8->memory->delay_timer = chip8->memory->V[instruction.X];
    break;
  case 0x18:
    SDL_Log("Instruction 0xFx18: Set the sound timer to Vx (%X)",
            chip8->memory->V[instruction.X]);
    chip8->memory->sound_timer = chip8->memory->V[instruction.X];
    break;
  case 0x1E:
    SDL_Log("Instruction 0xFx1E: Set I (%X) to I (%X) + Vx (%X)",
            chip8->memory->I, chip8->memory->I,
            chip8->memory->V[instruction.X]);
    chip8->memory->I += chip8->memory->V[instruction.X];
    break;
  case 0x29:
    // TODO
    SDL_Log("Instruction 0xFx29: TODO - Set I (%X) to the location of sprite",
            chip8->memory->I);
    break;
  case 0x33: {
    SDL_Log("Instruction 0xFx33: Store BCD representation of Vx (%X)",
            chip8->memory->V[instruction.X]);
    uint8_t value = chip8->memory->V[instruction.X];
    chip8->memory->ram[chip8->memory->I] = value / 100;
    chip8->memory->ram[chip8->memory->I + 1] = (value / 10) % 10;
    chip8->memory->ram[chip8->memory->I + 2] = value % 10;
    break;
  }
  case 0x55:
    // TODO
    SDL_Log("Instruction 0xFx55: TODO - Store V0 to Vx in memory");
    break;
  case 0x65:
    // TODO
    SDL_Log("Instruction 0xFx65: TODO - Load V0 to Vx from memory");
    break;
  }
}
