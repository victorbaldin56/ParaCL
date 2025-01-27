cmake_minimum_required(VERSION 3.14)

add_library(ast_interface INTERFACE)
target_include_directories(ast_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

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
)

target_compile_features(ast PRIVATE cxx_std_17)
target_link_libraries(ast ast_interface)

