#ifndef PARACL_DRIVER_DRIVER_HH_
#define PARACL_DRIVER_DRIVER_HH_

#include <fstream>
#include <string>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

#include "lexer.hh"

namespace yy {

class PDriver final {
  std::string input_file_name_;

  std::ifstream input_stream_;
  yy::PLexer plex_;

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
};

} // namespace yy

#endif // PARACL_DRIVER_DRIVER_HH_
