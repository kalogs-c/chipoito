#pragma once

#include <stdint.h>

static const uint16_t ROM_ENTRY_POINT = 0x200;

typedef struct {
    uint8_t ram[4096]; // 4096 bytes of RAM.
    uint16_t stack[12]; // 12 levels of stack.
    uint16_t SP; // Stack pointer.
    uint8_t V[16]; // 16 8-bit general purpose registers.
    uint16_t I; // 16-bit address register.
    uint16_t PC; // Program counter.
    uint8_t delay_timer; // 8-bit delay timer.
    uint8_t sound_timer; // 8-bit sound timer.
} Memory;

Memory Chip8_CreateMemory(const char* rom_file_path);
