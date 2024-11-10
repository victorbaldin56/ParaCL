#ifndef PARACL_LEXER_LEXER_HH_
#define PARACL_LEXER_LEXER_HH_

#include <cstdlib>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

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

#endif // PARACL_LEXER_LEXER_HH_
