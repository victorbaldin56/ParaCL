%option c++

WS [ \t\n\v]+
OP [\+\-\*\/\=]

%%

{WS}            // all whitespace symbols are ignored in ParaCL
{OP}
