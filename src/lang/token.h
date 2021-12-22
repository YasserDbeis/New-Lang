/*
    File: token.h
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-21-2021
    Description: Declares the Token struct. A Token has both a token type and a lexeme it encapsulates.
                 The types of tokens are enumerated.
*/

#include <string>

enum TokenType
{
    SEMICOLON,
    RIGHTARROW,
    COMMA,
    EQUAL,
    BOOL,
    INT,
    DEC,
    STR,
    TRUE,
    FALSE,
    OPERATOR,
    LBRACE,
    RBRACE,
    LPAREN,
    RPAREN,
    IF,
    ELSIF,
    ELSE,
    FUNC,
    ID
};

typedef struct Token
{
    std::string lexeme;
    TokenType type;
    int line_number;

} Token;