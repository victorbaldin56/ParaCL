#include "parser/driver.hh"
#include <algorithm>
#include <exception>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iterator>
#include <string>

const std::string TEST_DIR = std::string(TEST_DATA_DIR) + "/";

template <typename Stream1, typename Stream2>
void close_files(Stream1 &file1, Stream2 &file2) {
  file1.close();
  file2.close();
}

bool compare_files(const std::string &file1, const std::string &file2) {
  std::ifstream f1(file1, std::ios::binary), f2(file2, std::ios::binary);

  if (!f1.is_open() || !f2.is_open()) {
    throw std::runtime_error("Error with opening files.");
  }

  char ch1, ch2;
  int position = 0;

  while (f1.get(ch1) && f2.get(ch2)) {
    ++position;
    if (ch1 != ch2) {
      close_files(f1, f2);
      return false;
    }
  }

  if (f1.get(ch1) || f2.get(ch2)) {
    close_files(f1, f2);
    return false;
  }

  close_files(f1, f2);

  return true;
}

bool test(const std::string &pcl_file, const std::string &in_file,
          const std::string &out_file) {
  std::ifstream in(TEST_DIR + in_file);
  std::streambuf *cinbuf = std::cin.rdbuf();
  std::cin.rdbuf(in.rdbuf());

  std::ofstream out("buf.txt");
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());

  yy::PDriver driver(TEST_DIR + pcl_file);
  ast::current_scope = ast::makeScope();

  if (!driver.parse()) {
    throw std::runtime_error("Something went wrong.");
  }

  ast::current_scope->calc();

  std::cin.rdbuf(cinbuf);
  std::cout.rdbuf(coutbuf);

  close_files(in, out);

  return compare_files("buf.txt", TEST_DIR + out_file);
}

TEST(is_prime, test1) {
  ASSERT_TRUE(test("is_prime/is_prime.pcl", "is_prime/is_prime1.in",
                   "is_prime/is_prime1.out"));
}

TEST(is_prime, test2) {
  ASSERT_TRUE(test("is_prime/is_prime.pcl", "is_prime/is_prime2.in",
                   "is_prime/is_prime2.out"));
}

TEST(other, test1) {
  ASSERT_TRUE(test("other/other.pcl", "other/other1.in", "other/other1.out"));
}

TEST(fibs, test1) {
  ASSERT_TRUE(test("fibs/fibs.pcl", "fibs/fibs1.in", "fibs/fibs1.out"));
}

TEST(fibs, test2) {
  ASSERT_TRUE(test("fibs/fibs.pcl", "fibs/fibs2.in", "fibs/fibs2.out"));
}

TEST(fact, test1) {
  ASSERT_TRUE(test("fact/fact.pcl", "fact/fact1.in", "fact/fact1.out"));
}

TEST(braces, test1) {
  ASSERT_TRUE(
      test("braces/braces.pcl", "braces/braces1.in", "braces/braces1.out"));
}

TEST(assignment, test1) {
  ASSERT_TRUE(
      test("assignment/assignment.pcl",
           "assignment/assignment1.in",
           "assignment/assignment1.out"));
}

TEST(loop_input, test1) {
  ASSERT_TRUE(
      test("loop_input/loop_input.pcl",
           "loop_input/loop_input1.in",
           "loop_input/loop_input1.out"));
}

TEST(logic, test1) {
  ASSERT_TRUE(
      test("logic/logic.pcl",
           "logic/logic1.in",
           "logic/logic1.out"));
}

TEST(logic, test2) {
  ASSERT_TRUE(
      test("logic/logic.pcl",
           "logic/logic2.in",
           "logic/logic2.out"));
}

TEST(complex_logic, test1) {
  ASSERT_TRUE(
      test("complex_logic/complex_logic.pcl",
           "complex_logic/complex_logic1.in",
           "complex_logic/complex_logic1.out"));
}

TEST(complex_logic, test2) {
  ASSERT_TRUE(
      test("complex_logic/complex_logic.pcl",
           "complex_logic/complex_logic2.in",
           "complex_logic/complex_logic2.out"));
}

TEST(complex_logic, test3) {
  ASSERT_TRUE(
      test("complex_logic/complex_logic.pcl",
           "complex_logic/complex_logic3.in",
           "complex_logic/complex_logic3.out"));
}

TEST(print_logic, test1) {
  ASSERT_TRUE(
      test("print_logic/print_logic.pcl",
           "print_logic/print_logic1.in",
           "print_logic/print_logic1.out"));
}

TEST(else, test1) {
  ASSERT_TRUE(
      test("else/else.pcl",
           "else/else1.in",
           "else/else1.out"));
}

TEST(bitwise, test1) {
  ASSERT_TRUE(
      test("bitwise/bitwise.pcl",
           "bitwise/bitwise1.in",
           "bitwise/bitwise1.out"));
}

TEST(bitwise, test2) {
  ASSERT_TRUE(
      test("bitwise/bitwise.pcl",
           "bitwise/bitwise2.in",
           "bitwise/bitwise2.out"));
}

TEST(bitwise, test3) {
  ASSERT_TRUE(
      test("bitwise/bitwise.pcl",
           "bitwise/bitwise3.in",
           "bitwise/bitwise3.out"));
}

TEST(bitwise, test4) {
  ASSERT_TRUE(
      test("bitwise/bitwise.pcl",
           "bitwise/bitwise4.in",
           "bitwise/bitwise4.out"));
}

TEST(bitwise, test5) {
  ASSERT_TRUE(
      test("bitwise/bitwise.pcl",
           "bitwise/bitwise5.in",
           "bitwise/bitwise5.out"));
}

TEST(assignment_with_modify, test1) {
  ASSERT_TRUE(
      test("assignment_with_modify/assignment_with_modify.pcl",
           "assignment_with_modify/assignment_with_modify1.in",
           "assignment_with_modify/assignment_with_modify1.out"));
}

TEST(custom_base, test1) {
  ASSERT_TRUE(
      test("custom_base/custom_base.pcl",
           "custom_base/custom_base1.in",
           "custom_base/custom_base1.out"));
}

TEST(incr_decr, test1) {
  ASSERT_TRUE(
      test("incr_decr/incr_decr.pcl",
           "incr_decr/incr_decr1.in",
           "incr_decr/incr_decr1.out"));
}

TEST(else_if, test1) {
  ASSERT_TRUE(
      test("else_if/else_if.pcl",
           "else_if/else_if1.in",
           "else_if/else_if1.out"));
}

TEST(empty, test1) {
  ASSERT_TRUE(
      test("empty/empty.pcl",
           "empty/empty1.in",
           "empty/empty1.out"));
}

TEST(empty_with_semicolons, test1) {
  ASSERT_TRUE(
      test("empty_with_semicolons/empty_with_semicolons.pcl",
           "empty_with_semicolons/empty_with_semicolons1.in",
           "empty_with_semicolons/empty_with_semicolons1.out"));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
