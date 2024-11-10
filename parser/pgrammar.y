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
  SUB               "-"
  ADD               "+"
  DIV               "/"
  MUL               "*"
  MOD               "%"

  IS_EQ             "=="
  IS_GE             ">="
  IS_GT             ">"
  IS_LT             "<"
  IS_LE             "<="
  IS_NE             "!="

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
  ;

%token<int> NUMBER
%token<std::string> ID

%type<ast::INode*>
  stm
  stms
  if
  while
  print
  assign
  expr
  ;

%type<ast::IScope*>
  scope
  br_stm
  ;

%%

program:     stms                           { current_scope->calc(); }
scope:       op_sc stms cl_sc               { /* nothing */ }

op_sc:       LB                             { current_scope = ast::makeScope(current_scope); }
cl_sc:       RB                             { current_scope = current_scope->parentScope(); }

stms:        stm                            { current_scope->push($1); }
           | stms stm                       { current_scope->push($2); }

br_stm:      stm                            {
                                              $$ = ast::makeScope(current_scope);
                                              $$->push($1);
                                            }

stm:         assign                         { $$ = $1; }
           | if                             { $$ = $1; }
           | while                          { $$ = $1; }
           | print                          { $$ = $1; }

assign:      ID ASSIGN expr SCOLON          { /* TODO */ }

expr:        expr ADD   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kAdd , $3); }
             expr SUB   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kSub , $3); }
             expr MUL   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kMul , $3); }
             expr DIV   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kDiv , $3); }
             expr MOD   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kMod , $3); }
             expr IS_EQ expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsEq, $3); }
             expr IS_GE expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsGe, $3); }
             expr IS_GT expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsGt, $3); }
             expr IS_LT expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsLt, $3); }
             expr IS_LE expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsLe, $3); }
             expr IS_NE expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsNe, $3); }

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
