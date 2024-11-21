cmake_minimum_required(VERSION 3.14)
project(pcl)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

flex_target(scanner
  scanner.l
  ${CMAKE_CURRENT_BINARY_DIR}/plexer.cc
)

bison_target(parser
  pgrammar.y
  ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
  COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/pgrammar.tab.hh"
)

add_flex_bison_dependency(scanner parser)

add_library(parser STATIC
  driver.cc
  lexer.cc
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(parser ast_interface)
target_compile_features(parser PRIVATE cxx_std_17)

if (${USE_ASAN})
  target_compile_options(parser PUBLIC "-fsanitize=address,leak,undefined")
endif()
