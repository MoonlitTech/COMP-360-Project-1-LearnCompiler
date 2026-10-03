// Purpose: Declares the lexical analyzer and its functions for reading input characters and creating lexemes and tokens.
// Contains the declarations for the lexical analyzer.
// Defines the functions and information needed to scan the input program and generate tokens for the parser.

#ifndef LEXER_H
#define LEXER_H 
#include "token.h"
#include <string>
#include <vector> 
#include <istream>

class Lexer {
private:
	std::istream& input;
	int currentLine;
public:
	Lexer(std::istream& inputStream);
	std::vector<token> tokenize();
};

#endif 
