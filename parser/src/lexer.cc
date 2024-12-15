#include "parser/lexer.hh"

namespace yy {

void PLexer::updateCurrentLocation() noexcept {
  int cur_line = lineno();

  int prev_end_col = cur_loc_.end.column;
  cur_loc_.begin.line = cur_loc_.end.line = cur_line;

  if (isEmptyLine(yytext)) {
    cur_loc_.begin.column = cur_loc_.end.column = 1;
  } else {
    cur_loc_.begin.column = prev_end_col;
    cur_loc_.end.column = cur_loc_.begin.column + yyleng;
  }
}

} // namespace yy
