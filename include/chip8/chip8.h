#ifndef CHIP8_H
#define CHIP8_H

typedef struct CPU CPU;
typedef void (*OpcodeFunc)(CPU *);

typedef enum VirtualMachineDescription
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
} VirtualMachineDescription;

struct CPU
{
    unsigned char memory[MEMORY_SIZE];
    unsigned char V[REGISTER_COUNT];
    unsigned short I;
    unsigned short pc;
    unsigned short stack[STACK_LEVELS];
    unsigned short sp;
    unsigned short opcode;
    unsigned char delaytimer;
    unsigned char soundtimer;
    unsigned char key[KEY_COUNT];
    unsigned int gfx[VIDEO_WIDTH * VIDEO_HEIGHT];

    OpcodeFunc opcodetable[0xF + 1];

    OpcodeFunc subtable0[0xE + 1];
    OpcodeFunc subtable1[0x0 + 1];
    OpcodeFunc subtable2[0x0 + 1];
    OpcodeFunc subtable3[0x0 + 1];
    OpcodeFunc subtable4[0x0 + 1];
    OpcodeFunc subtable5[0x0 + 1];
    OpcodeFunc subtable6[0x0 + 1];
    OpcodeFunc subtable7[0x0 + 1];
    OpcodeFunc subtable8[0xE + 1];
    OpcodeFunc subtable9[0x0 + 1];
    OpcodeFunc subtableA[0x0 + 1];
    OpcodeFunc subtableB[0x0 + 1];
    OpcodeFunc subtableC[0x0 + 1];
    OpcodeFunc subtableD[0x0 + 1];
    OpcodeFunc subtableE[0xE + 1];
    OpcodeFunc subtableF[0x65 + 1];
};

void Chip8_Create(CPU *cpu);
void Chip8_Destroy(CPU *cpu);

void Chip8_Cycle(CPU *cpu);

void OP_00E0(CPU *cpu); // CLS
void OP_00EE(CPU *cpu); // RET
void OP_0nnn(CPU *cpu); // SYS addr
void OP_1nnn(CPU *cpu); // JMP addr
void OP_2nnn(CPU *cpu); // CALL addr
void OP_3xkk(CPU *cpu); // SE Vx, byte
void OP_4xkk(CPU *cpu); // SNE Vx, byte
void OP_5xy0(CPU *cpu); // SE Vx, Vy
void OP_6xkk(CPU *cpu); // LD Vx, byte
void OP_7xkk(CPU *cpu); // ADD Vx, byte
void OP_8xy0(CPU *cpu); // LD Vx, Vy
void OP_8xy1(CPU *cpu); // OR Vx, Vy
void OP_8xy2(CPU *cpu); // AND Vx, Vy
void OP_8xy3(CPU *cpu); // XOR Vx, Vy
void OP_8xy4(CPU *cpu); // ADD Vx, Vy
void OP_8xy5(CPU *cpu); // SUB Vx, Vy
void OP_8xy6(CPU *cpu); // SHR Vx {, Vy}
void OP_8xy7(CPU *cpu); // SUBN Vx, Vy
void OP_8xyE(CPU *cpu); // SHL Vx {, Vy}
void OP_9xy0(CPU *cpu); // SNE Vx, Vy
void OP_Annn(CPU *cpu); // LD I, addr
void OP_Bnnn(CPU *cpu); // JP V0, addr
void OP_Cxkk(CPU *cpu); // RND Vx, byte
void OP_Dxyn(CPU *cpu); // DRW Vx, Vy, nibble
void OP_Ex9E(CPU *cpu); // SKP Vx
void OP_ExA1(CPU *cpu); // SKNP Vx
void OP_Fx07(CPU *cpu); // LD Vx, DT
void OP_Fx0A(CPU *cpu); // LD Vx, K
void OP_Fx15(CPU *cpu); // LD DT, Vx
void OP_Fx18(CPU *cpu); // LD ST, Vx
void OP_Fx1E(CPU *cpu); // ADD I, Vx
void OP_Fx29(CPU *cpu); // LD F, Vx
void OP_Fx33(CPU *cpu); // LD B, Vx
void OP_Fx55(CPU *cpu); // LD [I], Vx
void OP_Fx65(CPU *cpu); // LD Vx, [I]

#endif // CHIP8_H
