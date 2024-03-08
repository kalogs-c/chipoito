#ifndef INPUT_H
#define INPUT_H

#include "../chip8.h"
#include <SDL2/SDL_events.h>

typedef enum { QUIT, NONE } Event;

Event CHIP8_HandleInputEvent(Chip8 *chip8, SDL_Event event);

#endif // !INPUT_H