%{ 
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
int yylex(void); 
void yyerror(const char *s); 
%} 
%union { 
    double dval; 
} 
%token <dval> NUMBER 
%type <dval> expr 
%left '+' '-' 
%left '*' '/' 
%right UMINUS 
%% 
program     : 
            | program statement 
            ; 
statement   : expr '\n' { printf("= %.2f\n", $1); } 
            ; 
expr : expr '+' expr { $$ = $1 + $3; } 
     | expr '-' expr { $$ = $1 - $3; } 
     | expr '*' expr { $$ = $1 * $3; } 
     | expr '/' expr { 
     if ($3 == 0.0) { 
     fprintf(stderr, "Error: Division by zero!\n"); 
     YYERROR; 
     } 
     $$ = $1 / $3; 
     } 
     | '-' expr %prec UMINUS { $$ = -$2; } 
     | '(' expr ')' { $$ = $2; } 
     | NUMBER { $$ = $1; } 
     ; 
%% 
int main() { 
    printf("Simple Calculator\n"); 
    printf("Enter expressions (press Ctrl+Z + Enter to exit):\n"); 
    return yyparse(); 
} 
void yyerror(const char *s) { 
    fprintf(stderr, "Error: %s\n", s); 
} 
