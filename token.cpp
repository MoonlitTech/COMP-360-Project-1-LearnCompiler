// Purpose: Implements functions related to tokens, including displaying token information and converting token types into readable names.
// Contains the implementation of token-related functions.
// Handles the creation, storage, and display of tokens produced by the lexical analyzer.
#include "token.h" 

Token::Token(TokenType type, const std::string& lexeme, int tokenLine) {
	this->type = type;
	this->lexeme = lexeme;
	this->lineNumber = tokenLine;
}

std::string tokenTypeToString(TokenType type) {
	switch (type) {
		case TokenType::FLOAT_KEYWORD:
			return "FLOAT_KEYWORD";
			
		case TokenType::IDENTIFIER:
			return "IDENTIFIER";

		case TokenType::LEFT_PAR:
			return "LEFT_PAR";

		case TokenType::RIGHT_PAR:
			return "RIGHT_PAR";

		case TokenType::LEFT_BRACE:
			return "LEFT_BRACE";

		case TokenType::RIGHT_BRACE:
			return "RIGHT_BRACE";

		case TokenType::SEMICOLON:
			return "SEMICOLON";

		case TokenType::ASSIGN:
			return "ASSIGN";

		case TokenType::MULTIPLY:
			return "MULTIPLY";

		case TokenType::DIVIDE:
			return "DIVIDE";

		case TokenType::END_OF_FILE:
			return "END_OF_FILE";

		case TokenType::UNKNOWN:
			return "UNKNOWN";
	}
	return "UNKNOWN";
}
