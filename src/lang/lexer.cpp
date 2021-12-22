#include "lexer.h"
#include <iostream>

void Lexer::lexical_analysis(std::string input) {}
void Lexer::skip_space() {}

Lexer::Lexer(std::string input)
{
    Token tok;
    tok.line_number = 1;
    tok.lexeme = input;
    tok.type = ID;
    tokens.push_back(tok);
}
Lexer::~Lexer() {}

std::string Lexer::print_tokens()
{
    std::string str = "";

    for (int i = 0; i < tokens.size(); i++)
    {
        str += tokens.at(i).lexeme;
        // std::cout << tokens.at(i).lexeme << std::endl;
    }

    return str;
}

Token Lexer::get_token() { return Token(); }
Token Lexer::peek(int offset) { return Token(); }