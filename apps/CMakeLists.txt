add_executable(emulator emulator.c)
target_compile_features(emulator PRIVATE c_std_17)

target_link_libraries(emulator PRIVATE chip8)
