%{ 
#include "validator.tab.h" 
%} 
%% 
[a-zA-Z_][a-zA-Z0-9_]*      {return ID;} 
[0-9]+(\.[0-9]+)?           {return NUMBER;} 
=                           {return ASSIGN;} 
[+\-*/]                     {return OPERATOR;} 
\(                          {return LPAREN;} 
\)                          {return RPAREN;} 
[ \t\n]                     ; 
.                           {return yytext[0];} 
%% 
int yywrap() { 
    return 1; 
} 
