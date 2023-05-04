#include "chip8/chip8.h"

static const uint8_t fontset[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

static void dispatcher0(CPU *cpu)
{
    (*(cpu->subtable0[cpu->opcode & 0x000Fu]))(cpu);
}

static void dispatcher1(CPU *cpu)
{
    (*(cpu->subtable1[0x0]))(cpu);
}

static void dispatcher2(CPU *cpu)
{
    (*(cpu->subtable2[0x0]))(cpu);
}

static void dispatcher3(CPU *cpu)
{
    (*(cpu->subtable3[0x0]))(cpu);
}

static void dispatcher4(CPU *cpu)
{
    (*(cpu->subtable4[0x0]))(cpu);
}

static void dispatcher5(CPU *cpu)
{
    (*(cpu->subtable5[0x0]))(cpu);
}

static void dispatcher6(CPU *cpu)
{
    (*(cpu->subtable6[0x0]))(cpu);
}

static void dispatcher7(CPU *cpu)
{
    (*(cpu->subtable7[0x0]))(cpu);
}

static void dispatcher8(CPU *cpu)
{
    (*(cpu->subtable8[cpu->opcode & 0x000Fu]))(cpu);
}

static void dispatcher9(CPU *cpu)
{
    (*(cpu->subtable9[0x0]))(cpu);
}

static void dispatcherA(CPU *cpu)
{
    (*(cpu->subtableA[0x0]))(cpu);
}

static void dispatcherB(CPU *cpu)
{
    (*(cpu->subtableB[0x0]))(cpu);
}

static void dispatcherC(CPU *cpu)
{
    (*(cpu->subtableC[0x0]))(cpu);
}

static void dispatcherD(CPU *cpu)
{
    (*(cpu->subtableD[0x0]))(cpu);
}

static void dispatcherE(CPU *cpu)
{
    (*(cpu->subtableE[cpu->opcode & 0x000Fu]))(cpu);
}

static void dispatcherF(CPU *cpu)
{
    (*(cpu->subtableF[cpu->opcode & 0x00FFu]))(cpu);
}

static void clearMemory(void *ptr, size_t num)
{
    uint8_t *cptr = ptr;

    for (size_t i = 0; i < num; i++)
    {
        cptr[i] = 0;
    }
}

static void copyMemory(void *dest, const void *src, size_t num)
{
    const uint8_t *csrc = src;
    uint8_t *cdest = dest;

    for (size_t i = 0; i < num; i++)
    {
        cdest[i] = csrc[i];
    }
}

static void nullOpcodetablePointers(OpcodeFunc dispatcher[], size_t num)
{
    for (size_t i = 0; i < num; i++)
    {
        dispatcher[i] = OP_0nnn;
    }
}

void Chip8_Create(CPU *cpu)
{
    // Initialize registers and memory once
    clearMemory(cpu, sizeof(CPU));
    cpu->pc = START_ADDRESS;

    // Load fontset
    copyMemory(&cpu->memory[FONTSET_ADDRESS], fontset, 0x50);

    // Set subtable function pointers to OP_0nnn initially
    nullOpcodetablePointers(cpu->subtable0, 0xE + 1);
    nullOpcodetablePointers(cpu->subtable1, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtable2, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtable3, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtable4, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtable5, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtable6, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtable7, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtable8, 0xE + 1);
    nullOpcodetablePointers(cpu->subtable9, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtableA, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtableB, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtableC, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtableD, 0x0 + 1);
    nullOpcodetablePointers(cpu->subtableE, 0xE + 1);
    nullOpcodetablePointers(cpu->subtableF, 0x65 + 1);

    // Setup opcode function pointer table
    cpu->opcodetable[0x0] = dispatcher0;
    cpu->opcodetable[0x1] = dispatcher1;
    cpu->opcodetable[0x2] = dispatcher2;
    cpu->opcodetable[0x3] = dispatcher3;
    cpu->opcodetable[0x4] = dispatcher4;
    cpu->opcodetable[0x5] = dispatcher5;
    cpu->opcodetable[0x6] = dispatcher6;
    cpu->opcodetable[0x7] = dispatcher7;
    cpu->opcodetable[0x8] = dispatcher8;
    cpu->opcodetable[0x9] = dispatcher9;
    cpu->opcodetable[0xA] = dispatcherA;
    cpu->opcodetable[0xB] = dispatcherB;
    cpu->opcodetable[0xC] = dispatcherC;
    cpu->opcodetable[0xD] = dispatcherD;
    cpu->opcodetable[0xE] = dispatcherE;
    cpu->opcodetable[0xF] = dispatcherF;

    // Populate dispatcher function pointer arrays
    cpu->subtable0[0x0] = OP_00E0;
    cpu->subtable0[0xE] = OP_00EE;
    cpu->subtable1[0x0] = OP_1nnn;
    cpu->subtable2[0x0] = OP_2nnn;
    cpu->subtable3[0x0] = OP_3xkk;
    cpu->subtable4[0x0] = OP_4xkk;
    cpu->subtable5[0x0] = OP_5xy0;
    cpu->subtable6[0x0] = OP_6xkk;
    cpu->subtable7[0x0] = OP_7xkk;
    cpu->subtable8[0x0] = OP_8xy0;
    cpu->subtable8[0x1] = OP_8xy1;
    cpu->subtable8[0x2] = OP_8xy2;
    cpu->subtable8[0x3] = OP_8xy3;
    cpu->subtable8[0x4] = OP_8xy4;
    cpu->subtable8[0x5] = OP_8xy5;
    cpu->subtable8[0x6] = OP_8xy6;
    cpu->subtable8[0x7] = OP_8xy7;
    cpu->subtable8[0xE] = OP_8xyE;
    cpu->subtable9[0x0] = OP_9xy0;
    cpu->subtableA[0x0] = OP_Annn;
    cpu->subtableB[0x0] = OP_Bnnn;
    cpu->subtableC[0x0] = OP_Cxkk;
    cpu->subtableD[0x0] = OP_Dxyn;
    cpu->subtableE[0xE] = OP_Ex9E;
    cpu->subtableE[0x1] = OP_ExA1;
    cpu->subtableF[0x07] = OP_Fx07;
    cpu->subtableF[0x0A] = OP_Fx0A;
    cpu->subtableF[0x15] = OP_Fx15;
    cpu->subtableF[0x18] = OP_Fx18;
    cpu->subtableF[0x1E] = OP_Fx1E;
    cpu->subtableF[0x29] = OP_Fx29;
    cpu->subtableF[0x33] = OP_Fx33;
    cpu->subtableF[0x55] = OP_Fx55;
    cpu->subtableF[0x65] = OP_Fx65;
}

void Chip8_Cycle(CPU *cpu)
{
    // Fetch opcode
    cpu->opcode = (cpu->memory[cpu->pc] << 8u) | cpu->memory[cpu->pc + 1];

    // Increment program counter
    cpu->pc += 2;

    // Decode opcode
    uint8_t nibble = (cpu->opcode & 0xF000u) >> 12u;

    // Execute opcode
    (*(cpu->opcodetable[nibble]))(cpu);

    // Update timers
    if (cpu->delaytimer > 0)
    {
        cpu->delaytimer -= 1;
    }
    if (cpu->soundtimer > 0)
    {
        cpu->soundtimer -= 1;
    }
}

void Chip8_Destroy(CPU *cpu)
{
    // Clean registers and memory once
    (void)cpu;
}

void OP_00E0(CPU *cpu) // CLS
{
    clearMemory(cpu->gfx, VIDEO_SIZE);
}

void OP_00EE(CPU *cpu) // RET
{
}

void OP_0nnn(CPU *cpu) // SYS addr
{
}

void OP_1nnn(CPU *cpu) // JMP addr
{
    uint16_t address = cpu->opcode & 0x0FFFu;
    cpu->pc = address;
}

void OP_2nnn(CPU *cpu) // CALL addr
{
}

void OP_3xkk(CPU *cpu) // SE Vx, byte
{
}

void OP_4xkk(CPU *cpu) // SNE Vx, byte
{
}

void OP_5xy0(CPU *cpu) // SE Vx, Vy
{
}

void OP_6xkk(CPU *cpu) // LD Vx, byte
{
    uint8_t Vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;
    cpu->V[Vx] = byte;
}

void OP_7xkk(CPU *cpu) // ADD Vx, byte
{
    uint8_t Vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;
    cpu->V[Vx] += byte;
}

void OP_8xy0(CPU *cpu) // LD Vx, Vy
{
}

void OP_8xy1(CPU *cpu) // OR Vx, Vy
{
}

void OP_8xy2(CPU *cpu) // AND Vx, Vy
{
}

void OP_8xy3(CPU *cpu) // XOR Vx, Vy
{
}

void OP_8xy4(CPU *cpu) // ADD Vx, Vy
{
}

void OP_8xy5(CPU *cpu) // SUB Vx, Vy
{
}

void OP_8xy6(CPU *cpu) // SHR Vx {, Vy}
{
}

void OP_8xy7(CPU *cpu) // SUBN Vx, Vy
{
}

void OP_8xyE(CPU *cpu) // SHL Vx {, Vy}
{
}

void OP_9xy0(CPU *cpu) // SNE Vx, Vy
{
}

void OP_Annn(CPU *cpu) // LD I, addr
{
    uint16_t address = cpu->opcode & 0x0FFFu;
    cpu->I = address;
}

void OP_Bnnn(CPU *cpu) // JP V0, addr
{
}

void OP_Cxkk(CPU *cpu) // RND Vx, byte
{
}

void OP_Dxyn(CPU *cpu) // DRW Vx, Vy, nibble
{
    uint8_t Vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (cpu->opcode & 0x00F0u) >> 4u;
    uint8_t height = cpu->opcode & 0x000Fu;

    // Wrap if going beyond screen boundaries
    uint8_t xPos = cpu->V[Vx] % VIDEO_WIDTH;
    uint8_t yPos = cpu->V[Vy] % VIDEO_HEIGHT;

    cpu->V[0xF] = 0;

    for (size_t row = 0; row < height; ++row)
    {
        uint8_t spriteByte = cpu->memory[cpu->I + row];

        for (size_t col = 0; col < 8; ++col)
        {
            uint8_t spritePixel = spriteByte & (0x80u >> col);
            uint32_t *screenPixel = &cpu->gfx[(yPos + row) * VIDEO_WIDTH + (xPos + col)];

            if (spritePixel)
            {
                if (*screenPixel == 0xFFFFFFFFu)
                {
                    cpu->V[0xF] = 1;
                }

                *screenPixel ^= 0xFFFFFFFFu;
            }
        }
    }
}

void OP_Ex9E(CPU *cpu) // SKP Vx
{
}

void OP_ExA1(CPU *cpu) // SKNP Vx
{
}

void OP_Fx07(CPU *cpu) // LD Vx, DT
{
}

void OP_Fx0A(CPU *cpu) // LD Vx, K
{
}

void OP_Fx15(CPU *cpu) // LD DT, Vx
{
}

void OP_Fx18(CPU *cpu) // LD ST, Vx
{
}

void OP_Fx1E(CPU *cpu) // ADD I, Vx
{
}

void OP_Fx29(CPU *cpu) // LD F, Vx
{
}

void OP_Fx33(CPU *cpu) // LD B, Vx
{
}

void OP_Fx55(CPU *cpu) // LD [I], Vx
{
}

void OP_Fx65(CPU *cpu) // LD Vx, [I]
{
}
