#include "parser/driver.hh"
#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iterator>
#include <string>

namespace fs = std::filesystem;
using test_data = std::vector<std::string>;
using all_test_data = std::vector<test_data>;

const std::string TEST_DIR = std::string(TEST_DATA_DIR) + "/";

all_test_data find_test_files(const std::string &directory) {
  all_test_data tests;

  for (auto &&src : fs::recursive_directory_iterator(directory)) {
    if (src.path().extension() == ".pcl" &&
        src.path().stem().string().find("invalid") == std::string::npos) {

      std::string src_name = src.path().stem().string();

      for (auto &&test : fs::directory_iterator(src.path().parent_path())) {
        std::string file_name = test.path().stem().string();
        std::string ext = test.path().extension().string();

        if (file_name.find(src_name) == 0) {
          if (ext == ".in") {
            std::string in_file = test.path().string();
            std::string out_file =
                in_file.substr(0, in_file.find_last_of('.')) + ".out";

            if (fs::exists(out_file)) {
              tests.push_back({src.path().string(), in_file, out_file});
            }
          }
        }
      }
    }
  }

  return tests;
}

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

  bool result = compare_files("buf.txt", out_file);
  fs::remove("buf.txt");

  return result;
}

class PclTest : public ::testing::TestWithParam<test_data> {};

TEST_P(PclTest, EteTests) {
  test_data test_files = GetParam();

  ASSERT_TRUE(test(test_files[0], test_files[1], test_files[2]));
}

INSTANTIATE_TEST_SUITE_P(AllPclFiles, PclTest,
                         ::testing::ValuesIn(find_test_files(TEST_DIR)));

int main(int argc, char *argv[]) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
