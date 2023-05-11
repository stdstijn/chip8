#include "chip8/chip8.h"

static void dispatcher0X(CPU* cpu);
static void dispatcher1X(CPU* cpu);
static void dispatcher2X(CPU* cpu);
static void dispatcher3X(CPU* cpu);
static void dispatcher4X(CPU* cpu);
static void dispatcher5X(CPU* cpu);
static void dispatcher6X(CPU* cpu);
static void dispatcher7X(CPU* cpu);
static void dispatcher8X(CPU* cpu);
static void dispatcher9X(CPU* cpu);
static void dispatcherAX(CPU* cpu);
static void dispatcherBX(CPU* cpu);
static void dispatcherCX(CPU* cpu);
static void dispatcherDX(CPU* cpu);
static void dispatcherEX(CPU* cpu);
static void dispatcherFX(CPU* cpu);

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

static void clearMemory(void* ptr, size_t len)
{
    uint8_t* cptr = ptr;

    for (size_t i = 0; i < len; i++)
    {
        cptr[i] = 0;
    }
}

static void copyMemory(void* dest, const void* src, size_t len)
{
    const uint8_t* csrc = src;
    uint8_t* cdest = dest;

    for (size_t i = 0; i < len; i++)
    {
        cdest[i] = csrc[i];
    }
}

void Chip8_Create(CPU* cpu)
{
    clearMemory(cpu, sizeof(CPU));
    cpu->pc = START_ADDRESS;

    copyMemory(cpu->memory + FONTSET_ADDRESS, fontset, FONT_SIZE);

    cpu->table0X[0x0] = OP_00E0;
    cpu->table0X[0xE] = OP_00EE;
    cpu->table1X[0x0] = OP_1nnn;
    cpu->table2X[0x0] = OP_2nnn;
    cpu->table3X[0x0] = OP_3xkk;
    cpu->table4X[0x0] = OP_4xkk;
    cpu->table5X[0x0] = OP_5xy0;
    cpu->table6X[0x0] = OP_6xkk;
    cpu->table7X[0x0] = OP_7xkk;
    cpu->table8X[0x0] = OP_8xy0;
    cpu->table8X[0x1] = OP_8xy1;
    cpu->table8X[0x2] = OP_8xy2;
    cpu->table8X[0x3] = OP_8xy3;
    cpu->table8X[0x4] = OP_8xy4;
    cpu->table8X[0x5] = OP_8xy5;
    cpu->table8X[0x6] = OP_8xy6;
    cpu->table8X[0x7] = OP_8xy7;
    cpu->table8X[0xE] = OP_8xyE;
    cpu->table9X[0x0] = OP_9xy0;
    cpu->tableAX[0x0] = OP_Annn;
    cpu->tableBX[0x0] = OP_Bnnn;
    cpu->tableCX[0x0] = OP_Cxkk;
    cpu->tableDX[0x0] = OP_Dxyn;
    cpu->tableEX[0xE] = OP_Ex9E;
    cpu->tableEX[0x1] = OP_ExA1;
    cpu->tableFX[0x07] = OP_Fx07;
    cpu->tableFX[0x0A] = OP_Fx0A;
    cpu->tableFX[0x15] = OP_Fx15;
    cpu->tableFX[0x18] = OP_Fx18;
    cpu->tableFX[0x1E] = OP_Fx1E;
    cpu->tableFX[0x29] = OP_Fx29;
    cpu->tableFX[0x33] = OP_Fx33;
    cpu->tableFX[0x55] = OP_Fx55;
    cpu->tableFX[0x65] = OP_Fx65;

    cpu->dispatcher[0x0] = dispatcher0X;
    cpu->dispatcher[0x1] = dispatcher1X;
    cpu->dispatcher[0x2] = dispatcher2X;
    cpu->dispatcher[0x3] = dispatcher3X;
    cpu->dispatcher[0x4] = dispatcher4X;
    cpu->dispatcher[0x5] = dispatcher5X;
    cpu->dispatcher[0x6] = dispatcher6X;
    cpu->dispatcher[0x7] = dispatcher7X;
    cpu->dispatcher[0x8] = dispatcher8X;
    cpu->dispatcher[0x9] = dispatcher9X;
    cpu->dispatcher[0xA] = dispatcherAX;
    cpu->dispatcher[0xB] = dispatcherBX;
    cpu->dispatcher[0xC] = dispatcherCX;
    cpu->dispatcher[0xD] = dispatcherDX;
    cpu->dispatcher[0xE] = dispatcherEX;
    cpu->dispatcher[0xF] = dispatcherFX;

}

