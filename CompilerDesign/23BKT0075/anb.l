%{
#include "y.tab.h"
%}

%%
a   return 'a';
b   return 'b';
[ \t\n]  ;
.   return yytext[0];
%%

int yywrap() { return 1; }
