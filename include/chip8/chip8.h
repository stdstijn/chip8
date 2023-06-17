#ifndef CHIP8_H
#define CHIP8_H

#include "chip8/dispatcher.h"

#include <stddef.h>
#include <stdint.h>

typedef struct Chip8_Cpu Chip8_Cpu;
typedef uint16_t (*Chip8_Dispatcher)(Chip8_Cpu*);
typedef void (*Chip8_Function)(Chip8_Cpu*);

enum VirtualMachineDescription
{
    MEMORY_SIZE = 0x1000,
    VIDEO_SIZE = 0x0800,
    START_ADDRESS = 0x0200,
    FONTSET_ADDRESS = 0x0050,
    REGISTER_COUNT = 16,
    STACK_LEVELS = 16,
    CLOCK_HZ = 60,
    KEY_COUNT = 16,
    VIDEO_WIDTH = 64,
    VIDEO_HEIGHT = 32,
    FONT_SIZE = 80
};

typedef struct Chip8_Config
{
    uint8_t reset : 1;
    uint8_t memory : 1;
    uint8_t display : 1;
    uint8_t clipping : 1;
    uint8_t shifting : 1;
    uint8_t jumping : 1;
} Chip8_Config;

typedef struct Chip8_Opcode
{
    uint64_t inst : 16;
    uint64_t x : 4;
    uint64_t y : 4;
    uint64_t n : 4;
    uint64_t nn : 8;
    uint64_t nnn : 12;
} Chip8_Opcode;

struct Chip8_Cpu
{
    // Quirk configuration
    Chip8_Config config;

    // Virtual machine fields
    Chip8_Opcode opcode;
    uint8_t memory[MEMORY_SIZE];
    uint16_t pc;
    uint16_t stack[STACK_LEVELS];
    uint16_t sp;
    uint16_t i;
    uint8_t v[REGISTER_COUNT];
    uint8_t delaytimer;
    uint8_t soundtimer;
    uint16_t key;
    uint8_t gfx[VIDEO_WIDTH * VIDEO_HEIGHT / 8];
    uint8_t vbi;
    uint8_t draw;

    // Opcode table dispatcher function pointer array
    Chip8_Dispatcher Dispatcher[0xF + 1];

    // Opcode sub table implementation function pointer arrays
    Chip8_Function OP0x[0xE + 1];
    Chip8_Function OP1x[0x0 + 1];
    Chip8_Function OP2x[0x0 + 1];
    Chip8_Function OP3x[0x0 + 1];
    Chip8_Function OP4x[0x0 + 1];
    Chip8_Function OP5x[0x0 + 1];
    Chip8_Function OP6x[0x0 + 1];
    Chip8_Function OP7x[0x0 + 1];
    Chip8_Function OP8x[0xE + 1];
    Chip8_Function OP9x[0x0 + 1];
    Chip8_Function OPAx[0x0 + 1];
    Chip8_Function OPBx[0x0 + 1];
    Chip8_Function OPCx[0x0 + 1];
    Chip8_Function OPDx[0x0 + 1];
    Chip8_Function OPEx[0xE + 1];
    Chip8_Function OPFx[0x65 + 1];
};

void Chip8_Create(Chip8_Cpu* cpu, Chip8_Config config);
void Chip8_Destroy(Chip8_Cpu* cpu);

void Chip8_Cycle(Chip8_Cpu* cpu, const uint32_t time);

void Chip8_OP00E0(Chip8_Cpu* cpu); // CLS
void Chip8_OP00EE(Chip8_Cpu* cpu); // RET
void Chip8_OP0nnn(Chip8_Cpu* cpu); // SYS addr
void Chip8_OP1nnn(Chip8_Cpu* cpu); // JMP addr
void Chip8_OP2nnn(Chip8_Cpu* cpu); // CALL addr
void Chip8_OP3xkk(Chip8_Cpu* cpu); // SE Vx, byte
void Chip8_OP4xkk(Chip8_Cpu* cpu); // SNE Vx, byte
void Chip8_OP5xy0(Chip8_Cpu* cpu); // SE Vx, Vy
void Chip8_OP6xkk(Chip8_Cpu* cpu); // LD Vx, byte
void Chip8_OP7xkk(Chip8_Cpu* cpu); // ADD Vx, byte
void Chip8_OP8xy0(Chip8_Cpu* cpu); // LD Vx, Vy
void Chip8_OP8xy1(Chip8_Cpu* cpu); // OR Vx, Vy
void Chip8_OP8xy2(Chip8_Cpu* cpu); // AND Vx, Vy
void Chip8_OP8xy3(Chip8_Cpu* cpu); // XOR Vx, Vy
void Chip8_OP8xy4(Chip8_Cpu* cpu); // ADD Vx, Vy
void Chip8_OP8xy5(Chip8_Cpu* cpu); // SUB Vx, Vy
void Chip8_OP8xy6(Chip8_Cpu* cpu); // SHR Vx {, Vy}
void Chip8_OP8xy7(Chip8_Cpu* cpu); // SUBN Vx, Vy
void Chip8_OP8xyE(Chip8_Cpu* cpu); // SHL Vx {, Vy}
void Chip8_OP9xy0(Chip8_Cpu* cpu); // SNE Vx, Vy
void Chip8_OPAnnn(Chip8_Cpu* cpu); // LD I, addr
void Chip8_OPBnnn(Chip8_Cpu* cpu); // JP V0, addr
void Chip8_OPCxkk(Chip8_Cpu* cpu); // RND Vx, byte
void Chip8_OPDxyn(Chip8_Cpu* cpu); // DRW Vx, Vy, nibble
void Chip8_OPEx9E(Chip8_Cpu* cpu); // SKP Vx
void Chip8_OPExA1(Chip8_Cpu* cpu); // SKNP Vx
void Chip8_OPFx07(Chip8_Cpu* cpu); // LD Vx, DT
void Chip8_OPFx0A(Chip8_Cpu* cpu); // LD Vx, K
void Chip8_OPFx15(Chip8_Cpu* cpu); // LD DT, Vx
void Chip8_OPFx18(Chip8_Cpu* cpu); // LD ST, Vx
void Chip8_OPFx1E(Chip8_Cpu* cpu); // ADD I, Vx
void Chip8_OPFx29(Chip8_Cpu* cpu); // LD F, Vx
void Chip8_OPFx33(Chip8_Cpu* cpu); // LD B, Vx
void Chip8_OPFx55(Chip8_Cpu* cpu); // LD [I], Vx
void Chip8_OPFx65(Chip8_Cpu* cpu); // LD Vx, [I]

#endif // CHIP8_H
