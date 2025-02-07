%option c++
%option noyywrap
%option yylineno

%option warn nodefault debug noinput
%option yyclass="yy::PLexer"

%{

#include "parser/lexer.hh"
#include "pgrammar.tab.hh"

#define YY_USER_ACTION updateCurrentLocation();

%}

WS            [ \t\n\v]+
OCT_DIGIT     [0-7]
HEX_DIGIT     [0-9a-fA-F]
DIGIT         [0-9]
DIGIT1        [1-9]
ID            [a-zA-Z_][a-zA-Z0-9_]*
COMMENT       "//".*"\n"
%x IN_COMMENT
splice                  (\\[[:blank:]]*\n)*

%%

{WS}              /* all whitespace symbols are ignored in ParaCL */
{COMMENT}         /* skip */

[/]{splice}[*]          BEGIN(IN_COMMENT);

<IN_COMMENT>{
  [^*\\\n]+             /* eat anything that's not a '*' or line end */
  "*"+[^*/\\\n]*        /* eat up '*'s not followed by '/'s or line end */
  [*]{splice}[/]        BEGIN(INITIAL);
  [*\\]                 /* stray '*' or backslash */
  \n                    /* Reduce the amount of work needed for yylineno */
}

"+"               return yy::parser::token_type::ADD;
"-"               return yy::parser::token_type::SUB;
"*"               return yy::parser::token_type::MUL;
"/"               return yy::parser::token_type::DIV;
"%"               return yy::parser::token_type::MOD;

"="               return yy::parser::token_type::ASSIGN;
"+="              return yy::parser::token_type::ADD_ASSIGN;
"-="              return yy::parser::token_type::SUB_ASSIGN;
"*="              return yy::parser::token_type::MUL_ASSIGN;
"/="              return yy::parser::token_type::DIV_ASSIGN;
"%="              return yy::parser::token_type::MOD_ASSIGN;
"&="              return yy::parser::token_type::BTW_AND_ASSIGN;
"|="              return yy::parser::token_type::BTW_OR_ASSIGN;
"^="              return yy::parser::token_type::XOR_ASSIGN;
"<<="             return yy::parser::token_type::SHL_ASSIGN;
">>="             return yy::parser::token_type::SHR_ASSIGN;

"=="              return yy::parser::token_type::IS_EQ;
">="              return yy::parser::token_type::IS_GE;
">"               return yy::parser::token_type::IS_GT;
"<"               return yy::parser::token_type::IS_LT;
"<="              return yy::parser::token_type::IS_LE;
"!="              return yy::parser::token_type::IS_NE;

"!"               return yy::parser::token_type::NOT;
"||"              return yy::parser::token_type::OR;
"&&"              return yy::parser::token_type::AND;

"&"               return yy::parser::token_type::BTW_AND;
"|"               return yy::parser::token_type::BTW_OR;
"^"               return yy::parser::token_type::XOR;

"~"               return yy::parser::token_type::BTW_NOT;

"<<"              return yy::parser::token_type::SHL;
">>"              return yy::parser::token_type::SHR;

"++"              return yy::parser::token_type::INCR;
"--"              return yy::parser::token_type::DECR;

{DIGIT1}{DIGIT}*  return yy::parser::token_type::NUMBER;
"0"               return yy::parser::token_type::NUMBER;
"0x"{HEX_DIGIT}*  return yy::parser::token_type::NUMBER;  /* hexadecimal */
"0X"{HEX_DIGIT}*  return yy::parser::token_type::NUMBER;  /* hexadecimal */
"0"{OCT_DIGIT}*   return yy::parser::token_type::NUMBER;  /* octal */

"while"           return yy::parser::token_type::WHILE;
"if"              return yy::parser::token_type::IF;
"else"            return yy::parser::token_type::ELSE;

";"               return yy::parser::token_type::SCOLON;

"?"               return yy::parser::token_type::SCAN;
"print"           return yy::parser::token_type::PRINT;

"{"               return yy::parser::token_type::LB;
"}"               return yy::parser::token_type::RB;
"("               return yy::parser::token_type::LP;
")"               return yy::parser::token_type::RP;

{ID}              return yy::parser::token_type::ID;

.                 return yy::parser::token_type::UNKNOWN;

%%
