%{
//23BKT0075 Mohit Talgotra
#include "y.tab.h"
#include <string.h>
%}

%%
[0-9]+ { yylval.str = strdup(yytext); return NUM; }
\n { return 0; }
. ;
%%

int yywrap()
{
    return 1;
}