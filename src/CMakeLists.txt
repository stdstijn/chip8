# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${Chip8_SOURCE_DIR}/include/chip8/*.h")
set(HEADER_LIST "${Chip8_SOURCE_DIR}/include/chip8/chip8.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(chip8 chip8.c ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(chip8 PUBLIC ../include)

# This depends on (header only) boost
target_link_libraries(chip8 PRIVATE)

# All users of this library will need at least C17
target_compile_features(chip8 PUBLIC c_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
