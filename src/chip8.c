#include "chip8/chip8.h"

static const uint8_t fontset[FONT_SIZE] = {
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

static void dispatcher0(CPU* cpu)
{
    (*(cpu->table0[cpu->opcode & 0x000Fu]))(cpu);
}

static void dispatcher1(CPU* cpu)
{
    (*(cpu->table1[0x0]))(cpu);
}

static void dispatcher2(CPU* cpu)
{
    (*(cpu->table2[0x0]))(cpu);
}

static void dispatcher3(CPU* cpu)
{
    (*(cpu->table3[0x0]))(cpu);
}

static void dispatcher4(CPU* cpu)
{
    (*(cpu->table4[0x0]))(cpu);
}

static void dispatcher5(CPU* cpu)
{
    (*(cpu->table5[0x0]))(cpu);
}

static void dispatcher6(CPU* cpu)
{
    (*(cpu->table6[0x0]))(cpu);
}

static void dispatcher7(CPU* cpu)
{
    (*(cpu->table7[0x0]))(cpu);
}

static void dispatcher8(CPU* cpu)
{
    (*(cpu->table8[cpu->opcode & 0x000Fu]))(cpu);
}

static void dispatcher9(CPU* cpu)
{
    (*(cpu->table9[0x0]))(cpu);
}

static void dispatcherA(CPU* cpu)
{
    (*(cpu->tableA[0x0]))(cpu);
}

static void dispatcherB(CPU* cpu)
{
    (*(cpu->tableB[0x0]))(cpu);
}

static void dispatcherC(CPU* cpu)
{
    (*(cpu->tableC[0x0]))(cpu);
}

static void dispatcherD(CPU* cpu)
{
    (*(cpu->tableD[0x0]))(cpu);
}

static void dispatcherE(CPU* cpu)
{
    (*(cpu->tableE[cpu->opcode & 0x000Fu]))(cpu);
}

static void dispatcherF(CPU* cpu)
{
    (*(cpu->tableF[cpu->opcode & 0x00FFu]))(cpu);
}

static void clearMemory(void* ptr, size_t num)
{
    uint8_t* cptr = ptr;

    for (size_t i = 0; i < num; i++)
    {
        cptr[i] = 0;
    }
}

static void copyMemory(void* dest, const void* src, size_t num)
{
    const uint8_t* csrc = src;
    uint8_t* cdest = dest;

    for (size_t i = 0; i < num; i++)
    {
        cdest[i] = csrc[i];
    }
}

static void initOpcodeTable(OpcodeFunc table[], size_t num)
{
    for (size_t i = 0; i < num; i++)
    {
        table[i] = OP_0nnn;
    }
}

void Chip8_Create(CPU* cpu)
{
    // Initialize registers and memory once
    clearMemory(cpu, sizeof(CPU));
    cpu->pc = START_ADDRESS;

    // Load fontset
    copyMemory(cpu->memory + FONTSET_ADDRESS, fontset, FONT_SIZE);

    // Setup dispatcher function pointers
    cpu->dispatcher[0x0] = dispatcher0;
    cpu->dispatcher[0x1] = dispatcher1;
    cpu->dispatcher[0x2] = dispatcher2;
    cpu->dispatcher[0x3] = dispatcher3;
    cpu->dispatcher[0x4] = dispatcher4;
    cpu->dispatcher[0x5] = dispatcher5;
    cpu->dispatcher[0x6] = dispatcher6;
    cpu->dispatcher[0x7] = dispatcher7;
    cpu->dispatcher[0x8] = dispatcher8;
    cpu->dispatcher[0x9] = dispatcher9;
    cpu->dispatcher[0xA] = dispatcherA;
    cpu->dispatcher[0xB] = dispatcherB;
    cpu->dispatcher[0xC] = dispatcherC;
    cpu->dispatcher[0xD] = dispatcherD;
    cpu->dispatcher[0xE] = dispatcherE;
    cpu->dispatcher[0xF] = dispatcherF;

    // Set opcode table function pointers to OP_0nnn initially
    initOpcodeTable(cpu->table0, sizeof(cpu->table0) / sizeof(cpu->table0[0]));
    initOpcodeTable(cpu->table1, sizeof(cpu->table1) / sizeof(cpu->table1[0]));
    initOpcodeTable(cpu->table2, sizeof(cpu->table2) / sizeof(cpu->table2[0]));
    initOpcodeTable(cpu->table3, sizeof(cpu->table3) / sizeof(cpu->table3[0]));
    initOpcodeTable(cpu->table4, sizeof(cpu->table4) / sizeof(cpu->table4[0]));
    initOpcodeTable(cpu->table5, sizeof(cpu->table5) / sizeof(cpu->table5[0]));
    initOpcodeTable(cpu->table6, sizeof(cpu->table6) / sizeof(cpu->table6[0]));
    initOpcodeTable(cpu->table7, sizeof(cpu->table7) / sizeof(cpu->table7[0]));
    initOpcodeTable(cpu->table8, sizeof(cpu->table8) / sizeof(cpu->table8[0]));
    initOpcodeTable(cpu->table9, sizeof(cpu->table9) / sizeof(cpu->table9[0]));
    initOpcodeTable(cpu->tableA, sizeof(cpu->tableA) / sizeof(cpu->tableA[0]));
    initOpcodeTable(cpu->tableB, sizeof(cpu->tableB) / sizeof(cpu->tableB[0]));
    initOpcodeTable(cpu->tableC, sizeof(cpu->tableC) / sizeof(cpu->tableC[0]));
    initOpcodeTable(cpu->tableD, sizeof(cpu->tableD) / sizeof(cpu->tableD[0]));
    initOpcodeTable(cpu->tableE, sizeof(cpu->tableE) / sizeof(cpu->tableE[0]));
    initOpcodeTable(cpu->tableF, sizeof(cpu->tableF) / sizeof(cpu->tableF[0]));

    // Populate opcode table function pointers with corresponding functions
    cpu->table0[0x0] = OP_00E0;
    cpu->table0[0xE] = OP_00EE;
    cpu->table1[0x0] = OP_1nnn;
    cpu->table2[0x0] = OP_2nnn;
    cpu->table3[0x0] = OP_3xkk;
    cpu->table4[0x0] = OP_4xkk;
    cpu->table5[0x0] = OP_5xy0;
    cpu->table6[0x0] = OP_6xkk;
    cpu->table7[0x0] = OP_7xkk;
    cpu->table8[0x0] = OP_8xy0;
    cpu->table8[0x1] = OP_8xy1;
    cpu->table8[0x2] = OP_8xy2;
    cpu->table8[0x3] = OP_8xy3;
    cpu->table8[0x4] = OP_8xy4;
    cpu->table8[0x5] = OP_8xy5;
    cpu->table8[0x6] = OP_8xy6;
    cpu->table8[0x7] = OP_8xy7;
    cpu->table8[0xE] = OP_8xyE;
    cpu->table9[0x0] = OP_9xy0;
    cpu->tableA[0x0] = OP_Annn;
    cpu->tableB[0x0] = OP_Bnnn;
    cpu->tableC[0x0] = OP_Cxkk;
    cpu->tableD[0x0] = OP_Dxyn;
    cpu->tableE[0xE] = OP_Ex9E;
    cpu->tableE[0x1] = OP_ExA1;
    cpu->tableF[0x07] = OP_Fx07;
    cpu->tableF[0x0A] = OP_Fx0A;
    cpu->tableF[0x15] = OP_Fx15;
    cpu->tableF[0x18] = OP_Fx18;
    cpu->tableF[0x1E] = OP_Fx1E;
    cpu->tableF[0x29] = OP_Fx29;
    cpu->tableF[0x33] = OP_Fx33;
    cpu->tableF[0x55] = OP_Fx55;
    cpu->tableF[0x65] = OP_Fx65;
}

void Chip8_Cycle(CPU* cpu)
{
    // Fetch opcode
    cpu->opcode = (cpu->memory[cpu->pc] << 8u) | cpu->memory[cpu->pc + 1];

    // Increment program counter
    cpu->pc += 2;

    // Decode opcode
    uint8_t nibble = (cpu->opcode & 0xF000u) >> 12u;

    // Execute opcode
    (*(cpu->dispatcher[nibble]))(cpu);

    // Update delay timer if it has been set
    if (cpu->delaytimer > 0) cpu->delaytimer -= 1;

    // Update sound timer if it has been set
    if (cpu->soundtimer > 0) cpu->soundtimer -= 1;
}

void Chip8_Destroy(CPU* cpu)
{
    (void)cpu;
}

void OP_00E0(CPU* cpu) // CLS
{
    clearMemory(cpu->gfx, VIDEO_SIZE);
}

void OP_00EE(CPU* cpu) // RET
{
    cpu->sp -= 1;
    cpu->pc = cpu->stack[cpu->sp];
}

void OP_0nnn(CPU* cpu) // SYS addr
{
    (void)cpu;
}

void OP_1nnn(CPU* cpu) // JMP addr
{
    uint16_t address = cpu->opcode & 0x0FFFu;
    cpu->pc = address;
}

void OP_2nnn(CPU* cpu) // CALL addr
{
    uint16_t address = cpu->opcode & 0x0FFFu;
    cpu->stack[cpu->sp] = cpu->pc;
    cpu->sp += 1;
    cpu->pc = address;
}

void OP_3xkk(CPU* cpu) // SE Vx, byte
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;
    if (cpu->V[x] == byte) cpu->pc += 2;
}

