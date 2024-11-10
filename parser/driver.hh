#ifndef PARACL_DRIVER_DRIVER_HH_
#define PARACL_DRIVER_DRIVER_HH_

#include <fstream>
#include <string>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

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

 public:
  parser::token_type yylex(parser::semantic_type* yylval,
                           parser::location_type* yylloc) {
    parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());
    return tt;
  }

  bool parse() {
    parser parser(this);
    return !parser.parse();
  }
};

} // namespace yy

#endif // PARACL_DRIVER_DRIVER_HH_
