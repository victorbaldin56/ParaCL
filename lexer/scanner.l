%option yyclass="pcl::PLexer"
%option c++

%{

#include "lexer.hh"

%}

WS [ \t\n\v]+
OP [\+\-\*\/\=]

%%

{WS}            // all whitespace symbols are ignored in ParaCL
{OP}            { return 0; }

%%
