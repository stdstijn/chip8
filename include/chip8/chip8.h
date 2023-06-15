#ifndef CHIP8_H
#define CHIP8_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Chip8_Cpu Chip8_Cpu;
typedef void (*OpcodeFunc)(Chip8_Cpu*);

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
    uint8_t display: 1;
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

typedef struct Chip8_Dispatcher
{
    OpcodeFunc table[0xF + 1];
    OpcodeFunc table0X[0xE + 1];
    OpcodeFunc table1X[0x0 + 1];
    OpcodeFunc table2X[0x0 + 1];
    OpcodeFunc table3X[0x0 + 1];
    OpcodeFunc table4X[0x0 + 1];
    OpcodeFunc table5X[0x0 + 1];
    OpcodeFunc table6X[0x0 + 1];
    OpcodeFunc table7X[0x0 + 1];
    OpcodeFunc table8X[0xE + 1];
    OpcodeFunc table9X[0x0 + 1];
    OpcodeFunc tableAX[0x0 + 1];
    OpcodeFunc tableBX[0x0 + 1];
    OpcodeFunc tableCX[0x0 + 1];
    OpcodeFunc tableDX[0x0 + 1];
    OpcodeFunc tableEX[0xE + 1];
    OpcodeFunc tableFX[0x65 + 1];
} Chip8_Dispatcher;

struct Chip8_Cpu
{
    uint8_t memory[MEMORY_SIZE];
    uint16_t pc;
    Chip8_Opcode opcode;
    uint16_t stack[STACK_LEVELS];
    uint16_t sp;
    uint16_t i;
    uint8_t v[REGISTER_COUNT];
    uint8_t delaytimer;
    uint8_t soundtimer;
    uint16_t key;
    uint8_t gfx[VIDEO_WIDTH * VIDEO_HEIGHT / 8];
    Chip8_Dispatcher dispatcher;
    uint8_t vbi;
    uint8_t draw;
};

void Chip8_Create(Chip8_Cpu* cpu);
void Chip8_Destroy(Chip8_Cpu* cpu);

void Chip8_Cycle(Chip8_Cpu* cpu, const uint32_t time);

void OP_00E0(Chip8_Cpu* cpu); // CLS
void OP_00EE(Chip8_Cpu* cpu); // RET
void OP_0nnn(Chip8_Cpu* cpu); // SYS addr
void OP_1nnn(Chip8_Cpu* cpu); // JMP addr
void OP_2nnn(Chip8_Cpu* cpu); // CALL addr
void OP_3xkk(Chip8_Cpu* cpu); // SE Vx, byte
void OP_4xkk(Chip8_Cpu* cpu); // SNE Vx, byte
void OP_5xy0(Chip8_Cpu* cpu); // SE Vx, Vy
void OP_6xkk(Chip8_Cpu* cpu); // LD Vx, byte
void OP_7xkk(Chip8_Cpu* cpu); // ADD Vx, byte
void OP_8xy0(Chip8_Cpu* cpu); // LD Vx, Vy
void OP_8xy1(Chip8_Cpu* cpu); // OR Vx, Vy
void OP_8xy2(Chip8_Cpu* cpu); // AND Vx, Vy
void OP_8xy3(Chip8_Cpu* cpu); // XOR Vx, Vy
void OP_8xy4(Chip8_Cpu* cpu); // ADD Vx, Vy
void OP_8xy5(Chip8_Cpu* cpu); // SUB Vx, Vy
void OP_8xy6(Chip8_Cpu* cpu); // SHR Vx {, Vy}
void OP_8xy7(Chip8_Cpu* cpu); // SUBN Vx, Vy
void OP_8xyE(Chip8_Cpu* cpu); // SHL Vx {, Vy}
void OP_9xy0(Chip8_Cpu* cpu); // SNE Vx, Vy
void OP_Annn(Chip8_Cpu* cpu); // LD I, addr
void OP_Bnnn(Chip8_Cpu* cpu); // JP V0, addr
void OP_Cxkk(Chip8_Cpu* cpu); // RND Vx, byte
void OP_Dxyn(Chip8_Cpu* cpu); // DRW Vx, Vy, nibble
void OP_Ex9E(Chip8_Cpu* cpu); // SKP Vx
void OP_ExA1(Chip8_Cpu* cpu); // SKNP Vx
void OP_Fx07(Chip8_Cpu* cpu); // LD Vx, DT
void OP_Fx0A(Chip8_Cpu* cpu); // LD Vx, K
void OP_Fx15(Chip8_Cpu* cpu); // LD DT, Vx
void OP_Fx18(Chip8_Cpu* cpu); // LD ST, Vx
void OP_Fx1E(Chip8_Cpu* cpu); // ADD I, Vx
void OP_Fx29(Chip8_Cpu* cpu); // LD F, Vx
void OP_Fx33(Chip8_Cpu* cpu); // LD B, Vx
void OP_Fx55(Chip8_Cpu* cpu); // LD [I], Vx
void OP_Fx65(Chip8_Cpu* cpu); // LD Vx, [I]

#ifdef __cplusplus
}
#endif

#endif // CHIP8_H
