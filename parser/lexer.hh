#pragma once

#include <cstdlib>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

#include "pgrammar.tab.hh"

namespace yy {

class PLexer final : public yyFlexLexer {
 private:
  yy::location cur_loc_;
  int cur_line_;

 public:
  PLexer() = default;
  PLexer(const PLexer& rhs) = delete;
  PLexer& operator=(const PLexer& rhs) = delete;

  int yylex() override;

  const location& getCurrentLocation() const noexcept { return cur_loc_; }
  void updateCurrentLocation();

  static bool isEmptyLine(const char* line) noexcept;
};

} // namespace yy
