#pragma once

#include <cstdlib>

#pragma once
#include <FlexLexer.h>

#include "pgrammar.tab.hh"

namespace yy {

class PLexer final : public yyFlexLexer {
 public:
  PLexer() = default;

  PLexer(const PLexer& rhs) = delete;
  PLexer& operator=(const PLexer& rhs) = delete;

  int yylex() override;
};

}

