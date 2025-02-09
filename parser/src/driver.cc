#include "parser/driver.hh"

#include <stdexcept>

namespace yy {

PDriver::PDriver(const std::string& input_file_name)
    : input_file_name_(input_file_name) {
  input_stream_.open(input_file_name, std::ios_base::in);

  if (!input_stream_.is_open()) {
    std::string what = "Failed to open file " + input_file_name_;
    throw std::runtime_error(what);
  }

  while (!input_stream_.eof()) {
    std::string tmp;
    std::getline(input_stream_, tmp);
    lines_of_code_.push_back(std::move(tmp));
  }
  input_stream_.clear();
  input_stream_.seekg(std::ios::beg);
  plex_.switch_streams(input_stream_, std::cout);
}

parser::token_type PDriver::yylex(parser::semantic_type* yylval,
                                  parser::location_type* yylloc) {
  parser::token_type tt = static_cast<parser::token_type>(plex_.yylex());
  const char* cur_text = plex_.YYText();

  switch (tt) {
  case parser::token_type::NUMBER:
    try {
      yylval->emplace<int>(std::stol(cur_text, nullptr, 0));
    } catch (std::out_of_range& ex) {
      throw std::out_of_range("integral constant out of range");
    }
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
  *yylloc = plex_.getCurrentLocation();
  return tt;
}

void PDriver::printErroneousLine(const location& loc) const {
  int line_num = loc.begin.line;
  std::cerr << std::right << std::setw(9) << line_num;
  std::cerr << " | ";
  printUnderlinedLineOfCode(lines_of_code_[line_num - 1], loc);
  std::cerr << "          | ";

  for (int i = 0; i < loc.begin.column - 1; ++i) {
    std::cerr << ' '; // padding
  }

  std::cerr << ctty::setAttr(ctty::Attribute::kBold, ctty::Color::kRed);
  std::cerr << '^'; // 'pointer' to the error
  for (int i = 0; i < loc.end.column - loc.begin.column - 1; ++i) {
    std::cerr << '~'; // to underline an error
  }
  std::cerr << ctty::resetAttr() << '\n';
}

void PDriver::reportAnyError(const parser& parser,
                             const std::exception& ex) const {
  const location& loc = plex_.getCurrentLocation();
  reportErrorAtLocation(loc);

  std::cerr << ex.what() << '\n';
  printErroneousLine(loc);
}

void PDriver::printUnderlinedLineOfCode(const std::string& line,
                                        const location& loc) {
  int begin = loc.begin.column - 1;
  int end = loc.end.column - 1;
  std::cerr << line.substr(0, begin)
            << ctty::setAttr(ctty::Attribute::kBold, ctty::Color::kRed)
            << line.substr(begin, end - begin)
            << ctty::resetAttr()
            << line.substr(end) << '\n';
}

} // namespace yy
