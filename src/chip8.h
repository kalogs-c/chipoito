#pragma once

#include "display.h"
#include "memory.h"

typedef enum { QUIT, NONE, FREEZE, PLAY, CLEAR_SCREEN } Event;

typedef enum {
    RUNNING,
    STOPPED,
    PAUSED,
} State;

typedef struct {
    Display display;
    State state;
    Memory memory;
    bool keypad[16]; // Keypad. 0x0 - 0xF.
    char* rom; // ROM.
} Chip8;

Chip8 Chip8_Create(Display display, Memory memory);

void Chip8_Emulate(Chip8* chip8);

void Chip8_Stop(const Chip8* chip8);
