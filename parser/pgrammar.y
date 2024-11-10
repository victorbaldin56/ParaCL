%language "c++"
%skeleton "lalr1.cc"

%param {yy::PDriver* driver}
%locations

%defines
%define api.value.type variant

%code requires
{

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "inode.hh"

namespace yy {

class PDriver;

}

}

%code
{

#include "driver.hh"

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,
                         parser::location_type* yylloc,
                         PDriver* driver);

}

}

%token
  MINUS             "-"
  PLUS              "+"
  DIV               "/"
  MUL          "*"
  MOD           "%"

  IS_EQ             "=="
  IS_GE             ">="
  IS_GT             ">"
  IS_LT             "<"
  IS_LE             "<="

  ASSIGN            "="

  SCOLON            ";"
  IF                "if"
  WHILE             "while"

  SCAN              "?"
  PRINT             "print"

  LB                "{"
  RB                "}"
  LP                "("
  RP                ")"

%token<int> NUMBER
%token<std::string> ID

%nterm<ast::IScope*>
  scope
  br_scope
  op_br_sc
  ;

%nterm<ast::IScope*> br_stm

%nterm<ast::INode*>
  stm
  stms
  ;

%nterm<ast::INode*>
  if
  while
  print
  assign
  ;

%nterm<ast::INode*>
  expr
  expr_un
  expr_term
  ;


%start program

%%

program:     stms                           { current_scope->calc(); }
scope:       op_sc stms cl_sc               { /* nothing */ }

op_sc:       LB                             { /* TODO */ }
cl_sc:       RB                             { current_scope = current_scope->parentScope(); }

stms:        stm                            { current_scope->push($1); }
           | stms stm                       { current_scope->push($2); }

stm:         assign                         { $$ = $1; }
           | if                             { $$ = $1; }
           | while                          { $$ = $1; }
           | print                          { $$ = $1; }

assign:      ID ASSIGN expr SCOLON          { /* TODO */ }

expr:        /* TODO */                     { /* TODO */ }

if:          /* TODO */                     { /* TODO */ }

while:       /* TODO */                     { /* TODO */ }

print:       PRINT expr SCOLON              { /* TODO */ }



%%

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,
                         parser::location_type* yylloc,
                         PDriver* driver) {
  return driver->yylex(yylval, yylloc);
}

void parser::error(const parser::location_type& location,
                   const std::string& e) {
  std::cerr << e << " in: " << location << "\n";
}

}
