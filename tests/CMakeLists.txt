add_executable(unit_test test.cpp)

set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(unit_test PUBLIC TEST_DATA_DIR="${TEST_DATA_DIR}")
target_compile_definitions(unit_test PUBLIC CMAKE_BINARY_DIR="${CMAKE_BINARY_DIR}")
target_link_libraries(unit_test PRIVATE GTest::gmock)
target_include_directories(unit_test PRIVATE ${Boost_INCLUDE_DIRS})

gtest_discover_tests(unit_test)
