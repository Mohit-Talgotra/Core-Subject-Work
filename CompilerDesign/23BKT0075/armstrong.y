%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int yylex();
int yyerror(char *s);
%}

%union
{
    char *str;
}

%token <str> NUM

%%
S :
NUM
{
    int n = atoi($1);
    int t = n, s = 0, d = 0;
    while(t)
    {
        d++;
        t /= 10;
    }
    t = n;
    while(t)
    {
        int r = t % 10;
        s += pow(r, d);
        t /= 10;
    }
    if(s == n)
        printf("Armstrong Number\n");
    else
        printf("Not Armstrong Number\n");
}
;
%%

int yyerror(char *s)
{
    return 0;
}

int main()
{
    yyparse();
    return 0;
}