%{
#include "tokens.hpp"
#include <stdio.h>
%}

%option yylineno
%option noyywrap
digit ([0-9])
letter ([a-zA-Z])
whitespace ([\t\n\r ])

%%
whitespace  return(WHITESPACE);
void   return(VOID);
int    return(INT);
byte   return(BYTE);
b      return(B);
bool   return(BOOL);

%%
