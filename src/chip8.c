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

static void Dispatcher0(CPU *cpu)
{
    (*(cpu->dispatcher0[cpu->opcode & 0x000Fu]))(cpu);
}

static void Dispatcher1(CPU *cpu)
{
    (*(cpu->dispatcher1[0x0]))(cpu);
}

static void Dispatcher2(CPU *cpu)
{
    (*(cpu->dispatcher2[0x0]))(cpu);
}

static void Dispatcher3(CPU *cpu)
{
    (*(cpu->dispatcher3[0x0]))(cpu);
}

static void Dispatcher4(CPU *cpu)
{
    (*(cpu->dispatcher4[0x0]))(cpu);
}

static void Dispatcher5(CPU *cpu)
{
    (*(cpu->dispatcher5[0x0]))(cpu);
}

static void Dispatcher6(CPU *cpu)
{
    (*(cpu->dispatcher6[0x0]))(cpu);
}

static void Dispatcher7(CPU *cpu)
{
    (*(cpu->dispatcher7[0x0]))(cpu);
}

static void Dispatcher8(CPU *cpu)
{
    (*(cpu->dispatcher8[cpu->opcode & 0x000Fu]))(cpu);
}

static void Dispatcher9(CPU *cpu)
{
    (*(cpu->dispatcher9[0x0]))(cpu);
}

static void DispatcherA(CPU *cpu)
{
    (*(cpu->dispatcherA[0x0]))(cpu);
}

static void DispatcherB(CPU *cpu)
{
    (*(cpu->dispatcherB[0x0]))(cpu);
}

static void DispatcherC(CPU *cpu)
{
    (*(cpu->dispatcherC[0x0]))(cpu);
}

static void DispatcherD(CPU *cpu)
{
    (*(cpu->dispatcherD[0x0]))(cpu);
}

static void DispatcherE(CPU *cpu)
{
    (*(cpu->dispatcherE[cpu->opcode & 0x000Fu]))(cpu);
}

static void DispatcherF(CPU *cpu)
{
    (*(cpu->dispatcher0[cpu->opcode & 0x00FFu]))(cpu);
}

static void ClearMemory(void *ptr, size_t len)
{
    char *byte = ptr;

    for (size_t i = 0; i < len; i++)
    {
        byte[i] = 0;
    }
}

static void CopyMemory(void *dest, const void *src, size_t num)
{
    const char *srcByte = src;
    char *destByte = dest;

    for (size_t i = 0; i < num; i++)
    {
        destByte[i] = srcByte[i];
    }
}

static void NullOpcodeDispatcher(OpcodeFunc funcArray[], size_t arraySize)
{
    for (size_t i = 0; i <= arraySize; i++)
    {
        funcArray[i] = OP_0nnn;
    }
}

