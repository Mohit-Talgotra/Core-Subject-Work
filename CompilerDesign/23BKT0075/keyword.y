%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int yylex();
int yyerror(char *s);
%}

%union
{
    char *str;
}

%token <str> WORD

%%
S :
WORD
{
    char *k[] = {"int","float","if","else","while","return","for"};
    int i, flag = 0;
    for(i = 0; i < 7; i++)
    {
        if(strcmp($1, k[i]) == 0)
        {
            flag = 1;
            break;
        }
    }
    if(flag)
        printf("Keyword\n");
    else
        printf("Not Keyword\n");
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