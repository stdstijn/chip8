#include "chip8/chip8.h"

#include <unity.h>

static CPU chip8;

void setUp(void)
{
    Chip8_Create(&chip8);
}

void tearDown(void)
{
    Chip8_Destroy(&chip8);
}

void chip8_Chip8Create_WithReferenceToEmptyCPU_InitializesCPU(void)
{
    Chip8_Create(&chip8);

    TEST_ASSERT_EQUAL_UINT16(0x200, chip8.pc);
}

void chip8_Chip8Destroy_WithReferenceToEmptyCPU_CPUCastedToVoid(void)
{
    Chip8_Destroy(&chip8);

    TEST_PASS();
}

void chip8_Op00E0_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_00E0(&chip8);

    TEST_IGNORE();
}

void chip8_Op00EE_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_00EE(&chip8);

    TEST_IGNORE();
}

void chip8_Op0nnn_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_0nnn(&chip8);

    TEST_IGNORE();
}

void chip8_Op1nnn_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_1nnn(&chip8);

    TEST_IGNORE();
}

void chip8_Op2nnn_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_2nnn(&chip8);

    TEST_IGNORE();
}

void chip8_Op3xkk_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_3xkk(&chip8);

    TEST_IGNORE();
}

void chip8_Op4xkk_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_4xkk(&chip8);

    TEST_IGNORE();
}

void chip8_Op5xy0_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_5xy0(&chip8);

    TEST_IGNORE();
}

void chip8_Op6xkk_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_6xkk(&chip8);

    TEST_IGNORE();
}

void chip8_Op7ckk_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_7xkk(&chip8);

    TEST_IGNORE();
}

void chip8_Op8xy0_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_8xy0(&chip8);

    TEST_IGNORE();
}

void chip8_Op8xy1_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_8xy1(&chip8);

    TEST_IGNORE();
}

void chip8_Op8xy2_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_8xy2(&chip8);

    TEST_IGNORE();
}

void chip8_Op8xy3_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_8xy3(&chip8);

    TEST_IGNORE();
}

void chip8_Op8xy4_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_8xy4(&chip8);

    TEST_IGNORE();
}

void chip8_Op8xy5_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_8xy5(&chip8);

    TEST_IGNORE();
}

void chip8_Op8xy6_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_8xy6(&chip8);

    TEST_IGNORE();
}

void chip8_Op8xy7_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_8xy7(&chip8);

    TEST_IGNORE();
}

void chip8_Op8xyE_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_8xyE(&chip8);

    TEST_IGNORE();
}

void chip8_Op9xy0_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_9xy0(&chip8);

    TEST_IGNORE();
}

void chip8_OpAnnn_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Annn(&chip8);

    TEST_IGNORE();
}

void chip8_OpBnnn_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Bnnn(&chip8);

    TEST_IGNORE();
}

void chip8_OpCxkk_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Cxkk(&chip8);

    TEST_IGNORE();
}

void chip8_OpDxyn_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Dxyn(&chip8);

    TEST_IGNORE();
}

void chip8_OpEx9E_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Ex9E(&chip8);

    TEST_IGNORE();
}

void chip8_OpExA1_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_ExA1(&chip8);

    TEST_IGNORE();
}

void chip8_OpFx07_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Fx07(&chip8);

    TEST_IGNORE();
}

void chip8_OpFx0A_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Fx0A(&chip8);

    TEST_IGNORE();
}

void chip8_OpFx15_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Fx15(&chip8);

    TEST_IGNORE();
}

void chip8_OpFx18_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Fx18(&chip8);

    TEST_IGNORE();
}

void chip8_OpFx1E_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Fx1E(&chip8);

    TEST_IGNORE();
}

void chip8_OpFx29_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Fx29(&chip8);

    TEST_IGNORE();
}

void chip8_OpFx33_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Fx33(&chip8);

    TEST_IGNORE();
}

void chip8_OpFx55_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Fx55(&chip8);

    TEST_IGNORE();
}

void chip8_OpFx65_OpcodeTest_AllFunctionalityCorrect(void)
{
    // OP_Fx65(&chip8);

    TEST_IGNORE();
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(chip8_Chip8Create_WithReferenceToEmptyCPU_InitializesCPU);
    RUN_TEST(chip8_Chip8Destroy_WithReferenceToEmptyCPU_CPUCastedToVoid);
    RUN_TEST(chip8_Op00E0_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op00EE_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op0nnn_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op1nnn_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op2nnn_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op3xkk_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op4xkk_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op5xy0_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op6xkk_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op7ckk_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op8xy0_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op8xy1_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op8xy2_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op8xy3_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op8xy4_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op8xy5_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op8xy5_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op8xy6_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op8xy7_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op8xyE_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_Op9xy0_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpAnnn_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpBnnn_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpCxkk_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpDxyn_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpExA1_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpEx9E_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpFx07_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpFx0A_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpFx15_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpFx18_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpFx29_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpFx33_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpFx55_OpcodeTest_AllFunctionalityCorrect);
    RUN_TEST(chip8_OpFx65_OpcodeTest_AllFunctionalityCorrect);

    return UNITY_END();
}