void Chip8_Create(CPU *cpu)
{
    // Initialize registers and memory once
    ClearMemory(cpu, sizeof(CPU));
    cpu->pc = START_ADDRESS;

    // Load fontset
    CopyMemory(&cpu->memory[FONTSET_ADDRESS], fontset, sizeof(fontset));

    // Null dispatcher functions initially 
    NullOpcodeDispatcher(cpu->dispatcher0, sizeof(cpu->dispatcher0));
    NullOpcodeDispatcher(cpu->dispatcher1, sizeof(cpu->dispatcher1));
    NullOpcodeDispatcher(cpu->dispatcher2, sizeof(cpu->dispatcher2));
    NullOpcodeDispatcher(cpu->dispatcher3, sizeof(cpu->dispatcher3));
    NullOpcodeDispatcher(cpu->dispatcher4, sizeof(cpu->dispatcher4));
    NullOpcodeDispatcher(cpu->dispatcher5, sizeof(cpu->dispatcher5));
    NullOpcodeDispatcher(cpu->dispatcher6, sizeof(cpu->dispatcher6));
    NullOpcodeDispatcher(cpu->dispatcher7, sizeof(cpu->dispatcher7));
    NullOpcodeDispatcher(cpu->dispatcher8, sizeof(cpu->dispatcher8));
    NullOpcodeDispatcher(cpu->dispatcher9, sizeof(cpu->dispatcher9));
    NullOpcodeDispatcher(cpu->dispatcherA, sizeof(cpu->dispatcherA));
    NullOpcodeDispatcher(cpu->dispatcherB, sizeof(cpu->dispatcherB));
    NullOpcodeDispatcher(cpu->dispatcherC, sizeof(cpu->dispatcherC));
    NullOpcodeDispatcher(cpu->dispatcherD, sizeof(cpu->dispatcherD));
    NullOpcodeDispatcher(cpu->dispatcherE, sizeof(cpu->dispatcherE));
    NullOpcodeDispatcher(cpu->dispatcherF, sizeof(cpu->dispatcherF));
    
    // Setup opcode function pointer table
    cpu->table[0x0] = Dispatcher0;
    cpu->table[0x1] = Dispatcher1;
    cpu->table[0x2] = Dispatcher2;
    cpu->table[0x3] = Dispatcher3;
    cpu->table[0x4] = Dispatcher4;
    cpu->table[0x5] = Dispatcher5;
    cpu->table[0x6] = Dispatcher6;
    cpu->table[0x7] = Dispatcher7;
    cpu->table[0x8] = Dispatcher8;
    cpu->table[0x9] = Dispatcher9;
    cpu->table[0xA] = DispatcherA;
    cpu->table[0xB] = DispatcherB;
    cpu->table[0xC] = DispatcherC;
    cpu->table[0xD] = DispatcherD;
    cpu->table[0xE] = DispatcherE;
    cpu->table[0xF] = DispatcherF;

    // Populate dispatcher function pointer arrays
    cpu->dispatcher0[0x0] = OP_00E0;
    cpu->dispatcher0[0xE] = OP_00EE;
    cpu->dispatcher1[0x0] = OP_1nnn;
    cpu->dispatcher2[0x0] = OP_2nnn;
    cpu->dispatcher3[0x0] = OP_3xkk;
    cpu->dispatcher4[0x0] = OP_4xkk;
    cpu->dispatcher5[0x0] = OP_5xy0;
    cpu->dispatcher6[0x0] = OP_6xkk;
    cpu->dispatcher7[0x0] = OP_7xkk;
    cpu->dispatcher8[0x0] = OP_8xy0;
    cpu->dispatcher8[0x1] = OP_8xy1;
    cpu->dispatcher8[0x2] = OP_8xy2;
    cpu->dispatcher8[0x3] = OP_8xy3;
    cpu->dispatcher8[0x4] = OP_8xy4;
    cpu->dispatcher8[0x5] = OP_8xy5;
    cpu->dispatcher8[0x6] = OP_8xy6;
    cpu->dispatcher8[0x7] = OP_8xy7;
    cpu->dispatcher8[0xE] = OP_8xyE;
    cpu->dispatcher9[0x0] = OP_9xy0;
    cpu->dispatcherA[0x0] = OP_Annn;
    cpu->dispatcherB[0x0] = OP_Bnnn;
    cpu->dispatcherC[0x0] = OP_Cxkk;
    cpu->dispatcherD[0x0] = OP_Dxyn;
    cpu->dispatcherE[0xE] = OP_Ex9E;
    cpu->dispatcherE[0x1] = OP_ExA1;
    cpu->dispatcherF[0x07] = OP_Fx07;
    cpu->dispatcherF[0x0A] = OP_Fx0A;
    cpu->dispatcherF[0x15] = OP_Fx15;
    cpu->dispatcherF[0x18] = OP_Fx18;
    cpu->dispatcherF[0x1E] = OP_Fx1E;
    cpu->dispatcherF[0x29] = OP_Fx29;
    cpu->dispatcherF[0x33] = OP_Fx33;
    cpu->dispatcherF[0x55] = OP_Fx55;
    cpu->dispatcher9[0x65] = OP_Fx65;
}

void Chip8_Destroy(CPU *cpu)
{
    // Clean registers and memory once
    (void) cpu;
}

void Chip8_Cycle(CPU *cpu)
{
    // Fetch opcode
    cpu->opcode = (cpu->memory[cpu->pc] << 8u) | cpu->memory[cpu->pc + 1];

    // Increment program counter
    cpu->pc += 2;

    // Decode opcode
    unsigned char nibble = (cpu->opcode & 0xF000u) >> 12u;

    // Execute opcode
    (*(cpu->table[nibble]))(cpu);

    // Update timers
    if (cpu->delaytimer > 0)
    {
        cpu->delaytimer -= 1;
    }
    if (cpu->soundtimer > 0)
    {
        cpu->delaytimer -= 1;
    }
}

void OP_00E0(CPU *cpu) // CLS
{

}

void OP_00EE(CPU *cpu) // RET
{

}

void OP_0nnn(CPU *cpu) // SYS addr
{

}

void OP_1nnn(CPU *cpu) // JMP addr
{

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

}

void OP_7xkk(CPU *cpu) // ADD Vx, byte
{

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

}

void OP_Bnnn(CPU *cpu) // JP V0, addr
{

}

void OP_Cxkk(CPU *cpu) // RND Vx, byte
{

}

void OP_Dxyn(CPU *cpu) // DRW Vx, Vy, nibble
{

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
