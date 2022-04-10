#include "tokens.hpp"
#include <iostream>

//declarations
class BasicToken {
private:
	tokentype type;
public:
	BasicToken(tokentype type) : type(type) {}
	virtual void handleToken();
};

class CommentToken : public BasicToken {
public:
	CommentToken(tokentype type = COMMENT) : BasicToken(type) {}
	void handleToken() override;
};

BasicToken* identifyToken(int token);
void handleError(int token);

//definitions
void BasicToken::handleToken() {
	std::string token;
	if (type == VOID) { token = std::string("VOID"); }
	else if (type == INT) { token = std::string("INT"); }
	else if (type == BYTE) { token = std::string("BYTE"); }
	else if (type == B) { token = std::string("B"); }
	else if (type == BOOL) { token = std::string("BOOL"); }
	else if (type == AUTO) { token = std::string("AUTO"); }
	else if (type == AND) { token = std::string("AND"); }
	else if (type == OR) { token = std::string("OR"); }
	else if (type == NOT) { token = std::string("NOT"); }
	else if (type == TRUE) { token = std::string("TRUE"); }
	else if (type == FALSE) { token = std::string("FALSE"); }
	else if (type == RETURN) { token = std::string("RETURN"); }
	else if (type == IF) { token = std::string("IF"); }
	else if (type == ELSE) { token = std::string("ELSE"); }
	else if (type == WHILE) { token = std::string("WHILE"); }
	else if (type == BREAK) { token = std::string("BREAK"); }
	else if (type == CONTINUE) { token = std::string("CONTINUE"); }
	else if (type == SC) { token = std::string("SC"); }
	else if (type == COMMA) { token = std::string("COMMA"); }
	else if (type == LPAREN) { token = std::string("LPAREN"); }
	else if (type == RPAREN) { token = std::string("RPAREN"); }
	else if (type == LBRACE) { token = std::string("LBRACE"); }
	else if (type == RBRACE) { token = std::string("RBRACE"); }
	else if (type == ASSIGN) { token = std::string("ASSIGN"); }
	else if (type == RELOP) { token = std::string("RELOP"); }
	else if (type == BINOP) { token = std::string("BINOP"); }
	else if (type == ID) { token = std::string("ID"); }
	else if (type == NUM) { token = std::string("NUM"); }
	//after detemining which token is it
	std::cout << yylineno << " " << token << " " << yytext << std::endl;
}

void CommentToken::handleToken() {
	std::cout << yylineno << " COMMENT //" << std::endl;
}

BasicToken* identifyToken(int token) {
	if (token < 0) {//error case
		return nullptr;
	}
	else if (token == COMMENT) {
		return new CommentToken();
	}
	/*if (token == STRING) {
		//handle string
	}*/
	else {
		return new BasicToken(tokentype(token));
	}
}

void handleError(int token) {
	//TODO - need to add error handler
	std::cout << "error" << std::endl;
	exit(0);
}

int main()
{
	int token = 0;
	while ((token = yylex())) {
		//find out what kind of token it is, and assign accordingly
		BasicToken* current_token = identifyToken(token);
		//if this token is an error - handle and exit program
		if (current_token == nullptr) {
			handleError(token);
		}
		current_token->handleToken();
		delete current_token;
	}
	return 0;
}
