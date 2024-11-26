cmake_minimum_required(VERSION 3.14)
project(pcl)

add_subdirectory(ast)
add_subdirectory(parser)
add_subdirectory(tests)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(GTest REQUIRED)

add_executable(pcl
  main.cc
)

target_link_libraries(pcl
  Boost::program_options
  parser
  ast
)

if (${USE_ASAN})
  target_link_options(pcl PRIVATE "-fsanitize=address,leak,undefined")
endif()
