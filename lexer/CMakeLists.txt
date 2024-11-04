cmake_minimum_required(VERSION 3.14)
project(pcl)

find_package(FLEX REQUIRED)

flex_target(scanner
  scanner.l
  ${CMAKE_CURRENT_BINARY_DIR}/yylexer.cc
)

add_library(lexer STATIC
  ${FLEX_scanner_OUTPUTS}
)

target_compile_features(lexer INTERFACE cxx_std_17)
target_include_directories(lexer PUBLIC .)
