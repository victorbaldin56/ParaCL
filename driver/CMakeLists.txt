cmake_minimum_required(VERSION 3.14)
project(pcl)

find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(pcl
  driver.cc
  main.cc
)

target_link_libraries(pcl Boost::program_options;lexer)