void Chip8_Cycle(CPU* cpu, const uint32_t time)
{
    cpu->opcode = (cpu->memory[cpu->pc] << 8u) | cpu->memory[cpu->pc + 1];

    cpu->pc += 2;

    uint8_t nibble = (cpu->opcode & 0xF000u) >> 12u;
    OpcodeFunc func = cpu->dispatcher[nibble];

    if (func)
    {
        func(cpu);
    }
    else
    {
        // Handle unknown opcode
    }

    static uint32_t lastTimerUpdate = 0;

    if (time - lastTimerUpdate >= 1000.0 / CLOCK_HZ + 0.5)
    {
        if (cpu->delaytimer > 0)
        {
            cpu->delaytimer -= 1;
        }
        if (cpu->soundtimer > 0)
        {
            cpu->soundtimer -= 1;
        }

        lastTimerUpdate = time;
    }
}

void Chip8_Destroy(CPU* cpu)
{
    (void)cpu;
}

void OP_00E0(CPU* cpu) // CLS
{
    clearMemory(cpu->gfx, sizeof(cpu->gfx));
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
    uint16_t addr = cpu->opcode & 0x0FFFu;

    cpu->pc = addr;
}

void OP_2nnn(CPU* cpu) // CALL addr
{
    uint16_t addr = cpu->opcode & 0x0FFFu;

    cpu->stack[cpu->sp] = cpu->pc;
    cpu->sp += 1;
    cpu->pc = addr;
}

void OP_3xkk(CPU* cpu) // SE Vx, byte
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;

    if (cpu->v[x] == byte) cpu->pc += 2;
}

void OP_4xkk(CPU* cpu) // SNE Vx, byte
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;

    if (cpu->v[x] != byte) cpu->pc += 2;
}

void OP_5xy0(CPU* cpu) // SE Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;

    if (cpu->v[x] == cpu->v[y]) cpu->pc += 2;
}

void OP_6xkk(CPU* cpu) // LD Vx, byte
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;

    cpu->v[x] = byte;
}

void OP_7xkk(CPU* cpu) // ADD Vx, byte
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;

    cpu->v[x] += byte;
}

void OP_8xy0(CPU* cpu) // LD Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->v[x] = cpu->v[y];
}

void OP_8xy1(CPU* cpu) // OR Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->v[x] |= cpu->v[y];
}

void OP_8xy2(CPU* cpu) // AND Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->v[x] &= cpu->v[y];
}

void OP_8xy3(CPU* cpu) // XOR Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->v[x] ^= cpu->v[y];
}

void OP_8xy4(CPU* cpu) // ADD Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    uint16_t ans = cpu->v[x] + cpu->v[y];

    cpu->v[x] = ans & 0xFFu;
    cpu->v[0xF] = (ans > 255u) ? 1 : 0;
}

void OP_8xy5(CPU* cpu) // SUB Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    uint8_t vx = cpu->v[x];

    cpu->v[x] -= cpu->v[y];
    cpu->v[0xF] = (vx >= cpu->v[y]) ? 1 : 0;
}

void OP_8xy6(CPU* cpu) // SHR Vx {, Vy}
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vx = cpu->v[x];

    cpu->v[x] >>= 1;
    cpu->v[0xF] = (vx & 0x01u);
}

