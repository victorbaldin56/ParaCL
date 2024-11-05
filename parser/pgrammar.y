%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::PDriver* driver}

%code requires
{
#include <iostream>
#include <string>

namespace yy {
  class PDriver;
}

%code
{
#include "driver.hh"

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,
                         PDriver* driver);

}

}

}
