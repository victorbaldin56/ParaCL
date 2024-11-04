#ifndef PARACL_LEXER_LEXER_HH_
#define PARACL_LEXER_LEXER_HH_

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

namespace yy {

class PLexer : public yyFlexLexer {
 public:
  int yylex() override;
};

}

#endif // PARACL_LEXER_LEXER_HH_
