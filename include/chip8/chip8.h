#ifndef CHIP8_H
#define CHIP8_H

#include <stddef.h>
#include <stdint.h>

typedef struct Chip8_Cpu Chip8_Cpu;

enum Chip8_VirtualMachineDescription
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

typedef enum Chip8_CycleCodes
{
    CYCLE_OK = 0,
    CYCLE_NOT_IMPLEMENTED = 1
} Chip8_CycleCodes;

typedef struct Chip8_Config
{
    uint8_t flagReset;
    uint8_t indexIncrement;
    uint8_t displayWait;
    uint8_t spriteClipping;
    uint8_t shiftInPlace;
    uint8_t jumpValue;
} Chip8_Config;

typedef struct Chip8_Opcode
{
    uint16_t inst;
    uint16_t x;
    uint16_t y;
    uint16_t n;
    uint16_t nn;
    uint16_t nnn;
} Chip8_Opcode;

struct Chip8_Cpu
{
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
    Chip8_Config config;
};

void Chip8_Create(Chip8_Cpu* cpu, Chip8_Config* config);
void Chip8_Destroy(Chip8_Cpu* cpu);

Chip8_CycleCodes Chip8_Cycle(Chip8_Cpu* cpu, const uint32_t time);

void Chip8_Op00E0(Chip8_Cpu* cpu); // CLS
void Chip8_Op00EE(Chip8_Cpu* cpu); // RET
void Chip8_Op0nnn(Chip8_Cpu* cpu); // SYS addr
void Chip8_Op1nnn(Chip8_Cpu* cpu); // JMP addr
void Chip8_Op2nnn(Chip8_Cpu* cpu); // CALL addr
void Chip8_Op3xkk(Chip8_Cpu* cpu); // SE Vx, byte
void Chip8_Op4xkk(Chip8_Cpu* cpu); // SNE Vx, byte
void Chip8_Op5xy0(Chip8_Cpu* cpu); // SE Vx, Vy
void Chip8_Op6xkk(Chip8_Cpu* cpu); // LD Vx, byte
void Chip8_Op7xkk(Chip8_Cpu* cpu); // ADD Vx, byte
void Chip8_Op8xy0(Chip8_Cpu* cpu); // LD Vx, Vy
void Chip8_Op8xy1(Chip8_Cpu* cpu); // OR Vx, Vy
void Chip8_Op8xy2(Chip8_Cpu* cpu); // AND Vx, Vy
void Chip8_Op8xy3(Chip8_Cpu* cpu); // XOR Vx, Vy
void Chip8_Op8xy4(Chip8_Cpu* cpu); // ADD Vx, Vy
void Chip8_Op8xy5(Chip8_Cpu* cpu); // SUB Vx, Vy
void Chip8_Op8xy6(Chip8_Cpu* cpu); // SHR Vx {, Vy}
void Chip8_Op8xy7(Chip8_Cpu* cpu); // SUBN Vx, Vy
void Chip8_Op8xyE(Chip8_Cpu* cpu); // SHL Vx {, Vy}
void Chip8_Op9xy0(Chip8_Cpu* cpu); // SNE Vx, Vy
void Chip8_OpAnnn(Chip8_Cpu* cpu); // LD I, addr
void Chip8_OpBnnn(Chip8_Cpu* cpu); // JP V0, addr
void Chip8_OpCxkk(Chip8_Cpu* cpu); // RND Vx, byte
void Chip8_OpDxyn(Chip8_Cpu* cpu); // DRW Vx, Vy, nibble
void Chip8_OpEx9E(Chip8_Cpu* cpu); // SKP Vx
void Chip8_OpExA1(Chip8_Cpu* cpu); // SKNP Vx
void Chip8_OpFx07(Chip8_Cpu* cpu); // LD Vx, DT
void Chip8_OpFx0A(Chip8_Cpu* cpu); // LD Vx, K
void Chip8_OpFx15(Chip8_Cpu* cpu); // LD DT, Vx
void Chip8_OpFx18(Chip8_Cpu* cpu); // LD ST, Vx
void Chip8_OpFx1E(Chip8_Cpu* cpu); // ADD I, Vx
void Chip8_OpFx29(Chip8_Cpu* cpu); // LD F, Vx
void Chip8_OpFx33(Chip8_Cpu* cpu); // LD B, Vx
void Chip8_OpFx55(Chip8_Cpu* cpu); // LD [I], Vx
void Chip8_OpFx65(Chip8_Cpu* cpu); // LD Vx, [I]

#endif // CHIP8_H