void OP_4xkk(CPU* cpu) // SNE Vx, byte
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;
    if (cpu->V[x] != byte) cpu->pc += 2;
}

void OP_5xy0(CPU* cpu) // SE Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    if (cpu->V[x] == cpu->V[y]) cpu->pc += 2;
}

void OP_6xkk(CPU* cpu) // LD Vx, byte
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;
    cpu->V[x] = byte;
}

void OP_7xkk(CPU* cpu) // ADD Vx, byte
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;
    cpu->V[x] += byte;
}

void OP_8xy0(CPU* cpu) // LD Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    cpu->V[x] = cpu->V[y];
}

void OP_8xy1(CPU* cpu) // OR Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    cpu->V[x] |= cpu->V[y];
}

void OP_8xy2(CPU* cpu) // AND Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    cpu->V[x] &= cpu->V[y];
}

void OP_8xy3(CPU* cpu) // XOR Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    cpu->V[x] ^= cpu->V[y];
}

void OP_8xy4(CPU* cpu) // ADD Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    uint16_t sum = cpu->V[x] + cpu->V[y];
    cpu->V[0xF] = (sum > 255u) ? 1 : 0;
    cpu->V[x] = sum & 0xFFu;
}

void OP_8xy5(CPU* cpu) // SUB Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    cpu->V[0xF] = (cpu->V[x] > cpu->V[y]) ? 1 : 0;
    cpu->V[x] -= cpu->V[y];
}

