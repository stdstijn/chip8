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

  # Let's ensure -std=cxx instead of -std=gxx
  set(CMAKE_C_EXTENSIONS OFF)

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
