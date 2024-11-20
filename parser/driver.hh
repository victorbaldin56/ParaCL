#pragma once

#include <fstream>
#include <string>

#pragma once
#include <FlexLexer.h>

#include "pgrammar.tab.hh"
#include "lexer.hh"

namespace yy {

class PDriver final {
 private:
  std::string input_file_name_;

  std::ifstream input_stream_;
  FlexLexer* plex_;

 public:
  PDriver(const std::string& input_file_name);

  PDriver(const PDriver& rhs) = delete;
  PDriver operator=(const PDriver& rhs) = delete;

  ~PDriver() {
    delete plex_;
  }

  parser::token_type yylex(parser::semantic_type* yylval,
                           parser::location_type* yylloc);

  bool parse() {
    parser parser(this);
    return !parser.parse();
  }
};

} // namespace yy

