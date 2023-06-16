#include "chip8/chip8.h"

static void dispatcher0X(Chip8_Cpu* cpu);
static void dispatcher1X(Chip8_Cpu* cpu);
static void dispatcher2X(Chip8_Cpu* cpu);
static void dispatcher3X(Chip8_Cpu* cpu);
static void dispatcher4X(Chip8_Cpu* cpu);
static void dispatcher5X(Chip8_Cpu* cpu);
static void dispatcher6X(Chip8_Cpu* cpu);
static void dispatcher7X(Chip8_Cpu* cpu);
static void dispatcher8X(Chip8_Cpu* cpu);
static void dispatcher9X(Chip8_Cpu* cpu);
static void dispatcherAX(Chip8_Cpu* cpu);
static void dispatcherBX(Chip8_Cpu* cpu);
static void dispatcherCX(Chip8_Cpu* cpu);
static void dispatcherDX(Chip8_Cpu* cpu);
static void dispatcherEX(Chip8_Cpu* cpu);
static void dispatcherFX(Chip8_Cpu* cpu);

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

void Chip8_Create(Chip8_Cpu* cpu, Chip8_Config config)
{
    const uint8_t fontset[FONT_SIZE] = {
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

    clearMemory(cpu, sizeof(Chip8_Cpu));
    cpu->config = config;
    cpu->pc = START_ADDRESS;

    copyMemory(cpu->memory + FONTSET_ADDRESS, fontset, FONT_SIZE);

    cpu->dispatcher.table0X[0x0] = OP_00E0;
    cpu->dispatcher.table0X[0xE] = OP_00EE;
    cpu->dispatcher.table1X[0x0] = OP_1nnn;
    cpu->dispatcher.table2X[0x0] = OP_2nnn;
    cpu->dispatcher.table3X[0x0] = OP_3xkk;
    cpu->dispatcher.table4X[0x0] = OP_4xkk;
    cpu->dispatcher.table5X[0x0] = OP_5xy0;
    cpu->dispatcher.table6X[0x0] = OP_6xkk;
    cpu->dispatcher.table7X[0x0] = OP_7xkk;
    cpu->dispatcher.table8X[0x0] = OP_8xy0;
    cpu->dispatcher.table8X[0x1] = OP_8xy1;
    cpu->dispatcher.table8X[0x2] = OP_8xy2;
    cpu->dispatcher.table8X[0x3] = OP_8xy3;
    cpu->dispatcher.table8X[0x4] = OP_8xy4;
    cpu->dispatcher.table8X[0x5] = OP_8xy5;
    cpu->dispatcher.table8X[0x6] = OP_8xy6;
    cpu->dispatcher.table8X[0x7] = OP_8xy7;
    cpu->dispatcher.table8X[0xE] = OP_8xyE;
    cpu->dispatcher.table9X[0x0] = OP_9xy0;
    cpu->dispatcher.tableAX[0x0] = OP_Annn;
    cpu->dispatcher.tableBX[0x0] = OP_Bnnn;
    cpu->dispatcher.tableCX[0x0] = OP_Cxkk;
    cpu->dispatcher.tableDX[0x0] = OP_Dxyn;
    cpu->dispatcher.tableEX[0xE] = OP_Ex9E;
    cpu->dispatcher.tableEX[0x1] = OP_ExA1;
    cpu->dispatcher.tableFX[0x07] = OP_Fx07;
    cpu->dispatcher.tableFX[0x0A] = OP_Fx0A;
    cpu->dispatcher.tableFX[0x15] = OP_Fx15;
    cpu->dispatcher.tableFX[0x18] = OP_Fx18;
    cpu->dispatcher.tableFX[0x1E] = OP_Fx1E;
    cpu->dispatcher.tableFX[0x29] = OP_Fx29;
    cpu->dispatcher.tableFX[0x33] = OP_Fx33;
    cpu->dispatcher.tableFX[0x55] = OP_Fx55;
    cpu->dispatcher.tableFX[0x65] = OP_Fx65;

    cpu->dispatcher.table[0x0] = dispatcher0X;
    cpu->dispatcher.table[0x1] = dispatcher1X;
    cpu->dispatcher.table[0x2] = dispatcher2X;
    cpu->dispatcher.table[0x3] = dispatcher3X;
    cpu->dispatcher.table[0x4] = dispatcher4X;
    cpu->dispatcher.table[0x5] = dispatcher5X;
    cpu->dispatcher.table[0x6] = dispatcher6X;
    cpu->dispatcher.table[0x7] = dispatcher7X;
    cpu->dispatcher.table[0x8] = dispatcher8X;
    cpu->dispatcher.table[0x9] = dispatcher9X;
    cpu->dispatcher.table[0xA] = dispatcherAX;
    cpu->dispatcher.table[0xB] = dispatcherBX;
    cpu->dispatcher.table[0xC] = dispatcherCX;
    cpu->dispatcher.table[0xD] = dispatcherDX;
    cpu->dispatcher.table[0xE] = dispatcherEX;
    cpu->dispatcher.table[0xF] = dispatcherFX;
}

void Chip8_Cycle(Chip8_Cpu* cpu, const uint32_t time)
{    
    uint16_t opcode = (cpu->memory[cpu->pc] << 8u) | cpu->memory[cpu->pc + 1];

    cpu->opcode = (Chip8_Opcode) {
        .inst = opcode,
        .x = (opcode & 0x0F00u) >> 8u,
        .y = (opcode & 0x00F0u) >> 4u,
        .n = opcode & 0x000Fu,
        .nn = opcode & 0x00FFu,
        .nnn = opcode & 0x0FFFu
    };
    
    cpu->pc += 2;
    cpu->draw = 0;

    uint8_t instruction = (cpu->opcode.inst & 0xF000u) >> 12u;
    OpcodeFunc operation = cpu->dispatcher.table[instruction];

    if (operation)
    {
        operation(cpu);
    }
    else
    {
        // Handle unknown opcode
    }

    static uint32_t lastTick = 0;
    if (time - lastTick >= 1000.0 / CLOCK_HZ + 0.5)
    {
        if (cpu->delaytimer > 0)
        {
            cpu->delaytimer -= 1;
        }
        if (cpu->soundtimer > 0)
        {
            cpu->soundtimer -= 1;
        }

        lastTick = time;
        cpu->vbi = 1;
    }
}

void Chip8_Destroy(Chip8_Cpu* cpu)
{
    (void)cpu;
}

void OP_00E0(Chip8_Cpu* cpu) // CLS
{
    clearMemory(cpu->gfx, sizeof(cpu->gfx));
}

void OP_00EE(Chip8_Cpu* cpu) // RET
{
    cpu->sp -= 1;
    cpu->pc = cpu->stack[cpu->sp];
}

void OP_0nnn(Chip8_Cpu* cpu) // SYS addr
{
    (void)cpu;
}

void OP_1nnn(Chip8_Cpu* cpu) // JMP addr
{
    cpu->pc = cpu->opcode.nnn;
}

void OP_2nnn(Chip8_Cpu* cpu) // CALL addr
{
    cpu->stack[cpu->sp] = cpu->pc;
    cpu->sp += 1;
    cpu->pc = cpu->opcode.nnn;
}

void OP_3xkk(Chip8_Cpu* cpu) // SE Vx, byte
{
    if (cpu->v[cpu->opcode.x] == cpu->opcode.nn)
    {
        cpu->pc += 2;
    }
}

void OP_4xkk(Chip8_Cpu* cpu) // SNE Vx, byte
{
    if (cpu->v[cpu->opcode.x] != cpu->opcode.nn)
    {
        cpu->pc += 2;
    }
}

void OP_5xy0(Chip8_Cpu* cpu) // SE Vx, Vy
{
    if (cpu->v[cpu->opcode.x] == cpu->v[cpu->opcode.y])
    {
        cpu->pc += 2;
    }
}

void OP_6xkk(Chip8_Cpu* cpu) // LD Vx, byte
{
    cpu->v[cpu->opcode.x] = cpu->opcode.nn;
}

void OP_7xkk(Chip8_Cpu* cpu) // ADD Vx, byte
{
    cpu->v[cpu->opcode.x] += cpu->opcode.nn;
}

void OP_8xy0(Chip8_Cpu* cpu) // LD Vx, Vy
{
    cpu->v[cpu->opcode.x] = cpu->v[cpu->opcode.y];
}

void OP_8xy1(Chip8_Cpu* cpu) // OR Vx, Vy
{
    cpu->v[cpu->opcode.x] |= cpu->v[cpu->opcode.y];

    if (cpu->config.reset)
    {
        cpu->v[0xF] = 0x00u;
    }
}

void OP_8xy2(Chip8_Cpu* cpu) // AND Vx, Vy
{
    cpu->v[cpu->opcode.x] &= cpu->v[cpu->opcode.y];
    
    if (cpu->config.reset)
    {
        cpu->v[0xF] = 0x00u;
    }
}

void OP_8xy3(Chip8_Cpu* cpu) // XOR Vx, Vy
{
    cpu->v[cpu->opcode.x] ^= cpu->v[cpu->opcode.y];
    
    if (cpu->config.reset)
    {
        cpu->v[0xF] = 0x00u;
    }
}

void OP_8xy4(Chip8_Cpu* cpu) // ADD Vx, Vy
{
    uint16_t ans = cpu->v[cpu->opcode.x] + cpu->v[cpu->opcode.y];

    cpu->v[cpu->opcode.x] = ans & 0xFFu;

    if (ans > 255u)
    {
        cpu->v[0xF] = 0x01u;
    }
    else
    {
        cpu->v[0xF] = 0x00u;
    }
}

void OP_8xy5(Chip8_Cpu* cpu) // SUB Vx, Vy
{
    uint8_t tx = cpu->v[cpu->opcode.x];

    cpu->v[cpu->opcode.x] -= cpu->v[cpu->opcode.y];

    if (tx >= cpu->v[cpu->opcode.y])
    {
        cpu->v[0xF] = 0x01u;
    }
    else
    {
        cpu->v[0xF] = 0x00u;
    }
}

void OP_8xy6(Chip8_Cpu* cpu) // SHR Vx {, Vy}
{
    uint8_t tx = cpu->v[cpu->opcode.x];

    if (!cpu->config.shifting)
    {
        cpu->v[cpu->opcode.x] = cpu->v[cpu->opcode.y];
    }

    cpu->v[cpu->opcode.x] >>= 1u;
    cpu->v[0xF] = (tx & 0x01u);
}

void OP_8xy7(Chip8_Cpu* cpu) // SUBN Vx, Vy
{
    cpu->v[cpu->opcode.x] = cpu->v[cpu->opcode.y] - cpu->v[cpu->opcode.x];

    if (cpu->v[cpu->opcode.y] > cpu->v[cpu->opcode.x])
    {
        cpu->v[0xF] = 0x01u;
    }
    else
    {
        cpu->v[0xF] = 0x00u;
    }
}

void OP_8xyE(Chip8_Cpu* cpu) // SHL Vx {, Vy}
{
    uint8_t tx = cpu->v[cpu->opcode.x];

    if (!cpu->config.shifting)
    {
        cpu->v[cpu->opcode.x] = cpu->v[cpu->opcode.y];
    }

    cpu->v[cpu->opcode.x] <<= 1u;
    cpu->v[0xF] = (tx & 0x80u) >> 7u;
}

void OP_9xy0(Chip8_Cpu* cpu) // SNE Vx, Vy
{
    if (cpu->v[cpu->opcode.x] != cpu->v[cpu->opcode.y])
    {
        cpu->pc += 2;
    }
}

void OP_Annn(Chip8_Cpu* cpu) // LD I, addr
{
    cpu->i = cpu->opcode.nnn;
}

void OP_Bnnn(Chip8_Cpu* cpu) // JP V0, addr
{
    if (cpu->config.jumping)
    {
        cpu->pc = cpu->opcode.nnn + cpu->v[(cpu->opcode.inst & 0x0F00) >> 8u];
    }
    else
    {
        cpu->pc = cpu->opcode.nnn + cpu->v[0x0];
    }
}

void OP_Cxkk(Chip8_Cpu* cpu) // RND Vx, byte
{
    static uint32_t seed = 0xB16B00B5u;

    static const uint32_t a = 1103515245;
    static const uint32_t c = 12345;
    static const uint32_t m = 2147483648;

    seed = (seed * a + c) % m;

    cpu->v[cpu->opcode.x] = seed & cpu->opcode.nn;
}

void OP_Dxyn(Chip8_Cpu* cpu) // DRW Vx, Vy, nibble
{
    if (cpu->config.display)
    {
        if (cpu->vbi == 0)
        {
            cpu->pc -= 2;
            return;
        }
    }
    
    uint8_t tx = cpu->v[cpu->opcode.x] & (VIDEO_WIDTH - 1);
    uint8_t ty = cpu->v[cpu->opcode.y] & (VIDEO_HEIGHT - 1);

    cpu->v[0xF] = 0;

    for (size_t row = 0; row < cpu->opcode.n; row++)
    {
        for (size_t col = 0; col < 8; col++)
        {
            if (cpu->config.clipping)
            {
                if (tx + col > VIDEO_WIDTH - 1 || ty + row > VIDEO_HEIGHT - 1)
                {
                    break;
                }
            }

            uint8_t pixel = (cpu->memory[cpu->i + row] & (0x80u >> col)) != 0;

            if (pixel)
            {
                uint8_t x = (tx + col) & (VIDEO_WIDTH - 1);
                uint8_t y = (ty + row) & (VIDEO_HEIGHT - 1);
                uint16_t index = y * VIDEO_WIDTH + x;
                
                uint8_t bit = 0x01u << (index & 0x07u);

                index >>= 3u;

                if (cpu->gfx[index] & bit)
                {
                    cpu->v[0xF] = 1;
                }

                cpu->gfx[index] ^= bit;
            }
        }
    }

    cpu->vbi = 0;
    cpu->draw = 1;
}

void OP_Ex9E(Chip8_Cpu* cpu) // SKP Vx
{
    if (cpu->key & (0x0001u << cpu->v[cpu->opcode.x])) 
    {
        cpu->pc += 2;
    }
}

void OP_ExA1(Chip8_Cpu* cpu) // SKNP Vx
{
    if (!(cpu->key & (0x0001u << cpu->v[cpu->opcode.x])))
    {
        cpu->pc += 2;
    }
}

void OP_Fx07(Chip8_Cpu* cpu) // LD Vx, DT
{
    cpu->v[cpu->opcode.x] = cpu->delaytimer;
}

void OP_Fx0A(Chip8_Cpu* cpu) // LD Vx, K
{
    if (!cpu->key) 
    {
        cpu->pc -= 2;
        return;
    }

    for (size_t i = 0; i < KEY_COUNT - 1; i++) 
    {
        if (cpu->key & (0x0001u << i)) 
        {
            cpu->v[cpu->opcode.x] = i;
            break;
        }
    }

    cpu->key = 0;
}

void OP_Fx15(Chip8_Cpu* cpu) // LD DT, Vx
{
    cpu->delaytimer = cpu->v[cpu->opcode.x];
}

void OP_Fx18(Chip8_Cpu* cpu) // LD ST, Vx
{
    cpu->soundtimer = cpu->v[cpu->opcode.x];
}

void OP_Fx1E(Chip8_Cpu* cpu) // ADD I, Vx
{
    cpu->i += cpu->v[cpu->opcode.x];
}

void OP_Fx29(Chip8_Cpu* cpu) // LD F, Vx
{
    cpu->i = FONTSET_ADDRESS + (5 * cpu->opcode.x);
}

void OP_Fx33(Chip8_Cpu* cpu) // LD B, Vx
{
    uint8_t tx = cpu->v[cpu->opcode.x];

    cpu->memory[cpu->i + 2] = tx % 10;
    tx /= 10;

    cpu->memory[cpu->i + 1] = tx % 10;
    tx /= 10;

    cpu->memory[cpu->i] = tx % 10;
}

void OP_Fx55(Chip8_Cpu* cpu) // LD [I], Vx
{
    size_t i;
    for (i = 0; i <= cpu->opcode.x; i++)
    {
        cpu->memory[cpu->i + i] = cpu->v[i];
    }

    if (cpu->config.memory)
    {
        cpu->i += i;
    }
}

void OP_Fx65(Chip8_Cpu* cpu) // LD Vx, [I]
{
    size_t i;
    for (i = 0; i <= cpu->opcode.x; i++)
    {
        cpu->v[i] = cpu->memory[cpu->i + i];
    }

    if (cpu->config.memory)
    {
        cpu->i += i;
    }
}

static void dispatcher0X(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.table0X[cpu->opcode.inst & 0x000Fu]))(cpu);
}

static void dispatcher1X(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.table1X[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcher2X(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.table2X[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcher3X(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.table3X[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcher4X(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.table4X[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcher5X(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.table5X[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcher6X(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.table6X[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcher7X(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.table7X[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcher8X(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.table8X[cpu->opcode.inst & 0x000Fu]))(cpu);
}

static void dispatcher9X(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.table9X[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcherAX(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.tableAX[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcherBX(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.tableBX[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcherCX(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.tableCX[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcherDX(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.tableDX[cpu->opcode.inst & 0x0000u]))(cpu);
}

static void dispatcherEX(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.tableEX[cpu->opcode.inst & 0x000Fu]))(cpu);
}

static void dispatcherFX(Chip8_Cpu* cpu)
{
    (*(cpu->dispatcher.tableFX[cpu->opcode.inst & 0x00FFu]))(cpu);
}
