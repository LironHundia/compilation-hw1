
<!-- saved from url=(0121)https://grades.cs.technion.ac.il/grades.cgi?cajfibgifbdf3589b8e5cc49efc5af+2+236360+Spring2022+hw/WCFiles/tokens.hpp+5251 -->
<html><head><meta http-equiv="Content-Type" content="text/html; charset=windows-1252"></head><body>#ifndef TOKENS_HPP_
#define TOKENS_HPP_
#include <cstdlib>
  enum tokentype
  {
    VOID = 1,
    INT = 2,
    BYTE = 3,
    B = 4,
    BOOL = 5,
    AND = 6,
    OR = 7,
    NOT = 8,
    TRUE = 9,
    FALSE = 10,
    RETURN = 11,
    IF = 12,
    ELSE = 13,
    WHILE = 14,
    BREAK = 15,
    CONTINUE = 16, 
    SC = 17,
    COMMA = 18,
    LPAREN = 19,
    RPAREN = 20,
    LBRACE = 21,
    RBRACE = 22,
    ASSIGN = 23,
    RELOP = 24,
    BINOP = 25,
    COMMENT = 26,
    ID = 27,
    NUM = 28,
    STRING = 29,
	AUTO=30
  };
  extern int yylineno;
  extern char* yytext;
  extern int yyleng;
  extern int yylex();
#endif /* TOKENS_HPP_ */
</cstdlib></body></html>