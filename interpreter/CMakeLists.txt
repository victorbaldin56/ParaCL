cmake_minimum_required(VERSION 3.14)

add_library(interpreter
  src/interpreter.cc
  src/cmd_parser.cc
)

target_include_directories(interpreter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(interpreter PUBLIC Boost::program_options)
target_link_libraries(interpreter PRIVATE parser)
