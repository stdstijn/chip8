# CHIP-8

This project is a Chip-8 interpreter written in C that emulates the functionality of the Chip-8 virtual machine. It allows users to run classic games and applications written in the Chip-8 language on modern hardware.

The project consists of a library that emulates the core functionality of a Chip-8 virtual machine. It can be used to run Chip-8 ROMs and can also be included as a library in other projects.

## Installation

To use the Chip-8 emulator, follow these steps:

1. Clone the repository: `git clone https://github.com/stdstijn/chip8.git`
2. Create a build directory: `cd chip-8 && mkdir build && cd build`
3. Generate the build files with CMake: `cmake ..`
4. Build the emulator: `make`

Please note that you need to have SDL (Simple DirectMedia Layer) installed on your machine for the emulator to work correctly.

## Usage

### Running ROMs

To run a Chip-8 ROM on the emulator, use the following command:

`./emulator <path_to_rom>`

Replace `<path_to_rom>` with the path to the .ch8 ROM file you want to run.

### Including as a Library

You can also include the Chip-8 emulator as a library in your own projects. To do this, just point Cmake to this directory and utilize the Chip-8 API and configure the quirks according to your platform requirements.

### Test ROMs

The project includes test ROMs in the `test` directory. These ROMs can be used to verify the correctness of the emulator's implementation.

## Implementation Details

The Chip-8 implementation provided in this project is a fairly simple one, following the description of the original COSMAC VIP interpreter. While the core functionality is implemented, please note that this emulator is more of a proof of concept and may have some limitations.

## Contributing

Contributions, suggestions, and pull requests are welcome! If you have any ideas for improvement or bug fixes, feel free to open an issue or submit a pull request on the project's GitHub repository.

## Acknowledgments

Special thanks to the authors of the Awesome CHIP-8 project and the CHIP-8 Test Suite for their valuable resources and contributions to the CHIP-8 community and helping me realizing this project.
