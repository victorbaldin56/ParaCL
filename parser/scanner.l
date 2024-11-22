%option c++
%option noyywrap
%option yylineno

%option warn nodefault debug noinput
%option yyclass="yy::PLexer"

%{

#include "lexer.hh"
#include "pgrammar.tab.hh"

#define YY_USER_ACTION updateCurrentLocation();

%}

WS            [ \t\n\v]+
DIGIT         [0-9]
DIGIT1        [1-9]
ID            [a-zA-Z_][a-zA-Z0-9_]*
COMMENT       "//".*"\n"
%x IN_COMMENT

%%

{WS}              /* all whitespace symbols are ignored in ParaCL */
{COMMENT}         /* skip */
<INITIAL>{
"/*"              BEGIN(IN_COMMENT);
}
<IN_COMMENT>{
"*/"              BEGIN(INITIAL);
[^*\n]+           // eat comment in chunks
"*"               // eat the lone star
}

"+"               return yy::parser::token_type::ADD;
"-"               return yy::parser::token_type::SUB;
"*"               return yy::parser::token_type::MUL;
"/"               return yy::parser::token_type::DIV;
"%"               return yy::parser::token_type::MOD;
"="               return yy::parser::token_type::ASSIGN;

"=="              return yy::parser::token_type::IS_EQ;
">="              return yy::parser::token_type::IS_GE;
">"               return yy::parser::token_type::IS_GT;
"<"               return yy::parser::token_type::IS_LT;
"<="              return yy::parser::token_type::IS_LE;
"!="              return yy::parser::token_type::IS_NE;

"!"               return yy::parser::token_type::NOT;
"||"              return yy::parser::token_type::OR;
"&&"              return yy::parser::token_type::AND;

{DIGIT1}{DIGIT}*  return yy::parser::token_type::NUMBER;
"0"               return yy::parser::token_type::NUMBER;

"while"           return yy::parser::token_type::WHILE;
"if"              return yy::parser::token_type::IF;

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
