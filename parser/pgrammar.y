%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::PDriver* driver}

%code requires
{

#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace yy {

class PDriver;

}

}

%code
{

#include "driver.hh"

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,
                         PDriver* driver);

}

}

%token
  EQUAL     "=="
  MINUS     "-"
  PLUS      "+"
  DIV       "/"
  ASTERICK  "*"
  SCOLON    ";"
  ERR

%token <int> NUMBER
%nterm <std::vector<int>> expr
%nterm <std::pair<std::vector<int>, std::vector<int>>> equals
%nterm <std::vector<std::pair<std::vector<int>, std::vector<int>>>> eqlist

%left '+' '-'

%start program

%%

program: eqlist               { driver->insert($1); }
;

eqlist: equals SCOLON eqlist  { $$ = $3; $$.push_back($1); }
      | equals SCOLON         { $$.push_back($1);          }
;

equals: expr EQUAL expr       { $$ = std::make_pair($1, $3); }
;

expr: NUMBER                  { $$.push_back($1); }
    | expr PLUS NUMBER        { $$ = $1; $$.push_back($3); }
    | expr MINUS NUMBER       { $$ = $1; $$.push_back(-$3); }
;

%%

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,
                         PDriver* driver) {
  return driver->yylex(yylval);
}

void parser::error(const std::string& e) {
  std::cerr << e;
}

}
