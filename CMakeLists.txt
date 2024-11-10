cmake_minimum_required(VERSION 3.14)
project(pcl)

add_subdirectory(ast)
add_subdirectory(parser)

find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(pcl
  main.cc
)

target_link_libraries(pcl
  Boost::program_options
  parser
  ast
)
