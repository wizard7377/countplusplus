%{

    
#include "parser.hpp"
int yylex(yy::parser::semantic_type *yylval);  



%}

%%
([0-9]+)(.[0-9]+)?  { yylval.numT = strtod(yytext,NULL); return VAL; }
[-+*/^()] { return yytext[0]; }
[ \t\n]     ;
(mean|mode|mead|root|pow) { return FUNC; } 
%%

int yywrap() {
    return 1;
}


typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

int evalF(const char * string) {
    YY_BUFFER_STATE buffer = yy_scan_string(string);
    yyparse();
    yy_delete_buffer(buffer);
    return 0;
}