void OP_8xy6(CPU* cpu) // SHR Vx {, Vy}
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    cpu->V[0xF] = (cpu->V[x] & 0x01u);
    cpu->V[x] >>= 1;
}

void OP_8xy7(CPU* cpu) // SUBN Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    cpu->V[0xF] = (cpu->V[y] > cpu->V[x]) ? 1 : 0;
    cpu->V[x] = cpu->V[y] - cpu->V[x];
}

void OP_8xyE(CPU* cpu) // SHL Vx {, Vy}
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    cpu->V[0xF] = (cpu->V[x] & 0x80u) >> 7u;
    cpu->V[x] <<= 1;
}

void OP_9xy0(CPU* cpu) // SNE Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    if (cpu->V[x] != cpu->V[y]) cpu->pc += 2;
}

void OP_Annn(CPU* cpu) // LD I, addr
{
    uint16_t address = cpu->opcode & 0x0FFFu;
    cpu->I = address;
}

void OP_Bnnn(CPU* cpu) // JP V0, addr
{
    uint16_t address = cpu->opcode & 0x0FFFu;
    cpu->pc = address + cpu->V[0x0];
}

void OP_Cxkk(CPU* cpu) // RND Vx, byte
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;

    // Initial seed
    static uint32_t seed = 0xB16B00B5u;

    // LCG parameters
    static const uint32_t a = 1103515245;
    static const uint32_t c = 12345;
    static const uint32_t m = 2147483648;

    // Generate next pseudo random number
    seed = (seed * a + c) % m;

    cpu->V[x] = seed & byte;
}

