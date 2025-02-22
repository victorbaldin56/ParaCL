# ParaCL

Programming language. Project from K. Vladimirov's ([@tilir](https://github.com/tilir)) course at MIPT.

## Prerequisites

This project uses Conan package manager to handle dependencies. Before installing Conan
you need following:

* Git
* CMake
* C++ compiler and `libstdc++` with at least C++17 support.

These dependencies are not handled by Conan yet and also need to be installed via your
system package manager:

* Flex
* Bison

## Examples

ParaCL syntax is quite similar to C. Examples can be found in `tests` directory.

## Build

To build:

1. Clone repo:

   ```sh
   git clone --recursive https://github.com/victorbaldin56/ParaCL.git
   ```

1. Create virtual environment for Python:

   ```sh
   python3 -m venv .venv
   source .venv/bin/activate
   ```

1. Install Conan:

   ```sh
   pip3 install conan
   conan profile detect --force
   ```

1. Install Conan requirements and toolchain:

   ```sh
   conan install . --output-folder=build --build=missing
   ```

1. Configure CMake:

   ```sh
   cmake .. --preset conan-release
   ```

1. Build:

   ```sh
   cmake --build . -j
   ```

## Docs

To generate docs, you need Doxygen. Once you have it installed, just run:

```sh
doxygen
```
