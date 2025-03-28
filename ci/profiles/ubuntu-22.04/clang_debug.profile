[settings]
arch=x86_64
os=Linux
compiler=clang
compiler.version=14
compiler.libcxx=libc++
build_type=Debug

[buildenv]
CC=/usr/bin/clang-14
CXX=/usr/bin/clang++-14

[conf]
tools.build:cxxflags=["-std=c++17", "-fsanitize=address,leak,undefined"]
tools.build:exelinkflags=["-fsanitize=address,leak,undefined"]
tools.build:sharedlinkflags=["-fsanitize=address,leak,undefined"]