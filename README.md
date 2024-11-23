# ParaCL
Programming language. Project from K. Vladimirov's ([@tilir](https://github.com/tilir)) course at MIPT.

## Prerequisites
To build you need the following installed:
* Git
* CMake
* Any C++ compiler supported by CMake
* Boost
* Flex
* Bison

## Examples
ParaCL syntax is quite similar to C. Examples can be found in `examples` directory.

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
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```
6. Build:
```sh
cmake --build . -j`nproc`
```
