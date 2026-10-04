// Purpose: Declares the recursive-descent parser and its functions for checking the input tokens against the LearnCompiler BNF grammar.
// Contains the declarations for the recursive-descent parser.
// Defines the parser functions used to check each part of the LearnCompiler BNF grammar.
#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <vector>
#include <string>

class Parser
{
private:
    std::vector<Token> tokens;
    int current;

    // Helper functions
    Token peek();
    Token advance();
    bool check(TokenType type);
    bool match(TokenType type);
    void syntaxError(std::string expected);

    // Grammar functions
    bool parseKeyword();
    bool parseIdentifier();
    bool parseDeclarations();
    bool parseAssignment();
    bool parseExpression();

public:
    Parser(std::vector<Token> tokens);

    bool parseProgram();
};

#endif