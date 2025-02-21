cmake_minimum_required(VERSION 3.14)
project(pcl)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

if (${BUILD_TESTING})
  find_package(GoogleTest REQUIRED)

  enable_testing()
  include(GoogleTest)
endif()

add_subdirectory(ast)
add_subdirectory(parser)
add_subdirectory(interpreter)

if (${BUILD_TESTING})
  add_subdirectory(tests)
endif()

add_executable(pcl
  main.cc
)

target_link_libraries(pcl interpreter)
