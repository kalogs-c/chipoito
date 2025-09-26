#pragma once

#include "instruction.h"

void Chip8_0x00__(Instruction instruction, Chip8 *chip8);
void Chip8_0x1nnn(Instruction instruction, Chip8 *chip8);
void Chip8_0x2nnn(Instruction instruction, Chip8 *chip8);
void Chip8_0x3xnn(Instruction instruction, Chip8 *chip8);
void Chip8_0x4xnn(Instruction instruction, Chip8 *chip8);
void Chip8_0x5xy0(Instruction instruction, Chip8 *chip8);
void Chip8_0x6xnn(Instruction instruction, Chip8 *chip8);
void Chip8_0x7xnn(Instruction instruction, Chip8 *chip8);
void Chip8_0x8xy_(Instruction instruction, Chip8 *chip8);
void Chip8_0x9xy0(Instruction instruction, Chip8 *chip8);
void Chip8_0xAnnn(Instruction instruction, Chip8 *chip8);
void Chip8_0xBnnn(Instruction instruction, Chip8 *chip8);
void Chip8_0xCxnn(Instruction instruction, Chip8 *chip8);
void Chip8_0xDxyn(Instruction instruction, Chip8 *chip8);
void Chip8_0xEx__(Instruction instruction, Chip8 *chip8);
void Chip8_0xFx__(Instruction instruction, Chip8 *chip8);