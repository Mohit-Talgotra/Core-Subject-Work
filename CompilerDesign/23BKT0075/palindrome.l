%{
#include <stdio.h>
#include <string.h>
%}

%%
[a-zA-Z]+ {
    int l = yyleng;
    char s[100];
    strcpy(s, yytext);
    int i, flag = 1;
    for(i = 0; i < l / 2; i++)
    {
        if(s[i] != s[l - i - 1])
        {
            flag = 0;
            break;
        }
    }
    if(flag)
        printf("Palindrome\n");
    else
        printf("Not Palindrome\n");
}
\n { return 0; }
%%

int yywrap()
{
    return 1;
}

int main()
{
    yylex();
    return 0;
}