add_executable(test test.cpp)
enable_testing()
include(GoogleTest)

target_link_libraries(test
  parser
  ast
  gtest gmock
)

gtest_discover_tests(test)