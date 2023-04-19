add_executable(emulator emulator.c)
target_compile_features(emulator PRIVATE c_std_17)

if(TARGET SDL2::SDL2main)
  # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
  target_link_libraries(emulator PRIVATE chip8 SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(emulator PRIVATE chip8 SDL2::SDL2)
