/**
 * @file
 * Driver interface.
 */
#pragma once

#include <fstream>
#include <string>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

#include "pgrammar.tab.hh"
#include "lexer.hh"

namespace yy {

/**
 * Provides interface for Bison parser to communicate with lexer.
 */
class PDriver final {
 private:
  std::string input_file_name_;

  std::ifstream input_stream_;
  PLexer* plex_;

 public:
  PDriver(const std::string& input_file_name);

  /** Non-copyable. */
  PDriver(const PDriver& rhs) = delete;

  /** Non-copyable. */
  PDriver operator=(const PDriver& rhs) = delete;

  ~PDriver() { delete plex_; }

  /** The way for parser to call lexer. */
  parser::token_type yylex(parser::semantic_type* yylval,
                           parser::location_type* yylloc);

  /** Invokes Bison parser. */
  bool parse() {
    parser parser(this);
    bool res = false;
    try {
      res = !parser.parse();
    } catch (std::runtime_error& ex) {
      handleParserError(parser, ex);
    }
    return res;
  }

 private:
  /**
   * Handles exceptions which cannot be handled by parser itself, thus is an
   * implementation detail.
   */
  void handleParserError(const parser& parser,
                         const std::runtime_error& ex) const;
};

} // namespace yy
