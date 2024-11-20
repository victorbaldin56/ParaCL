%language "c++"
%skeleton "lalr1.cc"

%param {yy::PDriver* driver}
%locations

%define parse.trace
%define parse.lac full

%define api.value.type variant
//%define parse.error custom

%code requires
{

//#define YYDEBUG 1

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "inode.hh"

namespace yy {

class PDriver;

} // namespace yy

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

// simple tokens
%token
  SCOLON
  IF
  WHILE
  SCAN
  PRINT
  LB
  RB
  LP
  RP

// non-trivial operators that require precedence & associativity
%right ASSIGN
%left IS_EQ IS_GE IS_GT IS_LE IS_LT IS_NE
%left ADD SUB
%left MUL DIV MOD

%token<int> NUMBER
%token<std::string> ID

%nterm<ast::pINode>
  stm
  stms
  if
  while
  print
  scan
  assign
  expr
  expr_un
  expr_term
  var

%nterm<ast::pIScope>
  scope
  // br_stm

%%

program:     stms                           { ast::current_scope->calc(); }
scope:       op_sc stms cl_sc               { /* nothing */ }

op_sc:       LB                             { ast::current_scope = ast::makeScope(ast::current_scope); }
cl_sc:       RB                             { ast::current_scope = ast::current_scope->parentScope(); }

stms:        stm                            { ast::current_scope->push($1); }
           | stms stm                       { ast::current_scope->push($2); }

/* br_stm:      stm                            {
                                              $$ = ast::makeScope(ast::current_scope);
                                              $$->push($1);
                                            } */

stm:         assign                         { $$ = $1; }
           | if                             { $$ = $1; }
           | while                          { $$ = $1; }
           | print                          { $$ = $1; }
           | scan                           { $$ = $1; }

assign:      var ASSIGN expr SCOLON         { $$ = ast::makeAssign($1, $3); }

expr:        expr ADD   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kAdd , $3); }
           | expr SUB   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kSub , $3); }
           | expr MUL   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kMul , $3); }
           | expr DIV   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kDiv , $3); }
           | expr MOD   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kMod , $3); }
           | expr IS_EQ expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsEq, $3); }
           | expr IS_GE expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsGe, $3); }
           | expr IS_GT expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsGt, $3); }
           | expr IS_LT expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsLt, $3); }
           | expr IS_LE expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsLe, $3); }
           | expr IS_NE expr                { $$ = ast::makeBinOp($1, ast::BinOp::kIsNe, $3); }
           | expr_un                        { $$ = $1; }

expr_un:     ADD expr_term                  { $$ = ast::makeUnOp($2, ast::UnOp::kPlus); }
           | SUB expr_term                  { $$ = ast::makeUnOp($2, ast::UnOp::kMinus); }
           | expr_term

expr_term:   NUMBER                         { $$ = ast::makeValue($1); }
           | ID                             { $$ = ast::makeVar($1); }

if:          IF LP expr RP scope            { $$ = ast::makeIf($3, $5); }
           | IF LP expr RP expr             { $$ = ast::makeIf($3, $5); }

while:       WHILE LP expr RP scope         { $$ = ast::makeWhile($3, $5); }
           | WHILE LP expr RP expr          { $$ = ast::makeWhile($3, $5); }

print:       PRINT expr SCOLON              { $$ = ast::makePrint($2); }

scan:        var ASSIGN SCAN SCOLON         { $$ = ast::makeScan($1); }

var:         ID                             { $$ = ast::makeVar($1); }

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
