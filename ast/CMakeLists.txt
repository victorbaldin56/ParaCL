cmake_minimum_required(VERSION 3.14)
project(ast)

add_library(ast_interface INTERFACE)
target_include_directories(ast_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(ast STATIC
  concrete/assign_node.cc
  concrete/binop_node.cc
  concrete/if_node.cc
  concrete/print_node.cc
  concrete/scan_node.cc
  concrete/scope.cc
  concrete/unop_node.cc
  concrete/value_node.cc
  concrete/var_node.cc
  concrete/while_node.cc
  context.cc
)

target_compile_features(ast PRIVATE cxx_std_17)
target_link_libraries(ast ast_interface)

if (${USE_ASAN})
  target_compile_options(ast PUBLIC "-fsanitize=address,leak,undefined")
endif()
