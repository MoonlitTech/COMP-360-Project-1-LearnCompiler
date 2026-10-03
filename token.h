// Purpose: Defines the token types and token structure used by the lexical analyzer and parser.
// Defines the token structure and token types used by the compiler.
// Provides the information needed to represent lexemes and their corresponding token types.

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
    FLOAT_KEYWORD,
    IDENTIFIER,
    LEFT_PAR,
    RIGHT_PAR,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    ASSIGN,
    MULTIPLY,
    DIVIDE,
    END_OF_FILE,
    UNKNOWN
};

struct Token
{
    TokenType type;
    std::string lexeme;
    int lineNumber;

    Token(TokenType type, const std::string& lexeme, int tokenLine);
};

std::string tokenTypeToString(TokenType type);

#endif
