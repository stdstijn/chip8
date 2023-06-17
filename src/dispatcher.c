#include "chip8/dispatcher.h"

Chip8_DispatchCodes Chip8_DispatchOpcode(Chip8_Cpu* cpu)
{
    uint16_t opcode = cpu->opcode.inst & 0xF000u;

    switch (opcode)
    {
    case 0x0000:
        switch (cpu->opcode.n)
        {
        case 0x0000:
            Chip8_Op00E0(cpu);
            break;
        case 0x000E:
            Chip8_Op00EE(cpu);
            break;
        default:
            return OPCODE_INVALID;
        }
        break;
    case 0x1000:
        Chip8_Op1nnn(cpu);
        break;
    case 0x2000:
        Chip8_Op2nnn(cpu);
        break;
    case 0x3000:
        Chip8_Op3xkk(cpu);
        break;
    case 0x4000:
        Chip8_Op4xkk(cpu);
        break;
    case 0x5000:
        Chip8_Op5xy0(cpu);
        break;
    case 0x6000:
        Chip8_Op6xkk(cpu);
        break;
    case 0x7000:
        Chip8_Op7xkk(cpu);
        break;
    case 0x8000:
        switch (cpu->opcode.n)
        {
        case 0x0000:
            Chip8_Op8xy0(cpu);
            break;
        case 0x0001:
            Chip8_Op8xy1(cpu);
            break;
        case 0x0002:
            Chip8_Op8xy2(cpu);
            break;
        case 0x0003:
            Chip8_Op8xy3(cpu);
            break;
        case 0x0004:
            Chip8_Op8xy4(cpu);
            break;
        case 0x0005:
            Chip8_Op8xy5(cpu);
            break;
        case 0x0006:
            Chip8_Op8xy6(cpu);
            break;
        case 0x0007:
            Chip8_Op8xy7(cpu);
            break;
        case 0x000E:
            Chip8_Op8xyE(cpu);
            break;
        default:
            return OPCODE_INVALID;
        }
        break;
    case 0x9000:
        Chip8_Op9xy0(cpu);
        break;
    case 0xA000:
        Chip8_OpAnnn(cpu);
        break;
    case 0xB000:
        Chip8_OpBnnn(cpu);
        break;
    case 0xC000:
        Chip8_OpCxkk(cpu);
        break;
    case 0xD000:
        Chip8_OpDxyn(cpu);
        break;
    case 0xE000:
        switch (cpu->opcode.nn)
        {
        case 0x009E:
            Chip8_OpEx9E(cpu);
            break;
        case 0x00A1:
            Chip8_OpExA1(cpu);
            break;
        default:
            return OPCODE_INVALID;
        }
        break;
    case 0xF000:
        switch (cpu->opcode.nn)
        {
        case 0x0007:
            Chip8_OpFx07(cpu);
            break;
        case 0x000A:
            Chip8_OpFx0A(cpu);
            break;
        case 0x0015:
            Chip8_OpFx15(cpu);
            break;
        case 0x0018:
            Chip8_OpFx18(cpu);
            break;
        case 0x001E:
            Chip8_OpFx1E(cpu);
            break;
        case 0x0029:
            Chip8_OpFx29(cpu);
            break;
        case 0x0033:
            Chip8_OpFx33(cpu);
            break;
        case 0x0055:
            Chip8_OpFx55(cpu);
            break;
        case 0x0065:
            Chip8_OpFx65(cpu);
            break;
        default:
            return OPCODE_INVALID;
        }
        break;
    default:
        return OPCODE_INVALID;
    }

    return OPCODE_OK;
}