void OP_Dxyn(CPU* cpu) // DRW Vx, Vy, nibble
{
    uint8_t Vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (cpu->opcode & 0x00F0u) >> 4u;
    uint8_t height = cpu->opcode & 0x000Fu;

    // Wrap if going beyond screen boundaries
    uint8_t x = cpu->V[Vx] % VIDEO_WIDTH;
    uint8_t y = cpu->V[Vy] % VIDEO_HEIGHT;

    cpu->V[0xF] = 0;

    for (size_t row = 0; row < height; row++)
    {
        uint8_t spriteByte = cpu->memory[cpu->I + row];

        for (size_t col = 0; col < 8; col++)
        {
            uint8_t spritePixel = spriteByte & (0x80u >> col);
            uint32_t screenIndex = (y + row) * VIDEO_WIDTH + (x + col);
            uint32_t* screenPixel = &cpu->gfx[screenIndex];

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

void OP_Ex9E(CPU* cpu) // SKP Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t key = cpu->V[x];
    if (cpu->key[key]) cpu->pc += 2;
}

void OP_ExA1(CPU* cpu) // SKNP Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t key = cpu->V[x];
    if (!cpu->key[key]) cpu->pc += 2;
}

void OP_Fx07(CPU* cpu) // LD Vx, DT
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    cpu->V[x] = cpu->delaytimer;
}

void OP_Fx0A(CPU* cpu) // LD Vx, K
{
    uint8_t Vx = (cpu->opcode & 0x0F00u) >> 8u;

	if (cpu->key[0x0]) cpu->V[Vx] = 0;
	else if (cpu->key[0x1]) cpu->V[Vx] = 0x1;
	else if (cpu->key[0x2]) cpu->V[Vx] = 0x2;
	else if (cpu->key[0x3]) cpu->V[Vx] = 0x3;
	else if (cpu->key[0x4]) cpu->V[Vx] = 0x4;
	else if (cpu->key[0x5]) cpu->V[Vx] = 0x5;
	else if (cpu->key[0x6]) cpu->V[Vx] = 0x6;
	else if (cpu->key[0x7]) cpu->V[Vx] = 0x7;
	else if (cpu->key[0x8]) cpu->V[Vx] = 0x8;
	else if (cpu->key[0x9]) cpu->V[Vx] = 0x9;
	else if (cpu->key[0xA]) cpu->V[Vx] = 0xA;
	else if (cpu->key[0xB]) cpu->V[Vx] = 0xB;
	else if (cpu->key[0xC]) cpu->V[Vx] = 0xC;
	else if (cpu->key[0xD]) cpu->V[Vx] = 0xD;
	else if (cpu->key[0xE]) cpu->V[Vx] = 0xE;
	else if (cpu->key[0xF]) cpu->V[Vx] = 0xF;
	else cpu->pc -= 2;
}

void OP_Fx15(CPU* cpu) // LD DT, Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    cpu->delaytimer = cpu->V[x];
}

void OP_Fx18(CPU* cpu) // LD ST, Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    cpu->soundtimer = cpu->V[x];
}

void OP_Fx1E(CPU* cpu) // ADD I, Vx
{
}

void OP_Fx29(CPU* cpu) // LD F, Vx
{
}

void OP_Fx33(CPU* cpu) // LD B, Vx
{
}

void OP_Fx55(CPU* cpu) // LD [I], Vx
{
}

void OP_Fx65(CPU* cpu) // LD Vx, [I]
{
}
