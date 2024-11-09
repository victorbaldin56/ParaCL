%option yyclass="yy::PLexer"
%option c++

%{

#include "lexer.hh"
#include "pgrammar.tab.hh"

%}

WS      [ \t\n\v]+
DIGIT   [0-9]
DIGIT1  [1-9]

%%

{WS}              // all whitespace symbols are ignored in ParaCL
"+"               return yy::parser::token_type::PLUS;
"-"               return yy::parser::token_type::MINUS;
"*"               return yy::parser::token_type::ASTERICK;
"/"               return yy::parser::token_type::DIV;
"=="              return yy::parser::token_type::EQUAL;
";"               return yy::parser::token_type::SCOLON;
{DIGIT1}{DIGIT}*  return yy::parser::token_type::NUMBER;
"while"           return yy::parser::token_type::WHILE;
"if"              return yy::parser::token_type::IF;
"="               return yy::parser::token_type::ASSIGNMENT;
"?"               return yy::parser::token_type::INPUT;
"{"               return yy::parser::token_type::OPENING_BRACKET;
"}"               return yy::parser::token_type::CLOSING_BRACKET;

%%
