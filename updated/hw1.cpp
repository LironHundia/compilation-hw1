#include "tokens.hpp"
#include <iostream>
#include <sstream>

//declarations
class BasicToken {
private:
	tokentype type;
public:
	BasicToken(tokentype type) : type(type) {}
	virtual ~BasicToken() = default;
	virtual void handleToken();
};

class CommentToken : public BasicToken {
public:
	CommentToken(tokentype type = COMMENT) : BasicToken(type) {}
	virtual ~CommentToken() = default;
	void handleToken() override;
};

class StringToken : public BasicToken {
public:
	static std::string our_string;
	static bool is_string_open;
	StringToken(tokentype type = STRING) : BasicToken(type) {}
	virtual ~StringToken() = default;
	void handleToken() override;
};


BasicToken* identifyToken(int token);
void handleError(int token);
void edit_lexema(std::string& to_edit);
//error functions:
void ErrorUndefinedChar();
void ErrorUnclosedString();
void ErrorUndefinedEscapeSequence();

//definitions
std::string StringToken::our_string = std::string();
bool StringToken::is_string_open = false;


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

void StringToken::handleToken() {
	if (yytext == std::string("\"")){
		if(is_string_open == false) {
			is_string_open = true;
		}
		else {
			std::cout << yylineno << " STRING " << our_string << std::endl;
			our_string.clear();
			is_string_open = false;
		}
		return;
	}
	std::string current_lexeme(yytext);
	edit_lexema(current_lexeme);
	our_string += current_lexeme;
}

void edit_lexema(std::string& to_edit) {
	size_t position = 0;
	if((position = to_edit.find("\\\\")) != std::string::npos) {
		to_edit.replace(position, 2, 1, '\\');
	} else if((position = to_edit.find("\\n")) != std::string::npos) {
		to_edit.replace(position, 2, 1, '\n');
	} else if((position = to_edit.find("\\r")) != std::string::npos) {
		to_edit.replace(position, 2, 1, '\r');
	} else if((position = to_edit.find("\\t")) != std::string::npos) {
		to_edit.replace(position, 2, 1, '\t');
	} else if((position = to_edit.find("\\\"")) != std::string::npos) {
		to_edit.replace(position, 2, 1, '\"');
	} else if((position = to_edit.find("\\0")) != std::string::npos) {
		to_edit.replace(position, 2, 1, '\0');
	} else if((position = to_edit.find("\\x")) != std::string::npos) {
		std::string hex_str = to_edit.substr(position + 2, 2);
		std::istringstream hex_stream(hex_str);
		int hex_int;
		hex_stream >> std::hex >> hex_int;
		char hex_char = char(hex_int);
		to_edit.replace(position, 4, 1, hex_char);
	}
}


//error functions:
void ErrorUndefinedChar() {
	if(yytext[0] == '0') {
		std::cout<< "ERROR 0" << std::endl;
	}
	else {
		std::cout<< "ERROR " << yytext << std::endl;
	}
}
void ErrorUnclosedString() {
	std::cout << "Error unclosed string" << std::endl;
}
void ErrorUndefinedEscapeSequence(){
	std::string bad_sequence(yytext);
	bad_sequence.erase(0,1); //remove the first '\'
	std::cout << "Error undefined escape sequence " << bad_sequence << std::endl;
}


void handleError(int token) {
	if (token == ERROR_UNDEFINED_CHAR) {
		ErrorUndefinedChar();
	}
	else if(token == ERROR_UNCLOSED_STRING) {
		ErrorUnclosedString();
	}
	else if(token == ERROR_UNDEFINED_ESCAPE_SEQUENCE) {
		ErrorUndefinedEscapeSequence();
	}
	else { //shouldn't get here
		std::cout << "ERROR - WRONG ERROR NUMBER!" << std::endl;
	}
	exit(0);
}


BasicToken* identifyToken(int token) {
	if (token < 0) {//error case
		return nullptr;
	}
	else if (token == COMMENT) {
		return new CommentToken();
	}
	if (token == STRING) {
		return new StringToken();
	}
	else {
		return new BasicToken(tokentype(token));
	}
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
	if (StringToken::is_string_open == true){
		ErrorUnclosedString();
	}
	return 0;
}
