%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}

%%
S : A 'b' { printf("Valid string\n"); }
  ;

A : 'a''a''a''a''a' A
  | 'a''a''a''a''a'
  ;
%%

int main() {
    printf("Enter a string: ");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    printf("Invalid string\n");
}
