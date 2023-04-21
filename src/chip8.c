#include "chip8/chip8.h"

void Chip8_Create(CPU *cpu)
{
    // Initialize registers and memory once
}

void Chip8_Destroy(CPU *cpu)
{
    // Clean registers and memory once
}

void Chip8_Cycle(CPU *cpu)
{
    // Fetch opcode
    // Increment program counter
    // Decode opcode
    // Execute opcode
    // Update timers
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

