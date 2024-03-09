#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdio.h>

#define MEMORY_SIZE 4096
#define STACK_SIZE 12
#define NUM_REGISTERS 16
#define ROM_ENTRY_POINT 0x200

typedef struct {
  uint8_t ram[MEMORY_SIZE];   // 4096 bytes of RAM.
  uint16_t stack[STACK_SIZE]; // 12 levels of stack.
  uint8_t V[NUM_REGISTERS];   // 16 8-bit general purpose registers.
  uint16_t I;                 // 16-bit address register.
  uint16_t PC;                // Program counter.
  uint8_t delay_timer;        // 8-bit delay timer.
  uint8_t sound_timer;        // 8-bit sound timer.
} Memory;

Memory *CHIP8_CreateMemory(const char *rom_file_path);
void CHIP8_DestroyMemory(Memory *memory);

#endif // !MEMORY_H
