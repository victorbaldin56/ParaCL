%language "c++"
%skeleton "lalr1.cc"

%param {yy::PDriver* driver}
%locations

%define parse.trace
%define parse.lac full

%define api.value.type variant
%define parse.error custom

%code requires
{

#define YYDEBUG 1

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

/* simple tokens */
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
  UNKNOWN
  UNKNOWN_ID

/* non-trivial operators that require precedence & associativity */
%right ASSIGN
%left OR
%left AND
%left IS_EQ IS_GE IS_GT IS_LE IS_LT IS_NE
%left ADD SUB
%left MUL DIV MOD
%left NOT

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

%nterm<ast::pIScope>
  scope
  br_stm
  op_br_stm

%%

program:     stms                           { /* nothing */ }
scope:       op_sc stms cl_sc               { /* nothing */ } /* plain scope */

br_stm:      op_br_stm stms cl_sc           { $$ = $1; }

op_br_stm:   LB                             {
                                              $$ = ast::current_scope
                                                 = ast::makeScope(ast::current_scope);
                                            }

op_sc:       LB                             {
                                              ast::pIScope tmp = ast::current_scope;
                                              ast::current_scope
                                                  = ast::makeScope(ast::current_scope);
                                              tmp->push(ast::current_scope);
                                            }

cl_sc:       RB                             {
                                              ast::current_scope
                                                  = ast::current_scope->parentScope();
                                            }

stms:        stm                            { ast::current_scope->push($1); }
           | stms stm                       { ast::current_scope->push($2); }
           | scope
           | stms scope

stm:         assign                         { $$ = $1; }
           | if                             { $$ = $1; }
           | while                          { $$ = $1; }
           | print                          { $$ = $1; }
           | scan                           { $$ = $1; }

assign:      ID ASSIGN expr SCOLON          { $$ = ast::makeAssign($1, $3); }

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
           | expr AND   expr                { $$ = ast::makeBinOp($1, ast::BinOp::kAnd , $3); }
           | expr OR    expr                { $$ = ast::makeBinOp($1, ast::BinOp::kOr  , $3); }
           | expr_un                        { $$ = $1; }

expr_un:     ADD expr_term                  { $$ = ast::makeUnOp($2, ast::UnOp::kPlus); }
           | SUB expr_term                  { $$ = ast::makeUnOp($2, ast::UnOp::kMinus); }
           | NOT expr_term                  { $$ = ast::makeUnOp($2, ast::UnOp::kNot); }
           | expr_term                      { $$ = $1; }

expr_term:   LP expr RP                     { $$ = $2; }
           | NUMBER                         { $$ = ast::makeValue($1); }
           | ID                             { $$ = ast::makeVar($1); }

if:          IF LP expr RP br_stm           { $$ = ast::makeIf($3, $5); }
           | IF LP expr RP stm              { $$ = ast::makeIf($3, $5); }

while:       WHILE LP expr RP br_stm        { $$ = ast::makeWhile($3, $5); }
           | WHILE LP expr RP stm           { $$ = ast::makeWhile($3, $5); }

print:       PRINT expr SCOLON              { $$ = ast::makePrint($2); }

scan:        ID ASSIGN SCAN SCOLON          { $$ = ast::makeScan($1); }

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

void parser::report_syntax_error(const parser::context& ctx) const {
  std::cerr << ctx.location() << ": syntax error";

  symbol_kind_type expected[symbol_kind_type::YYNTOKENS]{};
  int n = ctx.expected_tokens(expected, symbol_kind::YYNTOKENS);
  for (int i = 0; i < n; ++i) {
    std::cerr << (i == 0) ? ": expected " : " or" << symbol_name(expected[i]);
  }

  symbol_kind_type lookahead = ctx.token();
  if (lookahead != symbol_kind::S_YYEMPTY) {
    std::cerr << " before " << symbol_name(lookahead);
  }
  std::cerr << '\n';
}

}
