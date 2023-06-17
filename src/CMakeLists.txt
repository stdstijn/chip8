file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${Chip8_SOURCE_DIR}/include/chip8/*.h")

add_library(chip8 chip8.c dispatcher.c ${HEADER_LIST})

target_include_directories(chip8 PUBLIC ../include)

target_compile_features(chip8 PUBLIC c_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
