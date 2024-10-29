# ParaCL
Programming language. Project from K. Vladimirov's ([@tilir](https://github.com/tilir)) course at MIPT.

## Prerequisites
To build you need the following installed:
* Git
* CMake
* Any C++ compiler supported by CMake
* Boost

## Examples
ParaCL syntax is quite similar to C. Examples can be found in `examples` directory.

## Build
TO build:
1. Clone repo:
```sh
git clone --recursive https://github.com/victorbaldin56/ParaCL.git
```
2. Generate build files:
```sh
cmake -S . -B build
```
3. Build:
```sh
cmake --build build
```
