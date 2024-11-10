%option yyclass="yy::PLexer"
%option c++

%option noyywrap
%option yylineno

%{

#include "lexer.hh"
#include "pgrammar.tab.hh"

%}

WS            [ \t\n\v]+
DIGIT         [0-9]
DIGIT1        [1-9]
ID            [a-zA-Z][a-zA-Z0-9_]*

%%

{WS}              // all whitespace symbols are ignored in ParaCL
"+"               return yy::parser::token_type::PLUS;
"-"               return yy::parser::token_type::MINUS;
"*"               return yy::parser::token_type::MUL;
"/"               return yy::parser::token_type::DIV;
"%"               return yy::parser::token_type::MOD;

"=="              return yy::parser::token_type::IS_EQ;
">="              return yy::parser::token_type::IS_GE;
">"               return yy::parser::token_type::IS_GT;
"<"               return yy::parser::token_type::IS_LT;
"<="              return yy::parser::token_type::IS_LE;

"="               return yy::parser::token_type::ASSIGN;

{DIGIT1}{DIGIT}*  return yy::parser::token_type::NUMBER;

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

%%
