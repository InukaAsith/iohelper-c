# IOHelper for C

### A simple C library for handling inputs (including strings) with dynamic memory management.

#### Inspired by [cs50](https://cs50.harvard.edu)'s [lib50](https://github.com/cs50/libcs50/)

## Features

- `get_string("Output message")` function for string input, Memory is dynamically allocated and automatically freed when the program exits.
- `get_int("Output message")` function for integer input
- `get_float("Output message")` function for float input
- `get_double("Output message")` function for double input
- `get_long("Output message")` function for long input
- `get_char("Output message")` function for character input

- `free_string(string)` function for freeing memory allocated for a string manually (Overrides the default free at exit)'


## Usage

Include the header file in your C program:

```c
#include <iohelper/iohelper.h>
```

### Example

```c
#include <iohelper/iohelper.h>
#include <stdio.h>

int main() {
    string = get_string("Enter your name: ");
    printf("Hello, %s!\n", name);
    // Memory is automatically managed
    return 0;
}
```

## Compiling with GCC

After installing the library, you can compile your programs using GCC with the following flags:

```bash
# Basic compilation
gcc your_program.c -liohelper -o your_program

# If the library is not in the standard path, specify the path:
gcc your_program.c -L/usr/local/lib -I/usr/local/include -liohelper -o your_program
```

Note: The order of flags matters. The `-liohelper` flag should come after your source files.

### Example Compilation

```bash
# Compile hello.c
gcc hello.c -liohelper -o hello

# Run the program
./hello
```

## Installation

### Clone the Repository

First, clone the repository using one of these methods:

#### HTTPS
```bash
git clone https://github.com/inukaasith/iohelper.git
cd iohelper
```

#### SSH
```bash
git clone git@github.com:inukaasith/iohelper.git
cd iohelper
```

### Windows (MSVC)

1. Download and extract the repository
2. Open Command Prompt and run:
```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
cmake --install .
```

### Windows (MinGW)

1. Install MinGW and make sure it's added to your PATH
2. Open Command Prompt in the project directory and run:
```cmd
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
mingw32-make install
```

### macOS

1. Make sure you have Xcode Command Line Tools installed:
```bash
xcode-select --install
```

2. Build and install the library:
```bash
mkdir build && cd build
cmake ..
make
sudo make install
```

3. The library will be installed to `/usr/local/lib` and headers to `/usr/local/include/iohelper`

### Linux

```bash
mkdir build && cd build
cmake ..
make
sudo make install
```

After installation, the library will be available system-wide. On Linux and macOS, you might need to run `sudo ldconfig` to update the shared library cache.

## Building Options

By default, the library is built as a shared library. To build as a static library, use:

```bash
cmake .. -DBUILD_SHARED_LIBS=OFF
```

## Credits

This project is inspired by [cs50](https://cs50.harvard.edu)'s [lib50](https://github.com/cs50/libcs50/) library for C.


## License

This project is licensed under the MIT License - see the LICENSE file for details.
