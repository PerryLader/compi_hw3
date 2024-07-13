%{
#include <stdio.h>
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap
whitespace ([\t\n\r ])
letter ([a-zA-Z])
digit ([0-9])
hex ([0-9a-fA-F])
notStringEnd ([^\"\n\r])
unprintable ([\x00-\x08\x0B\x0C\x0E-\x1F])

%x STRING

%%
void    {return VOID;}
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
[=!]=|[<>]=?   {return RELOP;}
\+|-|\*|\/      {return BINOP;}
\/\/[^\n\r]*    {return COMMENT;}
{letter}({digit}|{letter})* {return ID;}
0|[1-9]{digit}*   {return NUM;}

\"               {BEGIN(STRING); return STRING_START;}
<STRING>\"       {BEGIN(INITIAL); return STRING_END;}
<STRING>\\n     {return STRING_ESCAPE_N;}
<STRING>\\r     {return STRING_ESCAPE_R;}
<STRING>\\t     {return STRING_ESCAPE_T;}
<STRING>\\\\    {return STRING_ESCAPE_BACKSLASH;}
<STRING>\\\"    {return STRING_ESCAPE_QUOTES;}
<STRING>\\x{hex}{hex}   {return STRING_ESCAPE_HEX;}
<STRING>\\x{notStringEnd}{0,2} {return UNRECOGNIZED_SYMBOL;}
<STRING>\\0     {return STRING_ESCAPE_0;}

<STRING>[\n\r]  {return UNCLOSED_STRING;}
<STRING>\\.     {return UNRECOGNIZED_SYMBOL;}       
<STRING>{unprintable} {return UNPRINTABLE_CHAR;}

<STRING>.       {return STRING_CHAR;}


{whitespace} ; /* To update yylineno and not print spaces */
. {return UNRECOGNIZED_SYMBOL;}
%%
