%{
#include "y.tab.h"
%}

%%
"("     { return '('; }
")"     { return ')'; }
\n      { return 0; }
.       { /* ignore other characters */ }
%%
int yywrap()
{
    return 1;
}