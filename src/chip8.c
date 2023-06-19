#include "chip8/chip8.h"
#include "chip8/dispatcher.h"

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

void Chip8_Create(Chip8_Cpu* cpu, Chip8_Config* config)
{
    clearMemory(cpu, sizeof(Chip8_Cpu));
    cpu->pc = START_ADDRESS;

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

    copyMemory(cpu->memory + FONTSET_ADDRESS, fontset, FONT_SIZE);

    if (config)
    {
        cpu->config = *config;
    }
    else
    {
        cpu->config.flagReset = 1;
        cpu->config.indexIncrement = 1;
        cpu->config.displayWait = 1;
        cpu->config.spriteClipping = 1;
        cpu->config.shiftInPlace = 0;
        cpu->config.jumpValue = 0;
    }
}

Chip8_CycleCodes Chip8_Cycle(Chip8_Cpu* cpu, const uint32_t time)
{
    Chip8_CycleCodes cycleCode = CYCLE_OK;

    cpu->opcode.inst = (cpu->memory[cpu->pc] << 8u) | cpu->memory[cpu->pc + 1];
    cpu->pc += 2;

    cpu->opcode.x = (cpu->opcode.inst & 0x0F00u) >> 8u;
    cpu->opcode.y = (cpu->opcode.inst & 0x00F0u) >> 4u;
    cpu->opcode.n = cpu->opcode.inst & 0x000Fu;
    cpu->opcode.nn = cpu->opcode.inst & 0x00FFu;
    cpu->opcode.nnn = cpu->opcode.inst & 0x0FFF;
    
    cpu->draw = 0;

    Chip8_DispatchCodes dispatchCode = Chip8_DispatchOpcode(cpu);

    if (dispatchCode == DISPATCH_OPCODE_FAIL)
    {
        cycleCode = CYCLE_NOT_IMPLEMENTED;
    }

    static uint32_t lastTick = 0;

    if (time - lastTick >= 1000.0 / CLOCK_HZ)
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

    return cycleCode;
}

void Chip8_Destroy(Chip8_Cpu* cpu)
{
    (void)cpu;
}

void Chip8_Op00E0(Chip8_Cpu* cpu) // CLS
{
    clearMemory(cpu->gfx, sizeof(cpu->gfx));
}

void Chip8_Op00EE(Chip8_Cpu* cpu) // RET
{
    cpu->sp -= 1;
    cpu->pc = cpu->stack[cpu->sp];
}

void Chip8_Op0nnn(Chip8_Cpu* cpu) // SYS addr
{
    (void)cpu;
}

void Chip8_Op1nnn(Chip8_Cpu* cpu) // JMP addr
{
    cpu->pc = cpu->opcode.nnn;
}

void Chip8_Op2nnn(Chip8_Cpu* cpu) // CALL addr
{
    cpu->stack[cpu->sp] = cpu->pc;
    cpu->sp += 1;
    cpu->pc = cpu->opcode.nnn;
}

void Chip8_Op3xkk(Chip8_Cpu* cpu) // SE Vx, byte
{
    if (cpu->v[cpu->opcode.x] == cpu->opcode.nn)
    {
        cpu->pc += 2;
    }
}

void Chip8_Op4xkk(Chip8_Cpu* cpu) // SNE Vx, byte
{
    if (cpu->v[cpu->opcode.x] != cpu->opcode.nn)
    {
        cpu->pc += 2;
    }
}

void Chip8_Op5xy0(Chip8_Cpu* cpu) // SE Vx, Vy
{
    if (cpu->v[cpu->opcode.x] == cpu->v[cpu->opcode.y])
    {
        cpu->pc += 2;
    }
}

void Chip8_Op6xkk(Chip8_Cpu* cpu) // LD Vx, byte
{
    cpu->v[cpu->opcode.x] = cpu->opcode.nn;
}

void Chip8_Op7xkk(Chip8_Cpu* cpu) // ADD Vx, byte
{
    cpu->v[cpu->opcode.x] += cpu->opcode.nn;
}

void Chip8_Op8xy0(Chip8_Cpu* cpu) // LD Vx, Vy
{
    cpu->v[cpu->opcode.x] = cpu->v[cpu->opcode.y];
}

void Chip8_Op8xy1(Chip8_Cpu* cpu) // OR Vx, Vy
{
    cpu->v[cpu->opcode.x] |= cpu->v[cpu->opcode.y];

    if (cpu->config.flagReset)
    {
        cpu->v[0xF] = 0x00u;
    }
}

void Chip8_Op8xy2(Chip8_Cpu* cpu) // AND Vx, Vy
{
    cpu->v[cpu->opcode.x] &= cpu->v[cpu->opcode.y];
    
    if (cpu->config.flagReset)
    {
        cpu->v[0xF] = 0x00u;
    }
}

void Chip8_Op8xy3(Chip8_Cpu* cpu) // XOR Vx, Vy
{
    cpu->v[cpu->opcode.x] ^= cpu->v[cpu->opcode.y];
    
    if (cpu->config.flagReset)
    {
        cpu->v[0xF] = 0x00u;
    }
}

void Chip8_Op8xy4(Chip8_Cpu* cpu) // ADD Vx, Vy
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

void Chip8_Op8xy5(Chip8_Cpu* cpu) // SUB Vx, Vy
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

