%{ 
#include <stdio.h> 
#include <stdlib.h> 
int yylex(void); 
void yyerror(const char *s); 
%} 
%token ID NUMBER ASSIGN OPERATOR LPAREN RPAREN 
%left OPERATOR 
%% 
program     : assignment 
            ; 
assignment  : ID ASSIGN expr 
            ; 
expr    : expr OPERATOR expr 
        | LPAREN expr RPAREN 
        | ID 
        | NUMBER 
        ; 
%% 
int main() { 
    if (yyparse() == 0) { 
    printf("Valid\n"); 
    } else { 
    printf("Invalid\n"); 
    } 
    return 0; 
} 

void yyerror(const char *s) {} 
