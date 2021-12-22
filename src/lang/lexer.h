/*
    File: lexer.h
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-21-2021
    Description: Declares the Lexer class. The Lexer performs lexical analysis on an input string
                 and stores the input as tokens in a private tokens vector. The parser can then
                 call the public functions: get_token, peek() in order to perform parsing.
*/

#pragma once

#include <string>
#include <vector>
#include "token.h"

class Lexer
{
private:
    std::vector<std::string> terminals          /* Vector containing language key words */
    {";", "->", ",", "=", "bool", "int", "dec", "str", "true", "false", "+", "-", "*", "/", ">", "<" 
    ">=", "<=", "is", "and", "or", "not", "!", "{", "{", "(", ")", "if", "elsif", "else", "func"};  

    std::vector<std::string> token_type_names;  /* Names of the token types (Accessed by the enum type index) */       
    std::vector<Token> tokens;                  /* Vector containing the tokens of the input received in constructor */
    int token_index;                            /* Parsing purposes: Keeps track of what token is currently being parsed */
    int input_index;
    int line_number;                            /* Keep track of current line number for describing the token */

    void lexical_analysis(std::string input);   /* Helper function - performs lexical analysis for the constructor */
    void skip_whitespace(std::string input);    /* Moves the token_index to the next valid start of a lexeme. Skipping whitespace */

public:
    Lexer(std::string input);                   /* Constructs lexer class. Reads input argument and does lexical analysis */
    ~Lexer();                                   /* Destructor */

    std::string print_tokens();                 /* Testing purposes: Returns a string representing tokens in input */

    Token get_token();                          /* Parsing purposes: Consumes and returns the next token in the tokens vector */
    Token peek(int offset);                     /* Parsing purposes: Returns the token at the given offset in the tokens vector */
};
