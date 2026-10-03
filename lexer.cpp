// Purpose: Implements the lexical analyzer. It reads the Sample Program, identifies lexemes, creates tokens, and reports unknown symbols.
// Contains the implementation of the lexical analyzer.
// Reads the input program and breaks it into lexemes and tokens, identifying keywords, identifiers, operators, and other symbols. 

#include "lexer.h"
#include <cctype>
#include <string>

Lexer::Lexer(std::istream& inputStream) : input(inputStream), currentLine(1) {
}
std::vector<token> Lexer::tokenize() {
	std::vector<token> tokens;
	char ch;

	while (input.get(ch)) {
		if (ch == '\n') {
			currentLine++;
		}
		else if (std::isspace(ch)) {
			continue; // Skip whitespace
		}
		else if (std::isalpha(ch)) {
			std::string lexeme(1, ch);
			while (input.get(ch) && (std::isalnum(ch) || ch == '_')) {
				lexeme += ch;
			}
			input.unget(); // Put back the last character that is not part of the identifier
			TokenType type = (lexeme == "float") ? TokenType::FLOAT_KEYWORD : TokenType::IDENTIFIER;
			tokens.emplace_back(type, lexeme, currentLine);
		}
		else if (ch == '(') {
			tokens.emplace_back(TokenType::LEFT_PAR, "(", currentLine);
		}
		else if (ch == ')') {
			tokens.emplace_back(TokenType::RIGHT_PAR, ")", currentLine);
		}
		else if (ch == '{') {
			tokens.emplace_back(TokenType::LEFT_BRACE, "{", currentLine);
		}
		else if (ch == '}') {
			tokens.emplace_back(TokenType::RIGHT_BRACE, "}", currentLine);
		}
		else if (ch == ';') {
			tokens.emplace_back(TokenType::SEMICOLON, ";", currentLine);
		}
		else if (ch == '=') {
			tokens.emplace_back(TokenType::ASSIGN, "=", currentLine);
		}
		else if (ch == '*') {
			tokens.emplace_back(TokenType::MULTIPLY, "*", currentLine);
		}
		else if (ch == '/') {
			tokens.emplace_back(TokenType::DIVIDE, "/", currentLine);
		}
		else {
			std::string unknownLexeme(1, ch);
			tokens.emplace_back(TokenType::UNKNOWN, unknownLexeme, currentLine);
		}
	}
	tokens.emplace_back(TokenType::END_OF_FILE, "", currentLine); // Add EOF token at the end
	return tokens;
}