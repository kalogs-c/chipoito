#include "chip8.h"
#include "display.h"
#include "input.h"
#include "instruction.h"
#include "memory.h"
#include <SDL2/SDL_events.h>

Chip8 Chip8_Create(const Display display, const Memory memory) {
    const Chip8 chip8 = {
        .display = display,
        .memory = memory,
        .state = RUNNING,
    };
    return chip8;
};

void Chip8_Stop(const Chip8* chip8) {
    Chip8_DestroyDisplay(&chip8->display);
};

void Chip8_HandleInput(Chip8* chip8) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (Chip8_HandleInputEvent(chip8, event)) {
            case QUIT:
                chip8->state = STOPPED;
                return;
            case FREEZE:
                chip8->state = PAUSED;
                return;
            case PLAY:
                chip8->state = RUNNING;
                return;
            case CLEAR_SCREEN:
                Chip8_ClearPixels(&chip8->display);
            case NONE:
                break;
        };
    }
}

void Chip8_Emulate(Chip8* chip8) {
    Chip8_ClearDisplay(&chip8->display);

    while (chip8->state != STOPPED) {
        Chip8_HandleInput(chip8);

        if (chip8->state == PAUSED) continue;

        Chip8_EmulateInstruction(chip8);
        Chip8_UpdateDisplay(&chip8->display);
        chip8->memory.PC += 2;
    }
}
