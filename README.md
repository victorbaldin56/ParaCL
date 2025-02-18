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
3. Create virtual environment:
```sh
python3 -m venv .venv
source .venv/bin/activate
pip3 install conan
conan profile detect --force
```
4. Install required packages:
```sh
conan install . --output-folder=build --build=missing
```
5. Generate build files:
```sh
cd build/
cmake .. --toolchain=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```
6. Build:
```sh
cmake --build . -j`nproc`
```

## Docs
To generate docs, you need Doxygen. Once you have it installed, just run:
```sh
doxygen
```
