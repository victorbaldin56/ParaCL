[settings]
arch=x86_64
os=Linux
compiler=clang
compiler.version=17
compiler.libcxx=libc++
build_type=Debug

[options]
testing=True

[buildenv]
CC=/usr/bin/clang-17
CXX=/usr/bin/clang++-17

[conf]
tools.build:cxxflags=["-fsanitize=address,leak,undefined"]
tools.build:exelinkflags=["-fsanitize=address,leak,undefined"]
tools.build:sharedlinkflags=["-fsanitize=address,leak,undefined"]
