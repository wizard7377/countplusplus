%language "c++"
%{
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <math.h>
using namespace std;

int yyparse(void);
//int yylex(void);
extern int yylex (yy::parser::semantic_type *yylval);  
int yywrap();
void yyerror(const char *msg);
%}

%glr-parser

%union {
    double numT;
    char * fName;
}

%token <numT> VAL
%token <fName> FUNC

%nterm <numT> exp

%%

exp: exp '+' exp	{ $$ = $1 + $3; }
|	exp '-' exp	{ $$ = $1 - $3; }
|	exp '/' exp	{ $$ = $1 / $3; }
|	exp '*' exp	{ $$ = $1 * $3; }
|	exp '^' exp	{ $$ = pow($1,$3); }
|  '(' exp ')' { printf("%f",$2); $$ = $2; }
|	VAL	{ printf("%f",$1); $$ = $1; }


/*
list:	list ',' VAL
|	VAL
;
*/

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}
