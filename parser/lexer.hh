/**
 * @file
 * Lexer interface.
 */
#pragma once

#include <cstdlib>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

#include "pgrammar.tab.hh"

namespace yy {

/**
 * Overrides some FlexLexer methods and adds custom ones.
 */
class PLexer final : public yyFlexLexer {
 private:
  yy::location cur_loc_;

 public:
  PLexer() = default;
  int yylex() override;

  const location& getCurrentLocation() const noexcept { return cur_loc_; }
  void updateCurrentLocation() noexcept;

  static bool isEmptyLine(const char* line) noexcept {
    char s = *line;
    return s == '\n';
  }
};

} // namespace yy
