#include "opcodes.h"
#include "instruction.h"
#include <SDL2/SDL_log.h>
#include <stdint.h>

void Chip8_0x00__(const Instruction instruction, Chip8* chip8) {
    switch (instruction.opcode) {
        case 0x00E0:
            Chip8_ClearPixels(&chip8->display);
            break;
        case 0x00EE:
            chip8->memory.SP--;
            chip8->memory.PC = chip8->memory.stack[chip8->memory.SP];
            break;
        default: break;
    }
}

void Chip8_0x1nnn(const Instruction instruction, Chip8* chip8) {
    chip8->memory.PC = instruction.NNN;
}

void Chip8_0x2nnn(const Instruction instruction, Chip8* chip8) {
    chip8->memory.stack[chip8->memory.SP] = chip8->memory.PC;
    chip8->memory.SP++;
    chip8->memory.PC = instruction.NNN;
}

void Chip8_0x3xnn(const Instruction instruction, Chip8* chip8) {
    if (chip8->memory.V[instruction.X] == instruction.NN) {
        chip8->memory.PC += 2;
    }
}

void Chip8_0x4xnn(const Instruction instruction, Chip8* chip8) {
    if (chip8->memory.V[instruction.X] != instruction.NN) {
        chip8->memory.PC += 2;
    }
}

void Chip8_0x5xy0(const Instruction instruction, Chip8* chip8) {
    if (instruction.N != 0) return;

    if (chip8->memory.V[instruction.X] == chip8->memory.V[instruction.Y]) {
        chip8->memory.PC += 2;
    }
}

void Chip8_0x6xnn(const Instruction instruction, Chip8* chip8) {
    chip8->memory.V[instruction.X] = instruction.NN;
}

void Chip8_0x7xnn(const Instruction instruction, Chip8* chip8) {
    chip8->memory.V[instruction.X] += instruction.NN;
}

void Chip8_0x8xy_(const Instruction instruction, Chip8* chip8) {
    switch (instruction.N) {
        case 0:
            chip8->memory.V[instruction.X] = chip8->memory.V[instruction.Y];
            break;

        case 1:
            chip8->memory.V[instruction.X] |= chip8->memory.V[instruction.Y];
            break;

        case 2:
            chip8->memory.V[instruction.X] &= chip8->memory.V[instruction.Y];
            break;

        case 3:
            chip8->memory.V[instruction.X] ^= chip8->memory.V[instruction.Y];
            break;

        case 4: {
            const uint16_t carry = chip8->memory.V[instruction.X] + chip8->memory.V[instruction.Y];
            if (carry > 0xFF) {
                chip8->memory.V[0xF] = 1;
            } else {
                chip8->memory.V[0xF] = 0;
            }
            chip8->memory.V[instruction.X] = carry & 0xFF;
            break;
        }

        case 5:
            if (chip8->memory.V[instruction.X] > chip8->memory.V[instruction.Y]) {
                chip8->memory.V[0xF] = 1;
            } else {
                chip8->memory.V[0xF] = 0;
            }
            chip8->memory.V[instruction.X] -= chip8->memory.V[instruction.Y];
            break;

        case 6:
            chip8->memory.V[0xF] = chip8->memory.V[instruction.X] & 0x1;
            chip8->memory.V[instruction.X] >>= 0x1;
            break;

        case 7:
            if (chip8->memory.V[instruction.Y] > chip8->memory.V[instruction.X]) {
                chip8->memory.V[0xF] = 1;
            } else {
                chip8->memory.V[0xF] = 0;
            }
            chip8->memory.V[instruction.X] =
                    chip8->memory.V[instruction.Y] - chip8->memory.V[instruction.X];
            break;

        case 0xE:
            chip8->memory.V[0xF] = chip8->memory.V[instruction.X] & 0x80;
            chip8->memory.V[instruction.X] <<= 0x1;
            break;
        default: break;
    }
}

void Chip8_0x9xy0(const Instruction instruction, Chip8* chip8) {
    if (chip8->memory.V[instruction.X] != chip8->memory.V[instruction.Y]) {
        chip8->memory.PC += 2;
    }
}

void Chip8_0xAnnn(const Instruction instruction, Chip8* chip8) {
    chip8->memory.I = instruction.NNN;
}

void Chip8_0xBnnn(const Instruction instruction, Chip8* chip8) {
    chip8->memory.PC = chip8->memory.V[0] + instruction.NNN;
}

void Chip8_0xCxnn(const Instruction instruction, Chip8* chip8) {
    chip8->memory.V[instruction.X] = (rand() % 0x100) & instruction.NN;
}

void Chip8_0xDxyn(const Instruction instruction, Chip8* chip8) {
    uint8_t x = chip8->memory.V[instruction.X] % DISPLAY_WIDTH;
    uint8_t y = chip8->memory.V[instruction.Y] % DISPLAY_HEIGHT;

    const uint8_t initial_x = x;

    chip8->memory.V[0xF] = 0;

    for (uint8_t row = 0; row < instruction.N; row++) {
        const uint8_t sprite = chip8->memory.ram[chip8->memory.I + row];
        x = initial_x;

        for (int8_t column = 7; column >= 0; column--) {
            bool* pixel = &chip8->display.pixels[y * DISPLAY_WIDTH + x];
            const bool mask = (sprite & (1 << column));

            if (mask && *pixel) {
                chip8->memory.V[0xF] = 1;
            }

            *pixel ^= (mask != 0);

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

    chip8->display.redraw = true;
}

void Chip8_0xEx__(const Instruction instruction, Chip8* chip8) {
    switch (instruction.NN) {
        case 0x9E:
            if (chip8->keypad[chip8->memory.V[instruction.X]]) {
                chip8->memory.PC += 2;
            }
            break;
        case 0xA1:
            if (!chip8->keypad[chip8->memory.V[instruction.X]]) {
                chip8->memory.PC += 2;
            }
            break;
        default: break;
    }
}

void Chip8_0xFx__(const Instruction instruction, Chip8* chip8) {
    switch (instruction.NN) {
        case 0x07:
            chip8->memory.V[instruction.X] = chip8->memory.delay_timer;
            break;
        case 0x0A:
            // TODO
            SDL_Log("Instruction 0xFx0A: TODO - Wait for a key press and store it on Vx");
            break;
        case 0x15:
            chip8->memory.delay_timer = chip8->memory.V[instruction.X];
            break;
        case 0x18:
            chip8->memory.sound_timer = chip8->memory.V[instruction.X];
            break;
        case 0x1E:
            chip8->memory.I += chip8->memory.V[instruction.X];
            break;
        case 0x29:
            // TODO
            SDL_Log("Instruction 0xFx29: TODO - Set I (%X) to the location of sprite", chip8->memory.I);
            break;
        case 0x33: {
            const uint8_t value = chip8->memory.V[instruction.X];
            chip8->memory.ram[chip8->memory.I] = value / 100;
            chip8->memory.ram[chip8->memory.I + 1] = (value / 10) % 10;
            chip8->memory.ram[chip8->memory.I + 2] = value % 10;
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
        default: break;
    }
}
