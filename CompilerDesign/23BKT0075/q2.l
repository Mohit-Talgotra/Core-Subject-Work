%{
#include <stdio.h>
#include <string.h>

char words[1000][100];
int count = 0;
%}

%%

[A-Za-z]+   {
                int len = strlen(yytext);
                if(len >= 5 && len <= 10)
                {
                    strcpy(words[count++], yytext);
                }
            }

.|\n        ;

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
    printf("Count: %d\n", count);
    for(int i = 0; i < count; i++)
    {
        printf("%s\n", words[i]);
    }
    return 0;
}
