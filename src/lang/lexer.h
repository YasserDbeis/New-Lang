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
    std::vector<std::string> terminals;
    std::vector<Token> tokens;
    int token_index;
    int line_number;

    void lexical_analysis(std::string input);
    void skip_space();

public:
    Lexer(std::string input);
    ~Lexer();

    std::string print_tokens();
    Token get_token();
    Token peek(int offset);
};
