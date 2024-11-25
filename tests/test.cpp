#include "driver.hh"
#include <algorithm>
#include <exception>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iterator>
#include <string>

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

  std::ifstream in(in_file);
  std::streambuf *cinbuf = std::cin.rdbuf();
  std::cin.rdbuf(in.rdbuf());

  std::ofstream out("buf.txt");
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());

  yy::PDriver driver(pcl_file);
  ast::current_scope = ast::makeScope();

  if (!driver.parse()) {
    throw std::runtime_error("Something went wrong.");
  }

  ast::current_scope->calc();

  std::cin.rdbuf(cinbuf);
  std::cout.rdbuf(coutbuf);

  close_files(in, out);

  return compare_files("buf.txt", out_file);
}

TEST(is_prime, test1) {
  ASSERT_TRUE(test("../../tests/is_prime/is_prime.pcl",
                   "../../tests/is_prime/is_prime1.in",
                   "../../tests/is_prime/is_prime1.out"));
}

TEST(is_prime, test2) {
  ASSERT_TRUE(test("../../tests/is_prime/is_prime.pcl",
                   "../../tests/is_prime/is_prime2.in",
                   "../../tests/is_prime/is_prime2.out"));
}

TEST(other, test1) {
  ASSERT_TRUE(test("../../tests/other/other.pcl",
                   "../../tests/other/other.in",
                   "../../tests/other/other.out"));
}

TEST(fibs, test1) {
  ASSERT_TRUE(test("../../tests/fibs/fibs.pcl",
                   "../../tests/fibs/fibs1.in",
                   "../../tests/fibs/fibs1.out"));
}

TEST(fibs, test2) {
  ASSERT_TRUE(test("../../tests/fibs/fibs.pcl",
                   "../../tests/fibs/fibs2.in",
                   "../../tests/fibs/fibs2.out"));
}

TEST(fact, test1) {
  ASSERT_TRUE(test("../../tests/fact/fact.pcl",
                   "../../tests/fact/fact1.in",
                   "../../tests/fact/fact1.out"));
}

TEST(braces, test1) {
  ASSERT_TRUE(test("../../tests/braces/braces.pcl",
                   "../../tests/braces/braces1.in",
                   "../../tests/braces/braces1.out"));
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}