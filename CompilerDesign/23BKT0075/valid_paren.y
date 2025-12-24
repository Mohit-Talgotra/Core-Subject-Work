%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%%
S : /* empty */
  | S '(' S ')'
  ;

%%

void yyerror(const char *s){
    printf("Invalid parenthesis\n");
}

int main(){
    printf("Enter the parenthesis expression: ");
    if(yyparse()==0)
        printf("Valid parenthesis\n");
    return 0;
}
