#ifndef CHIP8_H
#define CHIP8_H

#include "display/display.h"

typedef enum {
  RUNNING,
  STOPPED,
} State;

typedef struct {
  Display *display;
  State state;
} Chip8;

Chip8 *CHIP8_Create(DisplayConfig config);
void CHIP8_Destroy(Chip8 *chip8);

void CHIP8_Start(Chip8 *chip8);

#endif // !CHIP8_H
