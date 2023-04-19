# Testing library
FetchContent_Declare(
  unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
  GIT_TAG v2.5.2)
FetchContent_MakeAvailable(unity)

# Tests need to be added as executables first
add_executable(chip8_test chip8_test.c)

# I'm using C++17 in the test
target_compile_features(chip8_test PRIVATE c_std_17)

# Should be linked to the main library
target_link_libraries(chip8_test PRIVATE unity chip8)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME chip8_test COMMAND chip8_test) # Command can be a target
