/*
    File: token.h
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-21-2021
    Description: Declares the Token struct. A Token has both a token type and a lexeme it encapsulates.
                 It also contains the line number where the token is read in the input string.
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
    ID,
    END_OF_FILE
};

typedef struct Token
{
    std::string lexeme; /* Value of token, stored as a string */
    TokenType type;     /* The type of token */
    int line_number;    /* Line number it was found */

} Token;