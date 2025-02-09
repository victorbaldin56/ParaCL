cmake_minimum_required(VERSION 3.14)

add_library(ast
  src/assign_node.cc
  src/binop_node.cc
  src/if_node.cc
  src/print_node.cc
  src/scan_node.cc
  src/scope.cc
  src/unop_node.cc
  src/value_node.cc
  src/var_node.cc
  src/while_node.cc
  src/context.cc
  src/if_scope.cc
)

target_include_directories(ast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(ast PUBLIC cxx_std_17)
