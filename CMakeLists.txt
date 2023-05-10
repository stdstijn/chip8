cmake_minimum_required(VERSION 3.14...3.22)

project(
  Chip8
  VERSION 0.1.0
  DESCRIPTION "A Chip-8 emulator written in C"
  LANGUAGES C)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
  message(FATAL_ERROR "In-source builds are not allowed.
    Please create a subfolder and use `cmake ..` inside it.
    NOTE: cmake creates CMakeCache.txt and CMakeFiles/*.
          Remove them, or cmake will refuse to work.")
  endif()

  set(CMAKE_C_STANDARD 17)
  set(CMAKE_C_STANDARD_REQUIRED ON)
  set(CMAKE_C_EXTENSIONS OFF)

  add_compile_options(-Wall -Wextra -Werror -pedantic -O1)

  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  include(CTest)

  option(VENDORED_SDL "Use vendored SDL library" OFF)
  if(VENDORED_SDL)
    add_subdirectory(extern/sdl EXCLUDE_FROM_ALL)
  else()
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
  endif()
endif()

include(FetchContent)

add_subdirectory(src)

add_subdirectory(apps)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR CHIP8_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
