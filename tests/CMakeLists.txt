FetchContent_Declare(
  unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
  GIT_TAG v2.5.2)
FetchContent_MakeAvailable(unity)

add_executable(chip8_test chip8_test.c)

target_compile_features(chip8_test PRIVATE c_std_17)

target_link_libraries(chip8_test PRIVATE unity chip8)

add_test(NAME chip8_test COMMAND chip8_test)
