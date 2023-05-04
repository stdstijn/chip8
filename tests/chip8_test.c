#include "chip8/chip8.h"

#include <unity.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void chip8_Chip8CreateTest_WithReferenceToEmptyCPU_InitializesCPU(void)
{
    CPU chip8 = { 0 };
    Chip8_Create(&chip8);

    TEST_ASSERT_EQUAL_UINT16(0x200, chip8.pc);
}

int main(int argc, char* argv[])
{
    UNITY_BEGIN();

    RUN_TEST(chip8_Chip8CreateTest_WithReferenceToEmptyCPU_InitializesCPU);

    return UNITY_END();
}
