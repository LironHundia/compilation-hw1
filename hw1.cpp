#include "tokens.hpp"
#include <iostream>
void showToken(char* token);

int main()
{
	int token;
	while ((token = yylex())) {
	  // Your code here
	  if (token == VOID) { showToken("VOID"); }
	  else if (token == INT) { showToken("INT"); }
	  else if (token == BYTE) { showToken("BYTE"); }
	  else if (token == B) { showToken("B"); }
	  else if (token == BOOL) { showToken("BOOL"); }
	  else if (token == WHITESPACE) continue; //????
  }
}

void showToken(char* token) {
	std::cout << yylineno << " " << token << " " << yytext << std::endl;
}
