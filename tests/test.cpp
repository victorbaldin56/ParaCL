#include <algorithm>
#include <boost/process.hpp>
#include <exception>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iterator>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
namespace bp = boost::process;

const std::string TEST_DIR = std::string(TEST_DATA_DIR) + "/";
const std::string PCL_BINARY_PATH = CMAKE_BINARY_DIR + std::string("/pcl");

struct test_data {
  std::string pcl;
  std::string in;
  std::string out;
};

void PrintTo(const test_data& data, std::ostream* os) {
  *os << "pcl: " << data.pcl << ", in: " << data.in << ", out: " << data.out;
}

using all_test_data = std::vector<test_data>;

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

template <typename Stream>
std::stringstream stream_to_stringstream(Stream &stream) {
  std::stringstream content;
  std::string buf;

  while (std::getline(stream, buf)) {
    content << buf << std::endl;
  }

  return content;
}

bool test(const test_data &data) {
  std::ifstream test_in(data.in);
  std::ifstream test_out(data.out);

  bp::opstream in;
  bp::ipstream out;
  bp::ipstream err;

  try {
    bp::child pcl_run(PCL_BINARY_PATH, data.pcl,
                      bp::std_in<in, bp::std_out> out, bp::std_err > err);

    std::string buf;

    while (std::getline(test_in, buf)) {
      in << buf << std::endl;
    }
    in.close();

    std::string error_message = stream_to_stringstream(err).str();
    if (!error_message.empty()) {
      std::cerr << "Test error: " << error_message << std::endl;
    }

    pcl_run.wait();

    std::string out_string = stream_to_stringstream(test_out).str();
    std::string answer_string = stream_to_stringstream(out).str();

    close_files(test_in, test_out);

    return out_string == answer_string;

  } catch (const std::exception &err) {
    std::cerr << "Exception: " << err.what() << std::endl;
    close_files(test_in, test_out);
    return false;
  }
}

class PclTest : public ::testing::TestWithParam<test_data> {};

TEST_P(PclTest, EteTests) {
  test_data test_files = GetParam();

  ASSERT_TRUE(test(test_files));
}

INSTANTIATE_TEST_SUITE_P(AllPclFiles, PclTest,
                         ::testing::ValuesIn(find_test_files(TEST_DIR)));

int main(int argc, char *argv[]) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
