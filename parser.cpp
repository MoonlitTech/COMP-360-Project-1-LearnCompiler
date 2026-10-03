// Purpose: Implements the recursive-descent parser. It checks each grammar rule, identifies syntax errors, and reports whether the Sample Program is valid.
// Contains the implementation of the recursive-descent parser.
// Uses the LearnCompiler BNF grammar to check the syntax of the tokenized input program and reports syntax errors.
#include "Parser.h"
#include <iostream>

Parser::Parser(std::vector<Token> tokens)
{
    this->tokens = tokens;
    current = 0;
}

// Look at the current token
Token Parser::peek()
{
    return tokens[current];
}

// Move to the next token
Token Parser::advance()
{
    if (current < tokens.size())
    {
        current++;
    }

    return tokens[current - 1];
}

// Check the current token without moving
bool Parser::check(TokenType type)
{
    if (current >= tokens.size())
    {
        return false;
    }

    return peek().type == type;
}

// Check for a token and move forward if it matches
bool Parser::match(TokenType type)
{
    if (check(type))
    {
        advance();
        return true;
    }

    return false;
}

// Display the first syntax error
void Parser::syntaxError(std::string expected)
{
    std::cout << "Syntax Error on line "
              << peek().lineNumber
              << ": expected "
              << expected
              << ", found '"
              << peek().lexeme
              << "'."
              << std::endl;
}


// <keyword> -> float
bool Parser::parseKeyword()
{
    if (match(TokenType::FLOAT_KEYWORD))
    {
        return true;
    }

    syntaxError("float");
    return false;
}


// <ident> -> identifier
bool Parser::parseIdentifier()
{
    if (match(TokenType::IDENTIFIER))
    {
        return true;
    }

    syntaxError("identifier");
    return false;
}


// <expr> -> <ident> {*|/} <expr>
//         | <ident>
bool Parser::parseExpression()
{
    // Expression must start with an identifier
    if (!parseIdentifier())
    {
        return false;
    }

    // Check for *
    if (match(TokenType::MULTIPLY))
    {
        return parseExpression();
    }

    // Check for /
    if (match(TokenType::DIVIDE))
    {
        return parseExpression();
    }

    return true;
}


// <assign> -> <ident> = <expr>
bool Parser::parseAssignment()
{
    // Parse identifier
    if (!parseIdentifier())
    {
        return false;
    }

    // Parse =
    if (!match(TokenType::ASSIGN))
    {
        syntaxError("=");
        return false;
    }

    // Parse expression
    if (!parseExpression())
    {
        return false;
    }

    return true;
}


// <declares> -> <keyword> <ident> ;
//             | <keyword> <ident> ; <declares>
bool Parser::parseDeclarations()
{
    // At least one declaration is required
    if (!check(TokenType::FLOAT_KEYWORD))
    {
        return false;
    }

    // Keep reading declarations while we see float
    while (check(TokenType::FLOAT_KEYWORD))
    {
        // Parse float
        if (!parseKeyword())
        {
            return false;
        }

        // Parse variable name
        if (!parseIdentifier())
        {
            return false;
        }

        // Parse ;
        if (!match(TokenType::SEMICOLON))
        {
            syntaxError(";");
            return false;
        }
    }

    return true;
}


// <program> ->
// <keyword> <ident> (<keyword><ident>)
// { <declares> <assign> }
bool Parser::parseProgram()
{
    // float
    if (!parseKeyword())
    {
        return false;
    }

    // Program name
    if (!parseIdentifier())
    {
        return false;
    }

    // (
    if (!match(TokenType::LEFT_PAR))
    {
        syntaxError("(");
        return false;
    }

    // float
    if (!parseKeyword())
    {
        return false;
    }

    // Parameter name
    if (!parseIdentifier())
    {
        return false;
    }

    // )
    if (!match(TokenType::RIGHT_PAR))
    {
        syntaxError(")");
        return false;
    }

    // {
    if (!match(TokenType::LEFT_BRACE))
    {
        syntaxError("{");
        return false;
    }

    // Declarations
    if (!parseDeclarations())
    {
        syntaxError("declaration");
        return false;
    }

    // Assignment
    if (!parseAssignment())
    {
        return false;
    }

    // }
    if (!match(TokenType::RIGHT_BRACE))
    {
        syntaxError("}");
        return false;
    }

    // Make sure there is nothing after the program
    if (!check(TokenType::END_OF_FILE))
    {
        syntaxError("end of file");
        return false;
    }

    return true;
}