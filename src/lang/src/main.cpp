/*
    File: main.cpp
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-21-2021
    Description: Defines entry point for the SunLang interpreter
*/

#include "../include/executioner.h"
#include "../include/func_def_table.h"
#include <fstream>
#include <sstream>

enum PHASE_TYPE
{
    LEXER,
    PARSER,
    COMPILER
};

// Entry point to the SunLang interpreter. Reads in source code from stdin and interprets the
//   code according to the given phase type
// Usage: a.out (1-3) < file
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Invalid number of arguments to the program\n");
        exit(EXIT_FAILURE);
    }

    // Read the source code from stdin
    std::string input;
    std::string curr_line;
    while (std::getline(std::cin, curr_line))
    {
        input += curr_line + '\n';
    }

    // Get the phase choice from the 1st argument (0 indexed)
    int phase_choice = std::atoi(argv[1]);

    // Run the interpreter on the specified phase
    switch (phase_choice)
    {
    case LEXER:
    {
        Lexer lex(input);
        std::string res = lex.print_tokens();
        printf("%s\n", res.c_str());
        break;
    }
    case PARSER:
    {
        Parser parser(input);
        break;
    }
    case COMPILER:
    {
        Executioner executioner(input);
        executioner.execute_program();

        break;
    }
    default:
    {
        printf("Invalid argument (valid: 0-2)\n");
        exit(EXIT_FAILURE);
    }
    }
    return EXIT_SUCCESS;
}
