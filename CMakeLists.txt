# Works with 3.14 and tested through 3.26
cmake_minimum_required(VERSION 3.14...3.22)

# Project name and a few useful settings. Other commands can pick up the results
project(
  Chip8
  VERSION 0.1.0
  DESCRIPTION "A Chip-8 emulator written in C"
  LANGUAGES C)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # Optionally set things like CMAKE_C_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
  set(CMAKE_C_STANDARD 17)
  set(CMAKE_C_STANDARD_REQUIRED ON)
  set(CMAKE_C_EXTENSIONS OFF)

  # Make sure executable will end up in the build directory
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
# FetchContent_MakeAvailable was added in CMake 3.14; simpler usage
include(FetchContent)

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR CHIP8_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

# Create an option to switch between a system SDL library and a vendored SDL library
option(VENDORED_SDL "Use vendored SDL library" OFF)
if(VENDORED_SDL)
  add_subdirectory(extern/sdl EXCLUDE_FROM_ALL)
else()
  # 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
  find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

  # 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available
  find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
endif()
