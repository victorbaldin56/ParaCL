#ifndef PARACL_DRIVER_DRIVER_HH_
#define PARACL_DRIVER_DRIVER_HH_

#include <fstream>
#include <string>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

#include "pgrammar.tab.hh"

namespace yy {

class PDriver final {
 private:
  std::string input_file_name_;

  std::ifstream input_stream_;
  FlexLexer* plex_;

  bool valid_; // "bad bit"

 public:
  PDriver(const std::string& input_file_name)
      : input_file_name_(input_file_name),
        input_stream_(input_file_name),
        valid_(true) {
    if (!input_stream_.is_open()) {
      valid_ = false;
      std::cerr << "Failed to open file " << input_file_name_ << "\n";
    }
  }

  // Methods for checking PDriver validity.
  bool valid() const { return valid_; }
  operator bool() const { return valid(); }

 public:
  parser::token_type yylex(parser::semantic_type* yylval) {
    parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());
    return tt;
  }

  bool parse() {
    parser parser(this);
    return !parser.parse();
  }

 public:
  void insert(std::vector<std::pair<std::vector<int>, std::vector<int>>>) {

  }
};

} // namespace yy

#endif // PARACL_DRIVER_DRIVER_HH_
