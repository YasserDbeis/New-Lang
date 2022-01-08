/*
    File: test.cpp
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-21-2021
    Description: Defines entry point for local testing of the lexer, parser, and compiler.
*/

#include "../include/parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

enum TEST_CHOICE
{
    LEXER,
    PARSER,
    COMPILER
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Invalid number of arguments to the program";
        exit(EXIT_FAILURE);
    }

    std::string input;
    std::string curr_line;
    while (std::getline(std::cin, curr_line))
    {
        input += curr_line + '\n';
    }

    /*
    // For reading in through file
    std::ifstream t("./test_cases/parser_test_cases/valid_test_cases/test_valid_program.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();

    input = (buffer.str());
    */

    // Print the input
    // std::cout << "INPUT: " << input << std::endl;

    int test_suite_choice = std::atoi(argv[1]);

    switch (test_suite_choice)
    {
    case LEXER:
    {
        Lexer lex(input);
        std::string res = lex.print_tokens();
        std::cout << res << std::endl;
        break;
    }
    case PARSER:
    {
        Parser parser(input);
        parser.parse_program();
        break;
    }
    case COMPILER:
    {
        // TODO
        break;
    }
    default:
    {
        std::cout << "Invalid argument (valid: 0-2)" << std::endl;
        exit(EXIT_FAILURE);
    }
    }
    return EXIT_SUCCESS;
}
