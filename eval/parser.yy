%skeleton "lalr1.cc" // -*- C++ -*-
%require "3.8.1"
%header

//%define api.token.raw

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  # include <string>
  class driver;
}

// The parsing context.
%param { driver& drv }

%locations

%define parse.trace
%define parse.error detailed
%define parse.lac full
%glr-parser

%code {
# include "driver.hh"
#include <map>
#include <string>


}

%define api.token.prefix {TOK_}
%token <std::string> STR ID
%token ADD '+'
%token SUB '-'
%token DIV '/'
%token MUL '*'
%token IF "IF"
%token FOR "FOR"
%token WHILE "WHILE"
%token LPAR "(" 
%token RPAR ")"
//%token <std::string> CONK
  
//%token <std::string> ID
//%token <std::string> ID
%token <double> NUMBER
%token INF "IN"
%token EQ "="
%token OUTF "OUT"
%token EOLINE ";"
//%token <std::string> FUNC
%nterm <double> exp
%nterm <double> inputVal


%printer { yyo << $$; } <*>;

%%


inputVal : exp { drv.resVal = $1; };

exp:  NUMBER { $$ = $1; } 
| LPAR exp RPAR { $$ = $2; }
|	exp ADD exp { $$ = $1+$3; }
|	exp SUB exp { $$ = $1-$3; }
|	exp DIV exp { $$ = $1*$3; }
|	exp MUL exp { $$ = $1/$3; }

;


%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
