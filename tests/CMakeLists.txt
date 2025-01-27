add_executable(test test.cpp)
if (${BUILD_TESTING})
  enable_testing()
endif()

include(GoogleTest)

set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(test PUBLIC TEST_DATA_DIR="${TEST_DATA_DIR}")
target_link_libraries(test parser ast gtest::gtest)

gtest_discover_tests(test)
