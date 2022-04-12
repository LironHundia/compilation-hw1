%{
#include "tokens.hpp"
#include <stdio.h>
%}

%option yylineno
%option noyywrap
digit ([0-9])
letter ([a-zA-Z])
whitespace ([\t\n\r ])
string_chars [\t\x20-\x7E]
string_hexa_to_string ([0-7][0-9A-F])
string_escape_sequence \\\\|\\\"|\\n|\\r|\\t|\\0|\\x{string_hexa_to_string}

%X STRING_RULES

%%
void                        return VOID;
int                         return INT;
byte                        return BYTE;
b                           return B;
bool                        return BOOL;
auto                        return AUTO;
and                         return AND;
or                          return OR;
not                         return NOT;
true                        return TRUE;
false                       return FALSE;
return                      return RETURN;
if                          return IF;
else                        return ELSE;
while                       return WHILE;
break                       return BREAK;
continue                    return CONTINUE;
;                           return SC;
,                           return COMMA;
\(                          return LPAREN;
\)                          return RPAREN;
\{                          return LBRACE;
\}                          return RBRACE;
=                           return ASSIGN;
[==|!=|<|>|<=|>=]           return RELOP;
[\+|\-|\*|\/]               return BINOP;
{letter}({digit}|{letter})* return ID;
0|[1-9]{digit}*             return NUM;
\/\/[^\n\r]                 return COMMENT;

[\"]                                      BEGIN(STRING_RULES); return STRING;
<STRING_RULES>{string_escape_sequence}    return STRING;
<STRING_RULES>[\"]                        BEGIN(INITIAL); return STRING;
<STRING_RULES>{string_chars}              return STRING;


{whitespace}                ;


%%
