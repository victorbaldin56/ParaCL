[settings]
os=Linux
compiler=clang
compiler.version=14
compiler.libcxx=libstdc++11
build_type=Debug

[options]
testing=True

[conf]
tools.build:cxxflags=["-fsanitize=address,leak,undefined"]
tools.build:exelinkflags=["-fsanitize=address,leak,undefined"]
tools.build:sharedlinkflags=["-fsanitize=address,leak,undefined"]
