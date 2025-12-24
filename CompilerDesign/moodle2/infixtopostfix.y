%{ 
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%%
expr : expr '+' expr { printf("+ "); }
     | expr '-' expr { printf("- "); }
     | expr '*' expr { printf("* "); }
     | expr '/' expr { printf("/ "); }
     | '(' expr ')' { }
     | NUMBER { printf("%d ", $1); }
     ;
%%
int main() { 
    printf("Enter infix expression: "); 
    yyparse(); 
    printf("\n"); 
    return 0; 
} 
void yyerror(const char *s) { 
    fprintf(stderr, "Error: %s\n", s); 
} 