#pragma once

#include <fstream>
#include <string>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

#include "pgrammar.tab.hh"
#include "lexer.hh"

#define PARACL_LOG(s, ...) \
  fprintf(stderr, "[%s:%d] " s, __FILE__, __LINE__, __VA_ARGS__)

#define ENABLE_PARACL_TRACE

#ifdef ENABLE_PARACL_TRACE
#define PARACL_TRACE(s, ...) PARACL_LOG(s, __VA_ARGS__)
#else
#define PARACL_TRACE(s, ...)
#endif // ENABLE_PARACL_TRACE

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
