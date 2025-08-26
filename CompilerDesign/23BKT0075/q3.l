%{
#include <stdio.h>

int tokens = 0;
%}

%%

[ \t\r\n]+                         ;

[A-Za-z_][A-Za-z0-9_]*             { tokens++; }

[0-9]+                             { tokens++; }

\"([^\"\\]|\\.)*\"                 { tokens++; }

\'([^\'\\]|\\.)\'                  { tokens++; }

[+\-*/%=;:.,(){}[\]<>!]            { tokens++; }

.                                  { tokens++; }

%%

int yywrap()
{
    return 1;
}

int main(int argc, char*argv[])
{
    if(argc > 1)
    {
        yyin = fopen(argv[1], "r");
    }
    yylex();
    printf("%d\n", tokens);
    return 0;
}
