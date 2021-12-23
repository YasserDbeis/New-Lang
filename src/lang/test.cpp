/*
    File: test.cpp
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-21-2021
    Description: Defines entry point for local testing of the lexer, parser, and compiler.
*/

#include "lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    // std::ifstream t("test_code.txt");
    // std::stringstream buffer;
    // buffer << t.rdbuf();
    std::string input;
    std::string curr_line;
    while (std::getline(std::cin, curr_line))
    {
        input += curr_line + '\n';
    }

    // std::cout << "INPUT" << std::endl;
    // std::cout << input << std::endl;

    Lexer lex(input);
    std::string res = lex.print_tokens();
    std::cout << res << std::endl;
}