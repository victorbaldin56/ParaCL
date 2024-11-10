cmake_minimum_required(VERSION 3.14)
project(ast)

add_library(ast_interface INTERFACE)
target_include_directories(ast_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(ast STATIC node.cc)
target_compile_features(ast PRIVATE cxx_std_17)
