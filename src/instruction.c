#include "instruction.h"
#include "chip8.h"
#include "memory.h"
#include "opcodes.h"

Instruction mount_instruction(const Memory* memory) {
    Instruction instruction;
    instruction.opcode = (memory->ram[memory->PC] << 8) | memory->ram[memory->PC + 1];
    instruction.X = (instruction.opcode & 0x0F00) >> 8;
    instruction.Y = (instruction.opcode & 0x00F0) >> 4;
    instruction.N = instruction.opcode & 0x000F;
    instruction.NN = instruction.opcode & 0x00FF;
    instruction.NNN = instruction.opcode & 0x0FFF;
    return instruction;
}

void Chip8_EmulateInstruction(Chip8* chip8) {
    const Instruction instruction = mount_instruction(&chip8->memory);

    switch (instruction.opcode & 0xF000) {
        case 0x0000: return Chip8_0x00__(instruction, chip8);
        case 0x1000: return Chip8_0x1nnn(instruction, chip8);
        case 0x2000: return Chip8_0x2nnn(instruction, chip8);
        case 0x3000: return Chip8_0x3xnn(instruction, chip8);
        case 0x4000: return Chip8_0x4xnn(instruction, chip8);
        case 0x5000: return Chip8_0x5xy0(instruction, chip8);
        case 0x6000: return Chip8_0x6xnn(instruction, chip8);
        case 0x7000: return Chip8_0x7xnn(instruction, chip8);
        case 0x8000: return Chip8_0x8xy_(instruction, chip8);
        case 0x9000: return Chip8_0x9xy0(instruction, chip8);
        case 0xA000: return Chip8_0xAnnn(instruction, chip8);
        case 0xB000: return Chip8_0xBnnn(instruction, chip8);
        case 0xC000: return Chip8_0xCxnn(instruction, chip8);
        case 0xD000: return Chip8_0xDxyn(instruction, chip8);
        case 0xE000: return Chip8_0xEx__(instruction, chip8);
        case 0xF000: return Chip8_0xFx__(instruction, chip8);
        default: break;
    }
}
