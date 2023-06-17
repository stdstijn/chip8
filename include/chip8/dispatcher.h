#ifndef CHIP8_DISPATCHER_H
#define CHIP8_DISPATCHER_H

#include "chip8/chip8.h"

#include <stdint.h>

typedef struct Chip8_Cpu Chip8_Cpu;

typedef enum Chip8_DispatchCodes
{
    OPCODE_OK = 0,
    OPCODE_INVALID = 1
} Chip8_DispatchCodes;

Chip8_DispatchCodes Chip8_DispatchOpcode(Chip8_Cpu* cpu);

#endif // CHIP8_DISPATCHER_H
