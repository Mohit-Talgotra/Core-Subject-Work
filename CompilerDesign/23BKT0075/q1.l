%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int line = 1;
int target = -1;
char longest[1000];
int printed = 0;
%}

%%

[^\n ]+ {
            if(line == target && strlen(yytext) > strlen(longest))
            {
                strcpy(longest, yytext);
            }
        }

\n      {
            if(line == target)
            {
                printf("Line %d: %s\n", line, longest[0] ? longest : "");
                printed = 1;
            }
            line++;
            longest[0] = '\0';
        }

.       ;

%%

int yywrap()
{
    return 1;
}

int main(int argc, char*argv[])
{
    if(argc < 3)
    {
        printf("Usage: %s <filename> <line_number>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if(!yyin)
    {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }
    target = atoi(argv[2]);
    longest[0] = '\0';
    yylex();
    if(!printed && line == target)
    {
        printf("Line %d: %s\n", line, longest[0] ? longest : "");
    }
    return 0;
}