void OP_8xy7(CPU* cpu) // SUBN Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->v[x] = cpu->v[y] - cpu->v[x];
    cpu->v[0xF] = (cpu->v[y] > cpu->v[x]) ? 1 : 0;
}

void OP_8xyE(CPU* cpu) // SHL Vx {, Vy}
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vx = cpu->v[x];

    cpu->v[x] <<= 1;
    cpu->v[0xF] = (vx & 0x80u) >> 7u;
}

void OP_9xy0(CPU* cpu) // SNE Vx, Vy
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;

    if (cpu->v[x] != cpu->v[y]) cpu->pc += 2;
}

void OP_Annn(CPU* cpu) // LD I, addr
{
    uint16_t addr = cpu->opcode & 0x0FFFu;

    cpu->i = addr;
}

void OP_Bnnn(CPU* cpu) // JP V0, addr
{
    uint16_t addr = cpu->opcode & 0x0FFFu;

    cpu->pc = addr + cpu->v[0x0];
}

void OP_Cxkk(CPU* cpu) // RND Vx, byte
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t byte = cpu->opcode & 0x00FFu;

    static uint32_t seed = 0xB16B00B5u;

    static const uint32_t a = 1103515245;
    static const uint32_t c = 12345;
    static const uint32_t m = 2147483648;

    seed = (seed * a + c) % m;

    cpu->v[x] = seed & byte;
}

void OP_Dxyn(CPU* cpu) // DRW Vx, Vy, nibble
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t y = (cpu->opcode & 0x00F0u) >> 4u;
    uint8_t nibble = cpu->opcode & 0x000Fu;

    uint8_t vx = cpu->v[x];
    uint8_t vy = cpu->v[y];

    cpu->v[0xF] = 0;

    for (size_t row = 0; row < nibble; row++)
    {
        for (size_t col = 0; col < 8; col++)
        {
            uint8_t pixel = (cpu->memory[cpu->i + row] & (0x80u >> col)) != 0;

            if (pixel)
            {
                uint16_t tx = (vx + col) & (VIDEO_WIDTH - 1);
                uint16_t ty = (vy + row) & (VIDEO_HEIGHT - 1);
                uint16_t byte = ty * VIDEO_WIDTH + tx;

                uint8_t bit = 1 << (byte & 0x07u);

                byte >>= 3;

                if (cpu->gfx[byte] & bit)
                {
                    cpu->v[0xF] = 1;
                }

                cpu->gfx[byte] ^= bit;
            }
        }
    }
}

void OP_Ex9E(CPU* cpu) // SKP Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vx = cpu->v[x];

    if (cpu->key[vx]) cpu->pc += 2;
}

void OP_ExA1(CPU* cpu) // SKNP Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t key = cpu->v[x];

    if (!cpu->key[key]) cpu->pc += 2;
}

void OP_Fx07(CPU* cpu) // LD Vx, DT
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;

    cpu->v[x] = cpu->delaytimer;
}

