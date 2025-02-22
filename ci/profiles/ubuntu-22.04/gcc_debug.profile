[settings]
arch=x86_64
os=Linux
compiler=gcc
compiler.version=12
compiler.libcxx=libstdc++11
build_type=Debug

[buildenv]
CC=/usr/bin/gcc-11
CXX=/usr/bin/g++-11

[options]
testing=True

[conf]
tools.build:cxxflags=["-fsanitize=address,leak,undefined"]
tools.build:exelinkflags=["-fsanitize=address,leak,undefined"]
tools.build:sharedlinkflags=["-fsanitize=address,leak,undefined"]
