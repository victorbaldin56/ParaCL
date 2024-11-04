#ifndef PARACL_LEXER_LEXER_HH_
#define PARACL_LEXER_LEXER_HH_

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif // yyFlexLexer

namespace pcl {

class PLexer : public yyFlexLexer {
 public:
  int yylex() override;
  int yywrap() override;
};

}

#endif // PARACL_LEXER_LEXER_HH_
