#include "driver.hh"

#include <stdexcept>

namespace yy {

PDriver::PDriver(const std::string& input_file_name)
    : input_file_name_(input_file_name), plex_(new PLexer) {
  input_stream_.open(input_file_name, std::ios_base::in);

  if (!input_stream_.is_open()) {
    std::string what = "Failed to open file " + input_file_name_;
    throw std::runtime_error(what);
  }

  plex_->switch_streams(input_stream_, std::cout);
}

parser::token_type PDriver::yylex(parser::semantic_type* yylval,
                                  parser::location_type* yylloc) {
  parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());
  const char* cur_text = plex_->YYText();

  switch (tt) {
  case parser::token_type::NUMBER:
    yylval->emplace<int>(std::stoi(cur_text));
    break;
  case parser::token_type::ID:
    yylval->emplace<std::string>(cur_text);
    break;
  case parser::token_type::UNKNOWN:
    std::cerr << "Unknown token \"" << cur_text << "\"\n";
    break;
  default:
    break;
  }
  *yylloc = plex_->getCurrentLocation();
  return tt;
}

void PDriver::reportSyntaxError(const parser::context& ctx) const {
  std::cerr << ctx.location() << ": syntax error";
}

} // namespace yy
