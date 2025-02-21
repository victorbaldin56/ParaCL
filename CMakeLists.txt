cmake_minimum_required(VERSION 3.14)
project(pcl)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

add_subdirectory(ast)
add_subdirectory(parser)
add_subdirectory(interpreter)

if (${BUILD_TESTING})
  enable_testing()
  find_package(GTest REQUIRED)
  include(GoogleTest)
  add_subdirectory(tests)
endif()

add_executable(pcl
  main.cc
)

target_link_libraries(pcl interpreter)
