%{
#include "Node.hpp"
#define YYSTYPE Node*
#include "hw3_output.hpp"
#include "parser.tab.hpp"

extern int yylineno;
extern YYSTYPE yylval;
%}

%option yylineno
%option noyywrap
whitespace ([\t\n\r ])
letter ([a-zA-Z])
digit ([0-9])

%%
int     {return INT;}
byte    {return BYTE;}
b       {return B;}
bool    {return BOOL;}
and     {return AND;}
or      {return OR;}
not     {return NOT;}
true    {return TRUE;}
false   {return FALSE;}
return  {return RETURN;}
if      {return IF;}
else    {return ELSE;}
while   {return WHILE;}
break   {return BREAK;}
continue {return CONTINUE;}
;       {return SC;}
\(      {return LPAREN;}
\)      {return RPAREN;}
\{       {return LBRACE;}
\}       {return RBRACE;}
=       {return ASSIGN;}
==|!=   {yylval = new Op(yytext); return EQUALITY;}
>|<|>=|<=   {yylval = new Op(yytext); return RELATIONAL;}
\+|-    {yylval = new Op(yytext); return ADDITIVE;}
\*|\/      {yylval = new Op(yytext); return MULTIPLICATIVE;}
\"([^\n\r\"\\]|\\[rnt\"\\])+\" {return STRING;}
{letter}({digit}|{letter})* {yylval = new Id(yytext); return ID;}
0|[1-9]{digit}*   {yylval = new Number(yytext); return NUM;}

\/\/[^\n\r]*  ; /* Ignore comments */
{whitespace} ; /* To update yylineno and not print spaces */
. {output::errorLex(yylineno); exit(1);}
%%
