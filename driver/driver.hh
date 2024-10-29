#ifndef PARACL_DRIVER_DRIVER_HH_
#define PARACL_DRIVER_DRIVER_HH_

#include <fstream>
#include <string>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

#include "lexer.hh"

namespace pcl {

class Driver final {
  std::string input_file_name_;

  std::ifstream input_stream_;

 public:
  Driver(const std::string& input_file_name)
    : input_file_name_(input_file_name) {}
};

} // namespace pcl

#endif // PARACL_DRIVER_DRIVER_HH_
