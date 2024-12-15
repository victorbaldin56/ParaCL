cmake_minimum_required(VERSION 3.14)
project(pcl)

include(FetchContent)
FetchContent_Declare(
  YAColorTTY
  GIT_REPOSITORY https://github.com/victorbaldin56/YAColorTTY.git
  GIT_TAG        3de6c11cadf3f71fc35a13996bc3daaeb619bdb0
)
FetchContent_MakeAvailable(YAColorTTY)

add_subdirectory(ast)
add_subdirectory(parser)
add_subdirectory(tests)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(GTest REQUIRED)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

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