void OP_Fx0A(CPU* cpu) // LD Vx, K
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;

    static uint8_t keyPressed[0xF];

    if (cpu->key[0x0] && keyPressed[0x0]) cpu->v[x] = 0;
    else if (!cpu->key[0x1] && keyPressed[0x1]) cpu->v[x] = 0x1;
    else if (!cpu->key[0x2] && keyPressed[0x2]) cpu->v[x] = 0x2;
    else if (!cpu->key[0x3] && keyPressed[0x3]) cpu->v[x] = 0x3;
    else if (!cpu->key[0x4] && keyPressed[0x4]) cpu->v[x] = 0x4;
    else if (!cpu->key[0x5] && keyPressed[0x5]) cpu->v[x] = 0x5;
    else if (!cpu->key[0x6] && keyPressed[0x6]) cpu->v[x] = 0x6;
    else if (!cpu->key[0x7] && keyPressed[0x7]) cpu->v[x] = 0x7;
    else if (!cpu->key[0x8] && keyPressed[0x8]) cpu->v[x] = 0x8;
    else if (!cpu->key[0x9] && keyPressed[0x9]) cpu->v[x] = 0x9;
    else if (!cpu->key[0xA] && keyPressed[0xA]) cpu->v[x] = 0xA;
    else if (!cpu->key[0xB] && keyPressed[0xB]) cpu->v[x] = 0xB;
    else if (!cpu->key[0xC] && keyPressed[0xC]) cpu->v[x] = 0xC;
    else if (!cpu->key[0xD] && keyPressed[0xD]) cpu->v[x] = 0xD;
    else if (!cpu->key[0xE] && keyPressed[0xE]) cpu->v[x] = 0xE;
    else if (!cpu->key[0xF] && keyPressed[0xF]) cpu->v[x] = 0xF;
    else cpu->pc -= 2;

    copyMemory(keyPressed, cpu->key, sizeof(cpu->key));
}

void OP_Fx15(CPU* cpu) // LD DT, Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;

    cpu->delaytimer = cpu->v[x];
}

void OP_Fx18(CPU* cpu) // LD ST, Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;

    cpu->soundtimer = cpu->v[x];
}

void OP_Fx1E(CPU* cpu) // ADD I, Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;

    cpu->i += cpu->v[x];
}

void OP_Fx29(CPU* cpu) // LD F, Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vx = cpu->v[x];

    cpu->i = FONTSET_ADDRESS + (5 * vx);
}

void OP_Fx33(CPU* cpu) // LD B, Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vx = cpu->v[x];

    cpu->memory[cpu->i + 2] = vx % 10;
    vx /= 10;

    cpu->memory[cpu->i + 1] = vx % 10;
    vx /= 10;

    cpu->memory[cpu->i] = vx % 10;
}

void OP_Fx55(CPU* cpu) // LD [I], Vx
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;

    for (size_t i = 0; i <= x; i++)
    {
        cpu->memory[cpu->i + i] = cpu->v[i];
    }
}

void OP_Fx65(CPU* cpu) // LD Vx, [I]
{
    uint8_t x = (cpu->opcode & 0x0F00u) >> 8u;

    for (size_t i = 0; i <= x; i++)
    {
        cpu->v[i] = cpu->memory[cpu->i + i];
    }
}

static void dispatcher0X(CPU* cpu)
{
    (*(cpu->table0X[cpu->opcode & 0x000Fu]))(cpu);
}

static void dispatcher1X(CPU* cpu)
{
    (*(cpu->table1X[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcher2X(CPU* cpu)
{
    (*(cpu->table2X[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcher3X(CPU* cpu)
{
    (*(cpu->table3X[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcher4X(CPU* cpu)
{
    (*(cpu->table4X[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcher5X(CPU* cpu)
{
    (*(cpu->table5X[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcher6X(CPU* cpu)
{
    (*(cpu->table6X[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcher7X(CPU* cpu)
{
    (*(cpu->table7X[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcher8X(CPU* cpu)
{
    (*(cpu->table8X[cpu->opcode & 0x000Fu]))(cpu);
}

static void dispatcher9X(CPU* cpu)
{
    (*(cpu->table9X[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcherAX(CPU* cpu)
{
    (*(cpu->tableAX[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcherBX(CPU* cpu)
{
    (*(cpu->tableBX[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcherCX(CPU* cpu)
{
    (*(cpu->tableCX[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcherDX(CPU* cpu)
{
    (*(cpu->tableDX[cpu->opcode & 0x0000u]))(cpu);
}

static void dispatcherEX(CPU* cpu)
{
    (*(cpu->tableEX[cpu->opcode & 0x000Fu]))(cpu);
}

static void dispatcherFX(CPU* cpu)
{
    (*(cpu->tableFX[cpu->opcode & 0x00FFu]))(cpu);
}
