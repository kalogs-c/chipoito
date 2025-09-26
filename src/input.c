#include "input.h"
#include <SDL2/SDL_keycode.h>

Event handleKey(const SDL_Keycode key, const State state) {
    switch (key) {
        case SDLK_ESCAPE:
            return QUIT;
        case SDLK_SPACE:
            return state == RUNNING ? FREEZE : PLAY;
        default:
            return NONE;
    }
}

Event Chip8_HandleInputEvent(const Chip8* chip8, const SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT:
            return QUIT;
        case SDL_KEYDOWN:
            return handleKey(event.key.keysym.sym, chip8->state);
        default:
            return NONE;
    };
}
