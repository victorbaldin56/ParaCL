#include "lexer.hh"

namespace yy {

void PLexer::updateCurrentLocation() {
  int cur_line = lineno();

  int prev_end = cur_loc_.end.column;
  cur_loc_.begin.line = cur_loc_.end.line = cur_line;

  if (isEmptyLine(yytext)) {
    cur_loc_.begin.column = cur_loc_.end.column = 1;
  } else {
    cur_loc_.begin.column = prev_end;
    cur_loc_.end.column = cur_loc_.begin.column + yyleng;
  }
  cur_line_ = cur_line;
}

bool PLexer::isEmptyLine(const char* line) noexcept {
  char sym = 0;
  for (const char* p = line; (sym = *p) != '\0'; ++p) {
    if (!std::isspace(sym)) {
      return false;
    }
  }
  return true;
}

} // namespace yy
