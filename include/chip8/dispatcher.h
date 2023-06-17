#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "chip8/chip8.h"

#include <stdint.h>

typedef struct Chip8_Cpu Chip8_Cpu;

void InitialiseDispatcher(Chip8_Cpu* cpu);

#endif // DISPATCHER_H
