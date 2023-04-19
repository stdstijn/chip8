#include "chip8/chip8.h"

#include <unity.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void chip8_InitialTest_ThatIsEmpty_DoesPass(void)
{
    TEST_PASS();
}

int main(int argc, char* argv[])
{
    UNITY_BEGIN();

    RUN_TEST(chip8_InitialTest_ThatIsEmpty_DoesPass);

    return UNITY_END();
}
