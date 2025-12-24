%{
//23BKT0075 Mohit Talgotra
#include "y.tab.h"
#include <string.h>
%}

%%
[a-zA-Z]+ { yylval.str = strdup(yytext); return WORD; }
\n { return 0; }
. ;
%%

int yywrap()
{
    return 1;
}