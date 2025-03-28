cmake_minimum_required(VERSION 3.14)

flex_target(scanner
  scanner.l
  ${CMAKE_CURRENT_BINARY_DIR}/plexer.cc
)

bison_target(parser
  pgrammar.y
  ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
  COMPILE_FLAGS "-Werror"
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/pgrammar.tab.hh
)

add_flex_bison_dependency(scanner parser)

add_library(parser
  src/driver.cc
  src/lexer.cc
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(parser PUBLIC ast)
