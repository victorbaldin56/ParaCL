%language "c++"
%skeleton "lalr1.cc"

%param {yy::PDriver* driver}
%locations

%define parse.lac full

%define api.value.type variant
%define parse.error custom

%code requires
{

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "ast/inode.hh"

namespace yy {

class PDriver;

} // namespace yy

}

%code
{

#include "parser/driver.hh"

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

%precedence LOWER
%precedence ';'

%nonassoc XIF
%nonassoc ELSE
%nonassoc INCR DECR

/* non-trivial operators that require precedence & associativity */
%right ASSIGN
       ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
       BTW_AND_ASSIGN BTW_OR_ASSIGN XOR_ASSIGN SHL_ASSIGN SHR_ASSIGN

%left OR
%left AND
%left IS_EQ IS_GE IS_GT IS_LE IS_LT IS_NE
%left ADD SUB
%left MUL DIV MOD
%left SHL SHR
%left BTW_OR
%left XOR
%left BTW_AND
%left NOT
%left BTW_NOT

%token<int> NUMBER
%token<std::string> ID

%nterm<ast::pINode>
  stm
  if
  while
  print
  expr
  expr_un
  expr_term
  br_stm

%nterm<ast::pIScope>
  stms
  scope
  op_br_stm

%%

program:     stms                             { /* nothing */ }
scope:       op_sc stms cl_sc                 { /* nothing */ } /* plain scope */

br_stm:      op_br_stm stms cl_sc             { $$ = $1; }
           | stm                              { $$ = $1; }

op_br_stm:   LB                               {
                                                $$ = ast::current_scope
                                                   = ast::makeScope(ast::current_scope);
                                              }

op_sc:       LB                               {
                                                ast::pIScope tmp = ast::current_scope;
                                                ast::current_scope
                                                    = ast::makeScope(ast::current_scope);
                                                tmp->push(ast::current_scope);
                                              }

cl_sc:       RB                               {
                                                ast::current_scope
                                                    = ast::current_scope->parentScope();
                                              }

stms:        stms stm                         { if ($2) ast::current_scope->push($2); }
           | stms scope
           | %empty                           { $$ = nullptr; } %prec LOWER;

stm:         if                               { $$ = $1; }
           | while                            { $$ = $1; }
           | print                            { $$ = $1; }
           | expr SCOLON                      { $$ = $1; }
           | SCOLON                           { $$ = nullptr; }

expr:        expr ADD            expr         { $$ = ast::makeBinOp($1, ast::BinOp::kAdd   , $3); }
           | expr SUB            expr         { $$ = ast::makeBinOp($1, ast::BinOp::kSub   , $3); }
           | expr MUL            expr         { $$ = ast::makeBinOp($1, ast::BinOp::kMul   , $3); }
           | expr DIV            expr         { $$ = ast::makeBinOp($1, ast::BinOp::kDiv   , $3); }
           | expr MOD            expr         { $$ = ast::makeBinOp($1, ast::BinOp::kMod   , $3); }
           | expr IS_EQ          expr         { $$ = ast::makeBinOp($1, ast::BinOp::kIsEq  , $3); }
           | expr IS_GE          expr         { $$ = ast::makeBinOp($1, ast::BinOp::kIsGe  , $3); }
           | expr IS_GT          expr         { $$ = ast::makeBinOp($1, ast::BinOp::kIsGt  , $3); }
           | expr IS_LT          expr         { $$ = ast::makeBinOp($1, ast::BinOp::kIsLt  , $3); }
           | expr IS_LE          expr         { $$ = ast::makeBinOp($1, ast::BinOp::kIsLe  , $3); }
           | expr IS_NE          expr         { $$ = ast::makeBinOp($1, ast::BinOp::kIsNe  , $3); }
           | expr AND            expr         { $$ = ast::makeBinOp($1, ast::BinOp::kAnd   , $3); }
           | expr OR             expr         { $$ = ast::makeBinOp($1, ast::BinOp::kOr    , $3); }
           | expr BTW_AND        expr         { $$ = ast::makeBinOp($1, ast::BinOp::kBtwAnd, $3); }
           | expr BTW_OR         expr         { $$ = ast::makeBinOp($1, ast::BinOp::kBtwOr , $3); }
           | expr XOR            expr         { $$ = ast::makeBinOp($1, ast::BinOp::kXor   , $3); }
           | expr SHL            expr         { $$ = ast::makeBinOp($1, ast::BinOp::kShl   , $3); }
           | expr SHR            expr         { $$ = ast::makeBinOp($1, ast::BinOp::kShr   , $3); }
           | ID   ASSIGN         expr         { $$ = ast::makeAssign($1, $3); }
           | ID   ADD_ASSIGN     expr         { $$ = ast::makeAssign($1, ast::makeBinOp(ast::makeVar($1), ast::BinOp::kAdd   , $3)); }
           | ID   SUB_ASSIGN     expr         { $$ = ast::makeAssign($1, ast::makeBinOp(ast::makeVar($1), ast::BinOp::kSub   , $3)); }
           | ID   MUL_ASSIGN     expr         { $$ = ast::makeAssign($1, ast::makeBinOp(ast::makeVar($1), ast::BinOp::kMul   , $3)); }
           | ID   DIV_ASSIGN     expr         { $$ = ast::makeAssign($1, ast::makeBinOp(ast::makeVar($1), ast::BinOp::kDiv   , $3)); }
           | ID   MOD_ASSIGN     expr         { $$ = ast::makeAssign($1, ast::makeBinOp(ast::makeVar($1), ast::BinOp::kMod   , $3)); }
           | ID   BTW_AND_ASSIGN expr         { $$ = ast::makeAssign($1, ast::makeBinOp(ast::makeVar($1), ast::BinOp::kBtwAnd, $3)); }
           | ID   BTW_OR_ASSIGN  expr         { $$ = ast::makeAssign($1, ast::makeBinOp(ast::makeVar($1), ast::BinOp::kBtwOr , $3)); }
           | ID   XOR_ASSIGN     expr         { $$ = ast::makeAssign($1, ast::makeBinOp(ast::makeVar($1), ast::BinOp::kXor   , $3)); }
           | ID   SHL_ASSIGN     expr         { $$ = ast::makeAssign($1, ast::makeBinOp(ast::makeVar($1), ast::BinOp::kShl   , $3)); }
           | ID   SHR_ASSIGN     expr         { $$ = ast::makeAssign($1, ast::makeBinOp(ast::makeVar($1), ast::BinOp::kShr   , $3)); }
           | expr_un                          { $$ = $1; }

expr_un:     ADD expr_term                    { $$ = ast::makeUnOp($2, ast::UnOp::kPlus); }
           | SUB expr_term                    { $$ = ast::makeUnOp($2, ast::UnOp::kMinus); }
           | NOT expr_term                    { $$ = ast::makeUnOp($2, ast::UnOp::kNot); }
           | BTW_NOT expr_term                { $$ = ast::makeUnOp($2, ast::UnOp::kBtwNot); }
           | INCR ID[e]                       { $$ = ast::makeUnOp(ast::makeVar($e), ast::UnOp::kPreIncr); }
           | ID[e] INCR                       { $$ = ast::makeUnOp(ast::makeVar($e), ast::UnOp::kPostIncr); }
           | DECR ID[e]                       { $$ = ast::makeUnOp(ast::makeVar($e), ast::UnOp::kPreDecr); }
           | ID[e] DECR                       { $$ = ast::makeUnOp(ast::makeVar($e), ast::UnOp::kPostDecr); }
           | expr_term                        { $$ = $1; }

expr_term:   LP expr RP                       { $$ = $2; }
           | NUMBER                           { $$ = ast::makeValue($1); }
           | ID                               { $$ = ast::makeVar($1); }
           | SCAN                             { $$ = ast::makeScan(); }

if:          IF LP expr[e] RP
               br_stm[s] %prec XIF            { $$ = ast::makeIf($e, $s); }
           | IF LP expr[e] RP
               br_stm[s1]
             ELSE
               br_stm[s2]                     { $$ = ast::makeIf($e, $s1, $s2); }

while:       WHILE LP expr RP br_stm          { $$ = ast::makeWhile($3, $5); }

print:       PRINT expr SCOLON                { $$ = ast::makePrint($2); }

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
  const location& loc = ctx.location();
  driver->reportErrorAtLocation(loc);
  std::cerr << "unexpected token" << std::endl;

  std::cerr << std::endl;
  driver->printErroneousLine(loc);
}

}
