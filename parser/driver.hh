/**
 * @file
 * Driver interface.
 */
#pragma once

#include <fstream>
#include <iomanip>
#include <string>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

#include "color_output.hh"
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
  PLexer plex_;
  std::vector<std::string> lines_of_code_; ///< for verbose error reporting

 public:
  PDriver(const std::string& input_file_name);

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
      reportAstError(parser, ex);
    }
    return res;
  }

  void reportErrorAtLocation(const location& loc) const {
    std::cerr << input_file_name_ << ':' << loc << ": "
              << ctty::setAttr(ctty::Attribute::kBold, ctty::Color::kRed)
              << "error: " << ctty::resetAttr();
  }

  /** Prints the line in which an error occurred with a pointer to error. */
  void printErroneousLine(const location& loc) const;

 private:
  /** Handles exceptions from AST construction stage. */
  void reportAstError(const parser& parser,
                      const std::runtime_error& ex) const;
};

} // namespace yy
