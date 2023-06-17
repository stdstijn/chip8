#include "chip8/dispatcher.h"

static uint16_t dispatcher0X(Chip8_Cpu* cpu)
{
    uint8_t nibble = cpu->opcode.inst & 0x000Fu;

    if (nibble > 0xE)
    {
        return cpu->opcode.inst;
    }

    (*(cpu->OP0x[nibble]))(cpu);

    return 0;
}

static uint16_t dispatcher1X(Chip8_Cpu* cpu)
{
    (*(cpu->OP1x[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcher2X(Chip8_Cpu* cpu)
{
    (*(cpu->OP2x[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcher3X(Chip8_Cpu* cpu)
{
    (*(cpu->OP3x[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcher4X(Chip8_Cpu* cpu)
{
    (*(cpu->OP4x[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcher5X(Chip8_Cpu* cpu)
{
    (*(cpu->OP5x[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcher6X(Chip8_Cpu* cpu)
{
    (*(cpu->OP6x[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcher7X(Chip8_Cpu* cpu)
{
    (*(cpu->OP7x[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcher8X(Chip8_Cpu* cpu)
{
    uint8_t nibble = cpu->opcode.inst & 0x000Fu;

    if (nibble > 0xE)
    {
        return cpu->opcode.inst;
    }

    (*(cpu->OP8x[nibble]))(cpu);

    return 0;
}

static uint16_t dispatcher9X(Chip8_Cpu* cpu)
{
    (*(cpu->OP9x[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcherAX(Chip8_Cpu* cpu)
{
    (*(cpu->OPAx[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcherBX(Chip8_Cpu* cpu)
{
    (*(cpu->OPBx[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcherCX(Chip8_Cpu* cpu)
{
    (*(cpu->OPCx[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcherDX(Chip8_Cpu* cpu)
{
    (*(cpu->OPDx[0x0]))(cpu);

    return 0;
}

static uint16_t dispatcherEX(Chip8_Cpu* cpu)
{
    uint8_t nibble = cpu->opcode.inst & 0x000Fu;

    if (nibble > 0xE)
    {
        return cpu->opcode.inst;
    }

    (*(cpu->OPEx[nibble]))(cpu);

    return 0;
}

static uint16_t dispatcherFX(Chip8_Cpu* cpu)
{
    uint8_t nibble = cpu->opcode.inst & 0x00FFu;

    if (nibble > 0x65)
    {
        return cpu->opcode.inst;
    }

    (*(cpu->OPFx[nibble]))(cpu);

    return 0;
}

void InitialiseDispatcher(Chip8_Cpu* cpu)
{
    cpu->Dispatcher[0x0] = dispatcher0X;
    cpu->OP0x[0x00] = Chip8_OP00E0;
    cpu->OP0x[0x0E] = Chip8_OP00EE;

    cpu->Dispatcher[0x1] = dispatcher1X;
    cpu->OP1x[0x00] = Chip8_OP1nnn;

    cpu->Dispatcher[0x2] = dispatcher2X;
    cpu->OP2x[0x00] = Chip8_OP2nnn;

    cpu->Dispatcher[0x3] = dispatcher3X;
    cpu->OP3x[0x00] = Chip8_OP3xkk;

    cpu->Dispatcher[0x4] = dispatcher4X;
    cpu->OP4x[0x00] = Chip8_OP4xkk;

    cpu->Dispatcher[0x5] = dispatcher5X;
    cpu->OP5x[0x00] = Chip8_OP5xy0;

    cpu->Dispatcher[0x6] = dispatcher6X;
    cpu->OP6x[0x00] = Chip8_OP6xkk;

    cpu->Dispatcher[0x7] = dispatcher7X;
    cpu->OP7x[0x00] = Chip8_OP7xkk;

    cpu->Dispatcher[0x8] = dispatcher8X;
    cpu->OP8x[0x00] = Chip8_OP8xy0;
    cpu->OP8x[0x01] = Chip8_OP8xy1;
    cpu->OP8x[0x02] = Chip8_OP8xy2;
    cpu->OP8x[0x03] = Chip8_OP8xy3;
    cpu->OP8x[0x04] = Chip8_OP8xy4;
    cpu->OP8x[0x05] = Chip8_OP8xy5;
    cpu->OP8x[0x06] = Chip8_OP8xy6;
    cpu->OP8x[0x07] = Chip8_OP8xy7;
    cpu->OP8x[0x0E] = Chip8_OP8xyE;

    cpu->Dispatcher[0x9] = dispatcher9X;
    cpu->OP9x[0x00] = Chip8_OP9xy0;

    cpu->Dispatcher[0xA] = dispatcherAX;
    cpu->OPAx[0x00] = Chip8_OPAnnn;

    cpu->Dispatcher[0xB] = dispatcherBX;
    cpu->OPBx[0x00] = Chip8_OPBnnn;

    cpu->Dispatcher[0xC] = dispatcherCX;
    cpu->OPCx[0x00] = Chip8_OPCxkk;

    cpu->Dispatcher[0xD] = dispatcherDX;
    cpu->OPDx[0x00] = Chip8_OPDxyn;

    cpu->Dispatcher[0xE] = dispatcherEX;
    cpu->OPEx[0x0E] = Chip8_OPEx9E;
    cpu->OPEx[0x01] = Chip8_OPExA1;

    cpu->Dispatcher[0xF] = dispatcherFX;
    cpu->OPFx[0x07] = Chip8_OPFx07;
    cpu->OPFx[0x0A] = Chip8_OPFx0A;
    cpu->OPFx[0x15] = Chip8_OPFx15;
    cpu->OPFx[0x18] = Chip8_OPFx18;
    cpu->OPFx[0x1E] = Chip8_OPFx1E;
    cpu->OPFx[0x29] = Chip8_OPFx29;
    cpu->OPFx[0x33] = Chip8_OPFx33;
    cpu->OPFx[0x55] = Chip8_OPFx55;
    cpu->OPFx[0x65] = Chip8_OPFx65;
}
