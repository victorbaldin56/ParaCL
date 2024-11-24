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
  std::unique_ptr<PLexer> plex_;
  std::vector<std::string> lines_of_code_; ///< for verbose error reporting

 public:
  PDriver(const std::string& input_file_name);

  /** Non-copyable. */
  PDriver(const PDriver& rhs) = delete;

  /** Non-copyable. */
  PDriver operator=(const PDriver& rhs) = delete;

  PDriver(PDriver&& rhs) = default;
  PDriver& operator=(PDriver&& rhs) = default;

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
    std::cerr << loc << ": error: ";
  }

  void printErroneousLine(const location& loc) const {
    int line_num = loc.begin.line;
    std::cerr << "  " << line_num << " | " << lines_of_code_[line_num - 1]
              << '\n';
    // TODO: внизу написать указатель на конкретную позицию в строке где ошибка
  }

 private:
  /** Handles exceptions from AST construction stage. */
  void reportAstError(const parser& parser,
                      const std::runtime_error& ex) const;
};

} // namespace yy