void Chip8_Op8xy6(Chip8_Cpu* cpu) // SHR Vx {, Vy}
{
    uint8_t tx = cpu->v[cpu->opcode.x];

    if (!cpu->config.shiftInPlace)
    {
        cpu->v[cpu->opcode.x] = cpu->v[cpu->opcode.y];
    }

    cpu->v[cpu->opcode.x] >>= 1u;
    cpu->v[0xF] = (tx & 0x01u);
}

void Chip8_Op8xy7(Chip8_Cpu* cpu) // SUBN Vx, Vy
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

void Chip8_Op8xyE(Chip8_Cpu* cpu) // SHL Vx {, Vy}
{
    uint8_t tx = cpu->v[cpu->opcode.x];

    if (!cpu->config.shiftInPlace)
    {
        cpu->v[cpu->opcode.x] = cpu->v[cpu->opcode.y];
    }

    cpu->v[cpu->opcode.x] <<= 1u;
    cpu->v[0xF] = (tx & 0x80u) >> 7u;
}

void Chip8_Op9xy0(Chip8_Cpu* cpu) // SNE Vx, Vy
{
    if (cpu->v[cpu->opcode.x] != cpu->v[cpu->opcode.y])
    {
        cpu->pc += 2;
    }
}

void Chip8_OpAnnn(Chip8_Cpu* cpu) // LD I, addr
{
    cpu->i = cpu->opcode.nnn;
}

void Chip8_OpBnnn(Chip8_Cpu* cpu) // JP V0, addr
{
    if (cpu->config.jumpValue)
    {
        cpu->pc = cpu->opcode.nnn + cpu->v[(cpu->opcode.inst & 0x0F00) >> 8u];
    }
    else
    {
        cpu->pc = cpu->opcode.nnn + cpu->v[0x0];
    }
}

void Chip8_OpCxkk(Chip8_Cpu* cpu) // RND Vx, byte
{
    static uint32_t seed = 0xB16B00B5u;

    static const uint32_t a = 1103515245;
    static const uint32_t c = 12345;
    static const uint32_t m = 2147483648;

    seed = (seed * a + c) % m;

    cpu->v[cpu->opcode.x] = seed & cpu->opcode.nn;
}

void Chip8_OpDxyn(Chip8_Cpu* cpu) // DRW Vx, Vy, nibble
{
    if (cpu->config.displayWait)
    {
        if (cpu->vbi == 0)
        {
            cpu->pc -= 2;
            return;
        }
    }
    
    cpu->vbi = 0;
    
    uint8_t tx = cpu->v[cpu->opcode.x] & (VIDEO_WIDTH - 1);
    uint8_t ty = cpu->v[cpu->opcode.y] & (VIDEO_HEIGHT - 1);

    cpu->v[0xF] = 0;

    for (size_t row = 0; row < cpu->opcode.n; row++)
    {
        for (size_t col = 0; col < 8; col++)
        {
            if (cpu->config.spriteClipping)
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

    cpu->draw = 1;
}

void Chip8_OpEx9E(Chip8_Cpu* cpu) // SKP Vx
{
    if (cpu->key & (0x0001u << cpu->v[cpu->opcode.x])) 
    {
        cpu->pc += 2;
    }
}

void Chip8_OpExA1(Chip8_Cpu* cpu) // SKNP Vx
{
    if (!(cpu->key & (0x0001u << cpu->v[cpu->opcode.x])))
    {
        cpu->pc += 2;
    }
}

void Chip8_OpFx07(Chip8_Cpu* cpu) // LD Vx, DT
{
    cpu->v[cpu->opcode.x] = cpu->delaytimer;
}

void Chip8_OpFx0A(Chip8_Cpu* cpu) // LD Vx, K
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

void Chip8_OpFx15(Chip8_Cpu* cpu) // LD DT, Vx
{
    cpu->delaytimer = cpu->v[cpu->opcode.x];
}

void Chip8_OpFx18(Chip8_Cpu* cpu) // LD ST, Vx
{
    cpu->soundtimer = cpu->v[cpu->opcode.x];
}

void Chip8_OpFx1E(Chip8_Cpu* cpu) // ADD I, Vx
{
    cpu->i += cpu->v[cpu->opcode.x];
}

void Chip8_OpFx29(Chip8_Cpu* cpu) // LD F, Vx
{
    cpu->i = FONTSET_ADDRESS + (5 * cpu->opcode.x);
}

void Chip8_OpFx33(Chip8_Cpu* cpu) // LD B, Vx
{
    uint8_t tx = cpu->v[cpu->opcode.x];

    cpu->memory[cpu->i + 2] = tx % 10;
    tx /= 10;

    cpu->memory[cpu->i + 1] = tx % 10;
    tx /= 10;

    cpu->memory[cpu->i] = tx % 10;
}

void Chip8_OpFx55(Chip8_Cpu* cpu) // LD [I], Vx
{
    size_t i;
    for (i = 0; i <= cpu->opcode.x; i++)
    {
        cpu->memory[cpu->i + i] = cpu->v[i];
    }

    if (cpu->config.indexIncrement)
    {
        cpu->i += i;
    }
}

void Chip8_OpFx65(Chip8_Cpu* cpu) // LD Vx, [I]
{
    size_t i;
    for (i = 0; i <= cpu->opcode.x; i++)
    {
        cpu->v[i] = cpu->memory[cpu->i + i];
    }

    if (cpu->config.indexIncrement)
    {
        cpu->i += i;
    }
}
