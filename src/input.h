#pragma once

#include "chip8.h"
#include <SDL2/SDL_events.h>

Event Chip8_HandleInputEvent(const Chip8 *chip8, SDL_Event event);
