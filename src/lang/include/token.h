/*
    File: token.h
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-21-2021
    Description: Declares the Token struct. A Token has both a token type and a lexeme it encapsulates.
                 It also contains the line number where the token is read in the input string.
                 The types of tokens are enumerated.
*/

#pragma once

#include <string>

enum class TokenType
{
    SEMICOLON,
    RIGHTARROW,
    COMMA,
    EQUAL,
    BOOL,
    INT,
    DEC,
    STR,
    VOID,
    TRUE,
    FALSE,
    INT_NUM,
    DEC_NUM,
    STRING,
    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_MULT,
    OPERATOR_DIV,
    OPERATOR_GT,
    OPERATOR_LT,
    OPERATOR_GEQ,
    OPERATOR_LEQ,
    OPERATOR_IS,
    OPERATOR_AND,
    OPERATOR_OR,
    OPERATOR_NOT,
    OPERATOR_XOR,
    OPERATOR_XCL,
    OPERATOR_NEQ,
    LBRACE,
    RBRACE,
    LPAREN,
    RPAREN,
    WHILE,
    IF,
    ELSIF,
    ELSE,
    FUNC,
    RETURN,
    ID,
    END_OF_FILE
};

typedef struct Token
{
    std::string lexeme; /* Value of token, stored as a string */
    TokenType type;     /* The type of token */
    int line_number;    /* Line number it was found */

} Token;