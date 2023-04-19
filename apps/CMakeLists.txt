# Create executable target
add_executable(emulator emulator.c)
target_compile_features(emulator PRIVATE c_std_17)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(mygame PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL library.
if(VENDORED_SDL)
    target_link_libraries(emulator PRIVATE SDL2::SDL2 chip8)
else()
    target_link_libraries(emulator PRIVATE SDL2 chip8)
endif()
