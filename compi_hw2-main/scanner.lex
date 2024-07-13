%{
/* Declaration Section */
#include "output.hpp"
#include "parser.tab.hpp"
#include <stdio.h>
%}

%option yylineno
%option noyywrap
%x STR

letter           ([A-Za-z])

hex              (x[0-7][0-9a-fA-F])
digitnozero      ([1-9])
whitespace       ([\n\t\r ])
escape           ([\\ntr\"0])
string           ([ !\]-~#-\[	])
digit            ([0-9])
digithex         ([0-9a-fA-F])
stringprefix     ({string}|\\{hex}|\\{escape})


%%
int                                                                                 return INT;
byte                                                                                return BYTE;
b                                                                                   return B;
bool                                                                                return BOOL;
and                                                                                 return AND;
or                                                                                  return OR;
not                                                                                 return NOT;
true                                                                                return TRUE;
false                                                                               return FALSE;
return                                                                              return RETURN;
if                                                                                  return IF;
else                                                                                return ELSE;
while                                                                               return WHILE;
break                                                                               return BREAK;
continue                                                                            return CONTINUE;
;                                                                                   return SC;
\(                                                                                  return LPAREN;
\)                                                                                  return RPAREN;
\{                                                                                  return LBRACE;
\}                                                                                  return RBRACE;
=                                                                                   return ASSIGN;
==|!=                                                                               return EQUALORNOT;
>|<|>=|<=                                                                           return RELOP;
[-+]                                                                                return MINUS_PLUS;
[*/]                                                                                return DIV_MUL;
\/\/[^\n\r]*                                                                        ;
{letter}[a-zA-Z0-9]*                                                                return ID;
({digitnozero}+{digit}*)|0                                                          return NUM;
\"{stringprefix}+\"                                                                 return STRING;
{whitespace}                                                                        ;
.                                                                                   {output::errorLex(yylineno); exit(1);}
